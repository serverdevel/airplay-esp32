[English](../../boards/xiao-esp32c5.md) | **Русский**

<a id="seeed-xiao-esp32-c5"></a>
# Seeed XIAO ESP32-C5

Seeed XIAO ESP32-C5 — это плата RISC-V с флэш-памятью 8 МБ, PSRAM 8 МБ и **двухдиапазонным интерфейсом.
WiFi 6**, что делает его привлекательным там, где полоса 2,4 ГГц перегружена. Подключите внешний ЦАП I2S.
например PCM5102A.

!!! warning "Нет Bluetooth A2DP"

    ESP32-C5 имеет только Bluetooth LE, а не Bluetooth Classic, поэтому звук A2DP не поддерживается.
    доступны на этой плате.

<a id="default-i2s-pins"></a>
## Контакты I2S по умолчанию

| Функция | GPIO | этикетка СЯО |
| --- | --- | --- |
| Битовые часы (BCK) | 8 | Д8 |
| Выбор слова (WS/LRCK) | 9 | Д9 |
| Данные в (DIN) | 10 | Д10 |

Измените их в разделе **Конфигурация платы → Конфигурация контактов** в `menuconfig`.

<a id="building"></a>
## Сборка

Для этой платы не существует готового образа — создайте его самостоятельно.

=== "PlatformIO"

Официальная платформа `platformio/espressif32` **не** поддерживает ESP32-C5, поэтому
    каждая среда использует сообщество
    Платформа [pioarduino](https://github.com/pioarduino/platform-espressif32), закреплена
    `platformio.ini`. Он включает в себя ESP-IDF 5.5.5, а PlatformIO загружает его автоматически.
    на первой сборке — дополнительная настройка не требуется.

    ```bash
    pio run -e esp32c5-xiao -t upload
    pio run -e esp32c5-xiao -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32c5
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32c5" build flash monitor
    ```

<a id="related"></a>
## См. также

- [Среды сборки](../reference/build-environments.md)
- [Пользовательская конфигурация платы](custom.md)
