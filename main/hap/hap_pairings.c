#include "hap_pairings.h"

#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "nvs.h"

static const char *TAG = "hap_pairings";

#define NVS_NAMESPACE "airplay"
#define NVS_KEY        "hap_pairings"
#define STORE_MAGIC    0x48504150u
#define STORE_VERSION  1u

typedef struct {
  uint32_t magic;
  uint8_t version;
  uint8_t count;
  uint8_t reserved[2];
  hap_pairing_t entries[HAP_PAIRING_MAX];
} hap_pairing_store_t;

static hap_pairing_store_t s_store;
static SemaphoreHandle_t s_lock;

static int find_pairing(const uint8_t *identifier, size_t identifier_len) {
  for (size_t i = 0; i < s_store.count; i++) {
    const hap_pairing_t *entry = &s_store.entries[i];
    if (entry->identifier_len == identifier_len &&
        memcmp(entry->identifier, identifier, identifier_len) == 0) {
      return (int)i;
    }
  }
  return -1;
}

static esp_err_t persist_locked(void) {
  nvs_handle_t nvs;
  esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs);
  if (err != ESP_OK) {
    return err;
  }
  err = nvs_set_blob(nvs, NVS_KEY, &s_store, sizeof(s_store));
  if (err == ESP_OK) {
    err = nvs_commit(nvs);
  }
  nvs_close(nvs);
  return err;
}

esp_err_t hap_pairings_init(void) {
  if (!s_lock) {
    s_lock = xSemaphoreCreateMutex();
    if (!s_lock) {
      return ESP_ERR_NO_MEM;
    }
  }

  memset(&s_store, 0, sizeof(s_store));
  nvs_handle_t nvs;
  esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs);
  if (err == ESP_OK) {
    size_t len = sizeof(s_store);
    err = nvs_get_blob(nvs, NVS_KEY, &s_store, &len);
    nvs_close(nvs);
    if (err == ESP_OK && len == sizeof(s_store) &&
        s_store.magic == STORE_MAGIC && s_store.version == STORE_VERSION &&
        s_store.count <= HAP_PAIRING_MAX) {
      ESP_LOGI(TAG, "Loaded %u persistent Home controller(s)", s_store.count);
      return ESP_OK;
    }
  }

  memset(&s_store, 0, sizeof(s_store));
  s_store.magic = STORE_MAGIC;
  s_store.version = STORE_VERSION;
  ESP_LOGI(TAG, "No valid Home pairings found");
  return ESP_OK;
}

size_t hap_pairings_count(void) {
  if (!s_lock) {
    return 0;
  }
  xSemaphoreTake(s_lock, portMAX_DELAY);
  size_t count = s_store.count;
  xSemaphoreGive(s_lock);
  return count;
}

bool hap_pairings_get(const uint8_t *identifier, size_t identifier_len,
                      hap_pairing_t *pairing) {
  if (!s_lock || !identifier || identifier_len == 0 ||
      identifier_len > HAP_PAIRING_ID_MAX) {
    return false;
  }
  xSemaphoreTake(s_lock, portMAX_DELAY);
  int index = find_pairing(identifier, identifier_len);
  if (index >= 0 && pairing) {
    *pairing = s_store.entries[index];
  }
  xSemaphoreGive(s_lock);
  return index >= 0;
}

bool hap_pairings_get_at(size_t index, hap_pairing_t *pairing) {
  if (!s_lock || !pairing) {
    return false;
  }
  xSemaphoreTake(s_lock, portMAX_DELAY);
  bool found = index < s_store.count;
  if (found) {
    *pairing = s_store.entries[index];
  }
  xSemaphoreGive(s_lock);
  return found;
}

esp_err_t hap_pairings_add(const uint8_t *identifier, size_t identifier_len,
                           const uint8_t public_key[32], uint8_t permissions) {
  if (!s_lock || !identifier || !public_key || identifier_len == 0 ||
      identifier_len > HAP_PAIRING_ID_MAX) {
    return ESP_ERR_INVALID_ARG;
  }

  xSemaphoreTake(s_lock, portMAX_DELAY);
  int index = find_pairing(identifier, identifier_len);
  if (index < 0) {
    if (s_store.count >= HAP_PAIRING_MAX) {
      xSemaphoreGive(s_lock);
      return ESP_ERR_NO_MEM;
    }
    index = s_store.count++;
  }

  hap_pairing_t *entry = &s_store.entries[index];
  memset(entry, 0, sizeof(*entry));
  memcpy(entry->identifier, identifier, identifier_len);
  entry->identifier_len = (uint8_t)identifier_len;
  memcpy(entry->public_key, public_key, sizeof(entry->public_key));
  entry->permissions = permissions;
  esp_err_t err = persist_locked();
  xSemaphoreGive(s_lock);
  return err;
}

esp_err_t hap_pairings_remove(const uint8_t *identifier,
                              size_t identifier_len) {
  if (!s_lock || !identifier || identifier_len == 0 ||
      identifier_len > HAP_PAIRING_ID_MAX) {
    return ESP_ERR_INVALID_ARG;
  }

  xSemaphoreTake(s_lock, portMAX_DELAY);
  int index = find_pairing(identifier, identifier_len);
  if (index < 0) {
    xSemaphoreGive(s_lock);
    return ESP_OK;
  }

  size_t remaining = s_store.count - (size_t)index - 1;
  if (remaining > 0) {
    memmove(&s_store.entries[index], &s_store.entries[index + 1],
            remaining * sizeof(hap_pairing_t));
  }
  s_store.count--;
  memset(&s_store.entries[s_store.count], 0, sizeof(hap_pairing_t));
  esp_err_t err = persist_locked();
  xSemaphoreGive(s_lock);
  return err;
}

esp_err_t hap_pairings_clear(void) {
  if (!s_lock) {
    return ESP_ERR_INVALID_STATE;
  }
  xSemaphoreTake(s_lock, portMAX_DELAY);
  memset(s_store.entries, 0, sizeof(s_store.entries));
  s_store.count = 0;
  esp_err_t err = persist_locked();
  xSemaphoreGive(s_lock);
  return err;
}
