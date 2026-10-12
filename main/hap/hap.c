#include <string.h>

#include "hap.h"

#include "esp_log.h"
#include "esp_mac.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "sodium.h"

#include "srp.h"
#include "hap_pairings.h"

static const char *TAG = "hap";

#define NVS_NAMESPACE  "airplay"
#define NVS_KEY_PUBLIC "ed25519_pub"
#define NVS_KEY_SECRET "ed25519_sec"

static uint8_t g_device_public_key[HAP_ED25519_PUBLIC_KEY_SIZE];
static uint8_t g_device_secret_key[HAP_ED25519_SECRET_KEY_SIZE];
static char g_pairing_identifier[37];
static bool g_initialized = false;

esp_err_t hap_init(void) {
  if (g_initialized) {
    return ESP_OK;
  }

  if (sodium_init() < 0) {
    ESP_LOGE(TAG, "Failed to initialize libsodium");
    return ESP_FAIL;
  }

  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  snprintf(g_pairing_identifier, sizeof(g_pairing_identifier),
           "A17A0000-%02X%02X-4%02X%01X-8%01X%02X-%02X%02X%02X%02X%02X%02X",
           mac[0], mac[1], mac[2], mac[3] & 0x0F, mac[4] & 0x0F, mac[5],
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  nvs_handle_t nvs;
  esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to open NVS: %s", esp_err_to_name(err));
    return err;
  }

  size_t pub_len = HAP_ED25519_PUBLIC_KEY_SIZE;
  size_t sec_len = HAP_ED25519_SECRET_KEY_SIZE;

  err = nvs_get_blob(nvs, NVS_KEY_PUBLIC, g_device_public_key, &pub_len);
  if (err == ESP_OK) {
    err = nvs_get_blob(nvs, NVS_KEY_SECRET, g_device_secret_key, &sec_len);
  }

  if (err != ESP_OK || pub_len != HAP_ED25519_PUBLIC_KEY_SIZE ||
      sec_len != HAP_ED25519_SECRET_KEY_SIZE) {
    crypto_sign_keypair(g_device_public_key, g_device_secret_key);

    err = nvs_set_blob(nvs, NVS_KEY_PUBLIC, g_device_public_key,
                       HAP_ED25519_PUBLIC_KEY_SIZE);
    if (err == ESP_OK) {
      err = nvs_set_blob(nvs, NVS_KEY_SECRET, g_device_secret_key,
                         HAP_ED25519_SECRET_KEY_SIZE);
    }
    if (err == ESP_OK) {
      err = nvs_commit(nvs);
    }
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "Failed to store keypair in NVS: %s", esp_err_to_name(err));
      nvs_close(nvs);
      return err;
    }
  }

  nvs_close(nvs);

  err = hap_pairings_init();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to initialize pairing store: %s",
             esp_err_to_name(err));
    return err;
  }

  g_initialized = true;
  return ESP_OK;
}

const uint8_t *hap_get_public_key(void) {
  return g_device_public_key;
}

void hap_get_pairing_identifier(char *buffer, size_t buffer_len) {
  if (buffer && buffer_len > 0) {
    strlcpy(buffer, g_pairing_identifier, buffer_len);
  }
}

size_t hap_pairing_count(void) { return hap_pairings_count(); }

esp_err_t hap_pairings_reset(void) { return hap_pairings_clear(); }

hap_session_t *hap_session_create(void) {
  hap_session_t *session = calloc(1, sizeof(hap_session_t));
  if (!session) {
    return NULL;
  }

  memcpy(session->device_public_key, g_device_public_key,
         HAP_ED25519_PUBLIC_KEY_SIZE);
  memcpy(session->device_secret_key, g_device_secret_key,
         HAP_ED25519_SECRET_KEY_SIZE);

  crypto_box_keypair(session->session_public_key, session->session_secret_key);

  session->pair_verify_state = 0;
  session->session_established = false;
  session->pair_setup_transient = false;
  session->encrypt_nonce = 0;
  session->decrypt_nonce = 0;

  return session;
}

void hap_session_free(hap_session_t *session) {
  if (!session) {
    return;
  }

  if (session->srp) {
    srp_session_free(session->srp);
    session->srp = NULL;
  }

  sodium_memzero(session->device_secret_key,
                 sizeof(session->device_secret_key));
  sodium_memzero(session->session_secret_key,
                 sizeof(session->session_secret_key));
  sodium_memzero(session->shared_secret, sizeof(session->shared_secret));
  sodium_memzero(session->encrypt_key, sizeof(session->encrypt_key));
  sodium_memzero(session->decrypt_key, sizeof(session->decrypt_key));
  free(session);
}
