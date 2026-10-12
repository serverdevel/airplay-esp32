#include "esp_log.h"
#include "esp_mac.h"
#include "esp_app_desc.h"
#include "mdns.h"
#include <stdio.h>
#include <string.h>

#include "base64.h"
#include "hap.h"
#include "mdns_airplay.h"
#include "rtsp_handlers.h"
#include "wifi.h"
#include "settings.h"

static const char *TAG = "mdns_airplay";

// Longest single DNS label (RFC 1035). The mDNS component caps names at
// MDNS_NAME_MAX_LEN, which is never smaller than this.
#define MDNS_HOSTNAME_MAX_LEN 63

// Feature flags are defined in rtsp_handlers.h (shared with /info handler)

// Protocol version
#ifdef CONFIG_AIRPLAY_FORCE_V1
#define AIRPLAY_PROTOCOL_VERSION "1"
#else
#define AIRPLAY_PROTOCOL_VERSION "2"
#endif
#define AIRPLAY_SOURCE_VERSION "377.40.00"

// Status bit 2 = audio link; bit 10 = configured for Home access control.
#define AIRPLAY_FLAG_AUDIO_LINK 0x0004u
#define AIRPLAY_FLAG_HOME_ACL   0x0400u

static char s_status_flags[12] = "0x4";
static bool s_mdns_started;

static void format_status_flags(void) {
  unsigned flags = AIRPLAY_FLAG_AUDIO_LINK;
  if (hap_pairing_count() > 0) {
    flags |= AIRPLAY_FLAG_HOME_ACL;
  }
  snprintf(s_status_flags, sizeof(s_status_flags), "0x%X", flags);
}

// Metadata types advertised in the "md" txt record:
//   0 = text (track title/artist/album), 1 = artwork (cover art images),
//   2 = progress.
// When artwork is disabled, drop "1" so senders do not transmit cover art
// (which can stall the audio pipeline and cause drop-outs on realtime
// streams) while still sending text and progress metadata.
#ifdef CONFIG_ENABLE_AIRPLAY_ARTWORK
#define AIRPLAY_METADATA_TYPES "0,1,2"
#else
#define AIRPLAY_METADATA_TYPES "0,2"
#endif

// Do not impersonate a HomePod here. Recent Home versions apply Apple's
// HomePod-specific provisioning rules to AudioAccessory model identifiers and
// may hide a third-party receiver from the manual accessory picker.
#define AIRPLAY_MODEL "AirPlay2-Receiver"

static void make_related_uuid(const char *pairing_id, char prefix,
                              char output[37]) {
  strlcpy(output, pairing_id, 37);
  output[0] = prefix;
}

static void format_extended_features(char output[16]) {
  uint64_t features = ((uint64_t)AIRPLAY_FEATURES_HI << 32) |
                      (uint64_t)AIRPLAY_FEATURES_LO;
  uint8_t little_endian[8];
  for (size_t i = 0; i < sizeof(little_endian); i++) {
    little_endian[i] = (uint8_t)(features >> (i * 8));
  }

  int len = base64_encode(little_endian, sizeof(little_endian), output, 15);
  if (len < 0) {
    output[0] = '\0';
    return;
  }
  while (len > 0 && output[len - 1] == '=') {
    len--;
  }
  output[len] = '\0';
}

void mdns_airplay_init(void) {
  char mac_str[18];
  char device_id[18];
  char features_str[32];
  char service_name[80];
  char pk_str[65]; // 32 bytes = 64 hex chars + null
  char device_name[65];
  char hostname[MDNS_HOSTNAME_MAX_LEN + 1];
  char pairing_id[37];
  char system_id[37];
  char group_id[37];
  char extended_features[16];

  // Get device name from settings. This is the user-facing name and stays
  // UTF-8 for the service instance names below; only the hostname is
  // restricted to ASCII.
  settings_get_device_name(device_name, sizeof(device_name));
  settings_device_name_to_hostname(device_name, hostname, sizeof(hostname));

  // Get MAC address
  wifi_get_mac_str(mac_str, sizeof(mac_str));
  strncpy(device_id, mac_str, sizeof(device_id));

  // Get real Ed25519 public key from HAP module
  const uint8_t *pk = hap_get_public_key();
  hap_get_pairing_identifier(pairing_id, sizeof(pairing_id));
  make_related_uuid(pairing_id, 'B', system_id);
  make_related_uuid(pairing_id, 'C', group_id);
  format_extended_features(extended_features);
  format_status_flags();
  for (int i = 0; i < 32; i++) {
    snprintf(pk_str + (size_t)i * 2, 3, "%02x", pk[i]);
  }

  // Format features as "hi,lo" hex string
  snprintf(features_str, sizeof(features_str), "0x%X,0x%X", AIRPLAY_FEATURES_LO,
           AIRPLAY_FEATURES_HI);

  // Create service name for RAOP: <mac>@<name>
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  snprintf(service_name, sizeof(service_name), "%02X%02X%02X%02X%02X%02X@%s",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], device_name);

  // Initialize mDNS
  ESP_ERROR_CHECK(mdns_init());

  // Set hostname. A bad name must not panic the device, so this is logged
  // like the service registrations below rather than ESP_ERROR_CHECK'd.
  esp_err_t err_host = mdns_hostname_set(hostname);
  if (err_host != ESP_OK) {
    ESP_LOGE(TAG, "Failed to set mDNS hostname '%s': %s", hostname,
             esp_err_to_name(err_host));
  } else {
    ESP_LOGI(TAG, "mDNS hostname: %s.local (device name: %s)", hostname,
             device_name);
  }

#ifndef CONFIG_AIRPLAY_FORCE_V1
  // ========================================
  // _airplay._tcp service (port 7000)
  // Only registered for AirPlay 2 mode
  // ========================================
  mdns_txt_item_t airplay_txt[] = {
      {"acl", "0"},
      {"deviceid", device_id},
      {"fex", extended_features},
      {"features", features_str},
      {"flags", s_status_flags},
      {"gcgl", "0"},
      {"gid", group_id},
      {"igl", "0"},
      {"manufacturer", "OpenAirplay"},
      {"model", AIRPLAY_MODEL},
      {"pk", pk_str},
      {"pi", pairing_id},
      {"protovers", "1.1"},
      {"psi", system_id},
      {"rsf", "0x0"},
      {"serialNumber", device_id},
      {"srcvers", AIRPLAY_SOURCE_VERSION},
      {"vv", AIRPLAY_PROTOCOL_VERSION},
      {"osvers", "15.0"},
      {"fv", esp_app_get_description()->version},
  };

  esp_err_t err =
      mdns_service_add(device_name, "_airplay", "_tcp", 7000, airplay_txt,
                       sizeof(airplay_txt) / sizeof(airplay_txt[0]));
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to add _airplay._tcp service: %s",
             esp_err_to_name(err));
  }
  ESP_LOGI(TAG,
           "AirPlay TXT: model=%s features=%s flags=%s pi=%s fex=%s",
           AIRPLAY_MODEL, features_str, s_status_flags, pairing_id,
           extended_features);
#endif

  // ========================================
  // _raop._tcp service (port 7000)
  // RAOP = Remote Audio Output Protocol
  // Service name format: <MAC>@<DeviceName>
  // ========================================
#ifdef CONFIG_AIRPLAY_FORCE_V1
  // AirPlay v1 (classic RAOP): match squeezelite-esp32 txt record format.
  // No features, no pk, no HAP pairing — just classic RAOP fields.
  mdns_txt_item_t raop_txt[] = {
      {"am", AIRPLAY_MODEL},
      {"tp", "UDP"},                  // Transport protocol
      {"sm", "false"},                // Sharing mode
      {"sv", "false"},                // Server version (unused)
      {"ek", "1"},                    // Encryption key available
      {"et", "0,1"},                  // Encryption types: none, RSA
      {"md", AIRPLAY_METADATA_TYPES}, // Metadata types
      {"cn", "0,1"},                  // Audio codecs: PCM, ALAC
      {"ch", "2"},                    // Channels
      {"ss", "16"},                   // Sample size (bits)
      {"sr", "44100"},                // Sample rate
      {"vn", "3"},                    // Version number
      {"txtvers", "1"},               // TXT record version
  };
#else
  // Dual-mode: include et=1 (RSA) so RAOP-only clients (TuneBlade, AirMusic,
  // shairtunes2, etc.) accept the advertisement, while keeping et=3,5 for
  // AirPlay 2 FairPlay/MFi-SAP. ek=1 advertises that an RSA-encrypted key
  // can be supplied via SDP rsaaeskey: at ANNOUNCE time.
  mdns_txt_item_t raop_txt[] = {
      {"am", AIRPLAY_MODEL},
      {"cn", "0,1,2,3"},              // Audio codecs: PCM, ALAC, AAC, AAC-ELD
      {"da", "true"},                 // Digest auth
      {"ek", "1"},                    // Encryption key available (RSA)
      {"et", "0,1,3,5"},              // Encryption types
      {"ft", features_str},           // Features (same as airplay)
      {"md", AIRPLAY_METADATA_TYPES}, // Metadata types
      {"pk", pk_str},                 // Public key
      {"sf", s_status_flags},         // Status flags
      {"tp", "UDP"},                  // Transport protocol
      {"vn", "65537"},                // Version number
      {"vs", AIRPLAY_SOURCE_VERSION},
      {"vv", AIRPLAY_PROTOCOL_VERSION},
  };
#endif

  esp_err_t err_raop =
      mdns_service_add(service_name, "_raop", "_tcp", 7000, raop_txt,
                       sizeof(raop_txt) / sizeof(raop_txt[0]));
  if (err_raop != ESP_OK) {
    ESP_LOGE(TAG, "Failed to add _raop._tcp service: %s",
             esp_err_to_name(err_raop));
  }
  s_mdns_started = true;
}

void mdns_airplay_update_pairing_status(void) {
  format_status_flags();
  if (!s_mdns_started) {
    return;
  }
#ifndef CONFIG_AIRPLAY_FORCE_V1
  esp_err_t err = mdns_service_txt_item_set("_airplay", "_tcp", "flags",
                                             s_status_flags);
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "Failed to update AirPlay pairing flag: %s",
             esp_err_to_name(err));
  }
#endif
  esp_err_t err_raop =
      mdns_service_txt_item_set("_raop", "_tcp", "sf", s_status_flags);
  if (err_raop != ESP_OK) {
    ESP_LOGW(TAG, "Failed to update RAOP pairing flag: %s",
             esp_err_to_name(err_raop));
  }
}
