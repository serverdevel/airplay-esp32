[English](../../boards/amped-esp32.md) | **Русский**

<a id="amped-esp32-and-amped-esparagus"></a>
# Amped-ESP32 и Amped-Esparagus

Платы Sonocotta [Amped-ESP32](https://github.com/sonocotta/esp32-audio-dock)
**PCM5100** I2S ЦАП перед усилителем класса D **TPA3110** или **TPA3128**. Спикеры
подключайтесь напрямую к плате, но в отличие от платы [Loud](loud-esp32.md) сигнал
сначала проходит через настоящий ЦАП.

Ни одна из частей не имеет порта управления I2C. Единственная линия управления усилителем — это линия активного высокого уровня.
Вывод `UNMUTE`, управляемый событиями воспроизведения RTSP с помощью того же кода поддержки платы, Loud
Использование плат: звук отключен до тех пор, пока клиент не нажмет кнопку воспроизведения, режим ожидания при паузе, выключение при отключении.

<a id="variants"></a>
## Варианты

| Среда сборки | Чип | Ethernet | Дисплей | Элементы управления | Bluetooth | Готовые |
| --- | --- | :-: | :-: | --- | :-: | :-: |
| `amped-esp32` | ESP32 | да | SH1106 OLED | — | — | — |
| `amped-esp32-bt` | ESP32 | да | SH1106 OLED | — | да | да |
| `amped-esparagus` | ESP32 | да | — | поворотный энкодер | — | — |
| `amped-esparagus-bt` | ESP32 | да | — | поворотный энкодер | да | да |
| `amped-esp32-s3` | ESP32-S3 | да | SH1106 OLED | — | — | да |

Bluetooth Classic существует только на оригинальном ESP32, поэтому для него не существует сборки `-bt`.
Плата S3. Для ESP32 публикуется готовый образ с Bluetooth.

!!! warning "Amped-Esparagus предназначена только для версии M"

    `config/sdkconfig.defaults.amped-esparagus` описывает аппаратное обеспечение **версии M**. Ранее
    версии используют другую распиновку.

Его ILI9342 TFT не является поддерживаемым драйвером — говорит прошивка
    [SSD1306/SH1106/SSD1309 OLED](../features/oled-display.md) и
    [ST7789 TFT](../features/tft-display.md) — поэтому поддержка дисплея закомментирована в
    конфигурация платы, плата поставляется без экрана. Поворотный энкодер работает:
    его поворот меняет громкость, щелчок переключает воспроизведение/паузу.

<a id="features"></a>
## Функции

- ЦАП PCM5100 в усилитель класса D TPA3110 или TPA3128.
- Усилитель отключен до начала воспроизведения, режим ожидания на паузе, выключен при отключении
- Программное управление громкостью — ни одна из частей не имеет регистра громкости.
- флэш-память 8 МБ
- [Bluetooth A2DP](../features/bluetooth.md) на вариантах ESP32
- [W5500 SPI Ethernet](../features/ethernet.md) с автоматическим аварийным переключением WiFi
- [SH1106 OLED](../features/oled-display.md) через SPI на Amped-ESP32 и Amped-ESP32-S3;
  [поворотный энкодер](../features/buttons.md) на Amped-Esparagus

<a id="flashing"></a>
## Прошивка

=== "Браузер"

Используйте установщик Amped для вашей платы на
    [страница прошивки](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    # ESP32 — AirPlay + Bluetooth + Ethernet + OLED
    pio run -e amped-esp32-bt -t upload
    pio run -e amped-esp32-bt -t uploadfs

    # ESP32 — Esparagus rev M, rotary encoder
    pio run -e amped-esparagus-bt -t upload
    pio run -e amped-esparagus-bt -t uploadfs

    # ESP32-S3
    pio run -e amped-esp32-s3 -t upload
    pio run -e amped-esp32-s3 -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.amped-esp32;config/sdkconfig.defaults.bt" build
    idf.py -p /dev/ttyUSB0 flash
    ```

Обмен `config/sdkconfig.defaults.amped-esp32-s3` после `idf.py set-target esp32s3`
    для версии S3.

<a id="default-gpio-assignments"></a>
## Назначения GPIO по умолчанию

| Функция | Ампед-ESP32 | Ампед-Esparagus | Ампед-ESP32-S3 |
| --- | :-: | :-: | :-: |
| I2S BCK | 26 | 26 | 14 |
| I2S WS | 25 | 25 | 15 |
| I2S ДЕЛАТЬ | 22 | 22 | 16 |
| Усилитель `UNMUTE` | 13 | 13 | 17 |
| Светодиод состояния | — | 12 | — |
| Роторный А | — | 33 | — |
| Роторный Б | — | 27 | — |
| Кодировщик нажмите | — | 34 | — |
| СПИ СКЛК | 18 | 18 | 12 |
| СПИ МОСИ | 23 | 23 | 11 |
| СПИ МИСО | 19 | 19 | 13 |
| Ethernet CS | 5 | 5 | 10 |
| Ethernet ИНТ | 35 | 35 | 6 |
| Ethernet РСТ | 14 | 14 | 5 |
| Показать CS | 15 | — | 47 |
| Дисплей постоянного тока | 4 | — | 38 |
| Показать РСТ | 32 | — | 48 |

<a id="related"></a>
## См. также

- [Loud-ESP32](loud-esp32.md) — усилители MAX98357A, без ЦАП спереди
- [HiFi-ESP32](hifi-esp32.md) — тот же PCM5100 на линейном уровне, без усилителя
- [Кнопки и поворотные энкодеры](../features/buttons.md)
- [Среды сборки](../reference/build-environments.md)
