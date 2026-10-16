[English](../../boards/louder-esp32.md) | **Русский**

<a id="louder-esp32-and-louder-esp32-plus"></a>
# Louder-ESP32 и Louder-ESP32-Plus

Платы Sonocotta [Louder-ESP32](https://github.com/sonocotta/esp32-audio-dock) имеют
TI **TAS58xx** сочетает в себе ЦАП и усилитель класса D, из того же семейства, что и
Используется [Esparagus Audio Brick](esparagus-audio-brick.md). Динамики подключаются напрямую.

Платы **Plus** оснащены **TAS5825M**; простые платы с **TAS5805M**.
Оба управляются одним и тем же драйвером, который считывает идентификатор кристалла при запуске, поэтому разница
это то, что может делать эта часть, а не то, какую сборку вы прошиваете:

- Громкость, отключение звука и 15-полосный параметрический эквалайзер (esparagus-audio-brick.md#equaliser)
  работайте над обеими частями.
- Потоки процессов и полные дампы PPC3 являются функцией **TAS5825M**. У TAS5805M нет
  регистр выбора потока, поэтому драйвер пропускает дамп, а не записывает его в неправильный адрес.
  место. См. [Платы TAS5805M](esparagus-audio-brick.md#tas5805m-boards).

Громкость регулируется усилителем (`CONFIG_DAC_CONTROLS_VOLUME`), а не программным обеспечением.

<a id="variants"></a>
## Варианты

| Среда сборки | Чип | Усилитель | Bluetooth | Готовые |
| --- | --- | --- | :-: | :-: |
| `louder-esp32` | ESP32 | ТАС5805М | — | — |
| `louder-esp32-bt` | ESP32 | ТАС5805М | да | да |
| `louder-esp32-plus` | ESP32 | ТАС5825М | — | — |
| `louder-esp32-plus-bt` | ESP32 | ТАС5825М | да | да |
| `louder-esp32-s3` | ESP32-S3 | ТАС5805М | — | да |
| `louder-esp32-s3-plus` | ESP32-S3 | ТАС5825М | — | да |

Bluetooth Classic существует только на оригинальной ESP32, поэтому ни на одной плате S3 нет `-bt`.
строить. Для ESP32 публикуется готовый образ с Bluetooth.

!!! note "Esparagus Louder — это отдельная плата"

    [Esparagus Louder](esparagus-audio-brick.md#esparagus-louder) тот же
    семейство усилителей в форм-факторе Sonocotta Esparagus и имеет собственную среду
    (`esparagus-louder`, `-bt`, `-s3`). Его сборка ESP32 отличается от `louder-esp32`
    распиновка: есть линия FAULTZ и светодиод RGB, но нет контакта `PDN`.

<a id="features"></a>
## Функции

- TAS5825M или TAS5805M со встроенным DSP и 15-полосным параметрическим эквалайзером (25 Гц – 16 кГц)
- Аппаратный регулятор громкости с настраиваемым максимальным уровнем
- Автоматическое управление состоянием питания, основанное на состоянии сеанса AirPlay.
- флэш-память 8 МБ
- [Bluetooth A2DP](../features/bluetooth.md) на вариантах ESP32
- [W5500 SPI Ethernet](../features/ethernet.md) с автоматическим аварийным переключением WiFi
- [SH1106 OLED](../features/oled-display.md) через SPI, совместно использующая шину Ethernet

<a id="flashing"></a>
## Прошивка

=== "Браузер"

Используйте установщик Louder для вашей платы на
    [страница прошивки](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    # ESP32 + TAS5805M
    pio run -e louder-esp32-bt -t upload
    pio run -e louder-esp32-bt -t uploadfs

    # ESP32 + TAS5825M
    pio run -e louder-esp32-plus-bt -t upload
    pio run -e louder-esp32-plus-bt -t uploadfs

    # ESP32-S3 + TAS5805M
    pio run -e louder-esp32-s3 -t upload
    pio run -e louder-esp32-s3 -t uploadfs

    # ESP32-S3 + TAS5825M
    pio run -e louder-esp32-s3-plus -t upload
    pio run -e louder-esp32-s3-plus -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.louder-esp32-plus;config/sdkconfig.defaults.bt" build
    idf.py -p /dev/ttyUSB0 flash
    ```

Обмен в `config/sdkconfig.defaults.louder-esp32-s3-plus` после
    `idf.py set-target esp32s3` для версии S3.

<a id="default-gpio-assignments"></a>
## Назначения GPIO по умолчанию

Версии ESP32 и S3 не имеют общей распиновки. Платы Plus отличаются от простых
только в выборе чипа Ethernet и выборе чипа OLED.

| Функция | Громче-ESP32 | Громче-ESP32-Plus | ESP32-S3 (оба) |
| --- | :-: | :-: | :-: |
| I2S BCK | 26 | 26 | 14 |
| I2S WS | 25 | 25 | 15 |
| I2S ДЕЛАТЬ | 22 | 22 | 16 |
| I2C ПДД | 21 | 21 | 8 |
| I2C СКЛ | 27 | 27 | 9 |
| Усилитель `PDN` | 33 | 33 | 17 |
| СПИ СКЛК | 18 | 18 | 12 |
| СПИ МОСИ | 23 | 23 | 11 |
| СПИ МИСО | 19 | 19 | 13 |
| Ethernet CS | 5 | 15 | 10 |
| Ethernet ИНТ | 35 | 35 | 6 |
| Ethernet РСТ | 14 | 14 | 5 |
| Показать CS | 15 | 5 | 47 |
| Дисплей постоянного тока | 4 | 4 | 38 |
| Показать РСТ | 32 | 32 | 48 |

`PDN` подается на высокий уровень один раз при загрузке, а затем остается в покое — это отключение питания усилителя.
контакт, а не отключение звука для каждой дорожки на платах [Loud](loud-esp32.md) и [Amped](amped-esp32.md)
переключиться с событий воспроизведения.

<a id="related"></a>
## См. также

- [Esparagus Audio Brick](esparagus-audio-brick.md) — тот же драйвер TAS58xx, эквалайзер и рабочий процесс PPC3
- [HybridFlow DSP](../features/hybridflow.md)
- [Bluetooth A2DP](../features/bluetooth.md)
- [Ethernet (W5500)](../features/ethernet.md)
- [Среды сборки](../reference/build-environments.md)
