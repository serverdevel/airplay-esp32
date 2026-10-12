#include "hap.h"

#include <string.h>

#include "esp_log.h"
#include "hap_pairings.h"
#include "sodium.h"
#include "tlv8.h"

static const char *TAG = "hap_pair_mgmt";

static void encode_error(uint8_t state, uint8_t error, uint8_t *output,
                         size_t output_capacity, size_t *output_len) {
  tlv8_encoder_t enc;
  tlv8_encoder_init(&enc, output, output_capacity);
  tlv8_encode_byte(&enc, TLV_TYPE_STATE, state);
  tlv8_encode_byte(&enc, TLV_TYPE_ERROR, error);
  *output_len = tlv8_encoder_size(&enc);
}

static bool valid_request(const uint8_t *input, size_t input_len,
                          uint8_t method) {
  size_t state_len = 0;
  size_t method_len = 0;
  const uint8_t *state =
      tlv8_find(input, input_len, TLV_TYPE_STATE, &state_len);
  const uint8_t *request_method =
      tlv8_find(input, input_len, TLV_TYPE_METHOD, &method_len);
  return state && state_len == 1 && state[0] == 1 && request_method &&
         method_len == 1 && request_method[0] == method;
}

static bool session_is_admin(const hap_session_t *session) {
  return session && session->session_established &&
         session->controller_authenticated &&
         (session->controller_permissions & HAP_PERMISSION_ADMIN) != 0;
}

esp_err_t hap_pair_add(hap_session_t *session, const uint8_t *input,
                       size_t input_len, uint8_t *output,
                       size_t output_capacity, size_t *output_len) {
  if (!session || !input || !output || !output_len ||
      !valid_request(input, input_len, TLV_METHOD_ADD_PAIRING)) {
    return ESP_ERR_INVALID_ARG;
  }

  uint8_t identifier[HAP_PAIRING_ID_MAX];
  uint8_t public_key[32];
  size_t identifier_len = 0;
  size_t public_key_len = 0;
  size_t permissions_len = 0;
  const uint8_t *permissions =
      tlv8_find(input, input_len, TLV_TYPE_PERMISSIONS, &permissions_len);

  if (!tlv8_decode_concat(input, input_len, TLV_TYPE_IDENTIFIER, identifier,
                          sizeof(identifier), &identifier_len) ||
      !tlv8_decode_concat(input, input_len, TLV_TYPE_PUBLIC_KEY, public_key,
                          sizeof(public_key), &public_key_len) ||
      identifier_len == 0 || public_key_len != sizeof(public_key) ||
      !permissions || permissions_len != 1) {
    return ESP_ERR_INVALID_ARG;
  }

  // The first Home controller is allowed to register over the transient HAP
  // session. Once paired, only a persistently verified admin may add peers.
  bool bootstrap = hap_pairings_count() == 0 && session->session_established;
  if (!bootstrap && !session_is_admin(session)) {
    encode_error(2, TLV_ERROR_AUTHENTICATION, output, output_capacity,
                 output_len);
    return ESP_OK;
  }

  hap_pairing_t existing;
  if (hap_pairings_get(identifier, identifier_len, &existing) &&
      sodium_memcmp(existing.public_key, public_key, sizeof(public_key)) != 0) {
    encode_error(2, TLV_ERROR_UNKNOWN, output, output_capacity, output_len);
    return ESP_OK;
  }

  esp_err_t err = hap_pairings_add(identifier, identifier_len, public_key,
                                   permissions[0]);
  if (err != ESP_OK) {
    encode_error(2, err == ESP_ERR_NO_MEM ? TLV_ERROR_MAX_PEERS
                                          : TLV_ERROR_UNKNOWN,
                 output, output_capacity, output_len);
    return ESP_OK;
  }

  memcpy(session->controller_identifier, identifier, identifier_len);
  session->controller_identifier_len = identifier_len;
  session->controller_permissions = permissions[0];
  session->controller_authenticated = true;

  tlv8_encoder_t enc;
  tlv8_encoder_init(&enc, output, output_capacity);
  tlv8_encode_byte(&enc, TLV_TYPE_STATE, 2);
  *output_len = tlv8_encoder_size(&enc);
  ESP_LOGI(TAG, "Stored Home controller (%u total)",
           (unsigned)hap_pairings_count());
  return ESP_OK;
}

esp_err_t hap_pair_remove(hap_session_t *session, const uint8_t *input,
                          size_t input_len, uint8_t *output,
                          size_t output_capacity, size_t *output_len) {
  if (!session || !input || !output || !output_len ||
      !valid_request(input, input_len, TLV_METHOD_REMOVE_PAIRING)) {
    return ESP_ERR_INVALID_ARG;
  }
  if (!session_is_admin(session)) {
    encode_error(2, TLV_ERROR_AUTHENTICATION, output, output_capacity,
                 output_len);
    return ESP_OK;
  }

  uint8_t identifier[HAP_PAIRING_ID_MAX];
  size_t identifier_len = 0;
  if (!tlv8_decode_concat(input, input_len, TLV_TYPE_IDENTIFIER, identifier,
                          sizeof(identifier), &identifier_len) ||
      identifier_len == 0) {
    return ESP_ERR_INVALID_ARG;
  }

  esp_err_t err = hap_pairings_remove(identifier, identifier_len);
  if (err != ESP_OK) {
    encode_error(2, TLV_ERROR_UNKNOWN, output, output_capacity, output_len);
    return ESP_OK;
  }

  tlv8_encoder_t enc;
  tlv8_encoder_init(&enc, output, output_capacity);
  tlv8_encode_byte(&enc, TLV_TYPE_STATE, 2);
  *output_len = tlv8_encoder_size(&enc);
  ESP_LOGI(TAG, "Removed Home controller (%u remaining)",
           (unsigned)hap_pairings_count());
  return ESP_OK;
}

esp_err_t hap_pair_list(hap_session_t *session, const uint8_t *input,
                        size_t input_len, uint8_t *output,
                        size_t output_capacity, size_t *output_len) {
  if (!session || !input || !output || !output_len ||
      !valid_request(input, input_len, TLV_METHOD_LIST_PAIRINGS)) {
    return ESP_ERR_INVALID_ARG;
  }
  if (!session_is_admin(session)) {
    encode_error(2, TLV_ERROR_AUTHENTICATION, output, output_capacity,
                 output_len);
    return ESP_OK;
  }

  tlv8_encoder_t enc;
  tlv8_encoder_init(&enc, output, output_capacity);
  if (!tlv8_encode_byte(&enc, TLV_TYPE_STATE, 2)) {
    return ESP_ERR_NO_MEM;
  }

  size_t count = hap_pairings_count();
  for (size_t i = 0; i < count; i++) {
    hap_pairing_t pairing;
    if (!hap_pairings_get_at(i, &pairing)) {
      continue;
    }
    if (i > 0 && !tlv8_encode(&enc, TLV_TYPE_SEPARATOR, NULL, 0)) {
      return ESP_ERR_NO_MEM;
    }
    if (!tlv8_encode(&enc, TLV_TYPE_IDENTIFIER, pairing.identifier,
                     pairing.identifier_len) ||
        !tlv8_encode(&enc, TLV_TYPE_PUBLIC_KEY, pairing.public_key,
                     sizeof(pairing.public_key)) ||
        !tlv8_encode_byte(&enc, TLV_TYPE_PERMISSIONS,
                          pairing.permissions)) {
      return ESP_ERR_NO_MEM;
    }
  }

  *output_len = tlv8_encoder_size(&enc);
  return ESP_OK;
}
