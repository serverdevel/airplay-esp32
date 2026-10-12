#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#define HAP_PAIRING_ID_MAX 64
#define HAP_PAIRING_MAX    16

#define HAP_PERMISSION_USER  0x00
#define HAP_PERMISSION_ADMIN 0x01

typedef struct {
  uint8_t identifier[HAP_PAIRING_ID_MAX];
  uint8_t identifier_len;
  uint8_t public_key[32];
  uint8_t permissions;
} hap_pairing_t;

esp_err_t hap_pairings_init(void);
size_t hap_pairings_count(void);

bool hap_pairings_get(const uint8_t *identifier, size_t identifier_len,
                      hap_pairing_t *pairing);
bool hap_pairings_get_at(size_t index, hap_pairing_t *pairing);

esp_err_t hap_pairings_add(const uint8_t *identifier, size_t identifier_len,
                           const uint8_t public_key[32], uint8_t permissions);
esp_err_t hap_pairings_remove(const uint8_t *identifier,
                              size_t identifier_len);
esp_err_t hap_pairings_clear(void);
