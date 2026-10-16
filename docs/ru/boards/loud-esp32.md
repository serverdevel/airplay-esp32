[English](../../boards/loud-esp32.md) | **Русский**

<a id="loud-esp32-loud-esparagus-and-esparagus-echo"></a>
# Loud-ESP32, Loud-Esparagus и Esparagus Echo

Платы Sonocotta [Loud-ESP32](https://github.com/sonocotta/esp32-audio-dock) приводят в действие
**MAX98357A** Непосредственно усилители I2S — без ЦАП спереди, без порта управления I2C. Спикеры
подключайтесь напрямую к плате.

MAX98357A имеет ровно одну линию управления: активный высокий уровень разрешения `SD_MODE`. Прошивка
регистрирует минимальный драйвер ЦАП, единственная задача которого — управлять этим выводом при воспроизведении RTSP
событий, поэтому усилитель остается отключенным до тех пор, пока клиент действительно не нажмет кнопку воспроизведения и не отключится
вернуться в режим ожидания на паузе. Это то же самое состояние власти, которое управляет
[Esparagus Audio Brick](esparagus-audio-brick.md) превосходит I2C, уменьшенный до одного GPIO.

<a id="variants"></a>
## Варианты

| Среда сборки | Чип | Усилители | Ethernet | Дисплей | Bluetooth | Готовые |
| --- | --- | :-: | :-: | :-: | :-: | :-: |
| `loud-esp32` | ESP32 | 1 | да | SH1106 OLED | — | — |
| `loud-esp32-bt` | ESP32 | 1 | да | SH1106 OLED | да | да |
| `loud-esparagus` | ESP32 | 2 | — | — | — | — |
| `loud-esparagus-bt` | ESP32 | 2 | — | — | да | да |
| `loud-esp32-s3` | ESP32-S3 | 2 | да | SH1106 OLED | — | да |
| `esparagus-echo` | ESP32-S3 | 2 | да | — | — | да |

Оба усилителя имеют один контакт включения, поэтому плата с двумя усилителями выключает и включает звук по мере необходимости.
единица. Bluetooth Classic существует только на оригинальной ESP32, поэтому ни одна плата S3 не имеет
Сборка `-bt`; на ESP32 публикуется готовый образ с Bluetooth.

[Esparagus Echo](https://github.com/sonocotta/esparagus-echo) - тот же усилитель
Расположение на плате Echo S3 — Ethernet, светодиод состояния RGB и отсутствие заголовка дисплея.

<a id="features"></a>
## Функции

- Один или два усилителя класса D MAX98357A, динамики подключены напрямую
- Усилитель отключен до начала воспроизведения, режим ожидания на паузе, выключен при отключении
- Программное управление громкостью — MAX98357A не имеет регистра громкости.
- флэш-память 8 МБ
- [Bluetooth A2DP](../features/bluetooth.md) на вариантах ESP32
- [W5500 SPI Ethernet](../features/ethernet.md) с автоматическим переключением при сбое WiFi, кроме
  Громкий-Esparagus
- [SH1106 OLED](../features/oled-display.md) через SPI, совместно использующая шину Ethernet, вкл.
  Loud-ESP32 и Loud-ESP32-S3

<a id="flashing"></a>
## Прошивка

=== "Браузер"

Используйте установщик Loud или Esparagus Echo на
    [страница прошивки](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    # ESP32 — AirPlay + Bluetooth + Ethernet + OLED
    pio run -e loud-esp32-bt -t upload
    pio run -e loud-esp32-bt -t uploadfs

    # ESP32 — Esparagus variant, dual amp over WiFi
    pio run -e loud-esparagus-bt -t upload
    pio run -e loud-esparagus-bt -t uploadfs

    # ESP32-S3 — dual amp, Ethernet + OLED
    pio run -e loud-esp32-s3 -t upload
    pio run -e loud-esp32-s3 -t uploadfs

    # ESP32-S3 — Esparagus Echo
    pio run -e esparagus-echo -t upload
    pio run -e esparagus-echo -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.loud-esp32;config/sdkconfig.defaults.bt" build
    idf.py -p /dev/ttyUSB0 flash
    ```

Обмен в `config/sdkconfig.defaults.loud-esp32-s3` или
    `config/sdkconfig.defaults.esparagus-echo` после `idf.py set-target esp32s3` для
    Платы S3.

<a id="default-gpio-assignments"></a>
## Назначения GPIO по умолчанию

| Функция | Громкий-ESP32 | Громкий-Esparagus | Громкий-ESP32-S3 | Esparagus Эхо |
| --- | :-: | :-: | :-: | :-: |
| I2S BCK | 26 | 26 | 14 | 18 |
| I2S WS | 25 | 25 | 15 | 8 |
| I2S ДЕЛАТЬ | 22 | 22 | 16 | 17 |
| Включение усилителя (`SD_MODE`) | 13 | 13 | 17 | 9 |
| Светодиод состояния | — | 33 | — | 42 |
| СПИ СКЛК | 18 | — | 12 | 12 |
| СПИ МОСИ | 23 | — | 11 | 11 |
| СПИ МИСО | 19 | — | 13 | 13 |
| Ethernet CS | 5 | — | 10 | 10 |
| Ethernet ИНТ | 35 | — | 6 | 6 |
| Ethernet РСТ | 14 | — | 5 | 5 |
| Показать CS | 15 | — | 39 | — |
| Дисплей постоянного тока | 4 | — | 40 | — |
| Показать РСТ | 32 | — | 38 | — |

!!! warning "Включающий контакт Loud-ESP32-S3 перемещен"

    `CONFIG_DAC_ENABLE_GPIO` — это GPIO 17 для аппаратного обеспечения версии G и более поздних версий. В версии F использовался GPIO 8.
    На плате версии F переопределите ее в
    [пользовательская конфигурация](custom.md), иначе звук никогда не будет включен.

<a id="related"></a>
## См. также

- [HiFi-ESP32](hifi-esp32.md) — та же раскладка с линейным PCM5100 вместо него
- [Amped-ESP32](amped-esp32.md) — PCM5100 с усилителем TPA31xx
- [Bluetooth A2DP](../features/bluetooth.md)
- [Ethernet (W5500)](../features/ethernet.md)
- [Среды сборки](../reference/build-environments.md)
