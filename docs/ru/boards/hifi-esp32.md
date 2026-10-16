[English](../../boards/hifi-esp32.md) | **Русский**

<a id="hifi-esp32-and-hifi-esparagus"></a>
# HiFi-ESP32 и HiFi-Esparagus

Платы Sonocotta [HiFi-ESP32](https://github.com/sonocotta/esp32-audio-dock) соединяются
ESP32 или ESP32-S3 с ЦАП TI **PCM5100** I2S и линейным выходом. Нет
встроенный усилитель, поэтому они питают существующий усилитель или пару активных динамиков.

PCM5100 представляет собой простой ЦАП I2S: без порта управления I2C, без вывода отключения звука и без аппаратной регулировки громкости.
зарегистрироваться. Таким образом, прошивка имеет объем программного обеспечения, а код поддержки платы имеет
нечего делать, кроме как подключить шину SPI, которую используют Ethernet и дисплей.

<a id="variants"></a>
## Варианты

| Среда сборки | Чип | Ethernet | Дисплей | Bluetooth | Готовые |
| --- | --- | :-: | :-: | :-: | :-: |
| `hifi-esp32` | ESP32 | да | SH1106 OLED | — | — |
| `hifi-esp32-bt` | ESP32 | да | SH1106 OLED | да | да |
| `hifi-esparagus` | ESP32 | — | — | — | — |
| `hifi-esparagus-bt` | ESP32 | — | — | да | да |
| `hifi-esp32-s3` | ESP32-S3 | да | SH1106 OLED | — | да |
| `hifi-esparagus-s3` | ESP32-S3 | — | — | — | да |

Варианты **Esparagus** имеют одинаковую аудиосистему, но без разъема Ethernet и
отображение заголовка; Вместо этого на них имеется светодиодный индикатор состояния WS2812. Bluetooth Classic существует только на
исходный ESP32, поэтому для любого варианта S3 нет сборки `-bt`.

Для ESP32 публикуется готовый образ с Bluetooth. Сборка `hifi-esp32` или
`hifi-esparagus` самостоятельно, если вы предпочитаете иметь ОЗУ и флэшбэк.

<a id="features"></a>
## Функции

- ЦАП линейного уровня PCM5100, вся флэш-память 8 МБ
- Программная регулировка громкости — ЦАП не имеет регистра громкости.
- [Bluetooth A2DP](../features/bluetooth.md) на вариантах ESP32
- [W5500 SPI Ethernet](../features/ethernet.md) с автоматическим аварийным переключением WiFi, на
  варианты, отличные от Esparagus
- [SH1106 OLED](../features/oled-display.md) через SPI, совместно использующий шину Ethernet, на
  варианты, отличные от Esparagus

<a id="flashing"></a>
## Прошивка

=== "Браузер"

Используйте установщик HiFi для вашей платы на
    [страница прошивки](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    # ESP32 — AirPlay + Bluetooth + Ethernet + OLED
    pio run -e hifi-esp32-bt -t upload
    pio run -e hifi-esp32-bt -t uploadfs

    # ESP32 — Esparagus variant, AirPlay + Bluetooth over WiFi
    pio run -e hifi-esparagus-bt -t upload
    pio run -e hifi-esparagus-bt -t uploadfs

    # ESP32-S3 — AirPlay + Ethernet + OLED
    pio run -e hifi-esp32-s3 -t upload
    pio run -e hifi-esp32-s3 -t uploadfs

    # ESP32-S3 — Esparagus variant
    pio run -e hifi-esparagus-s3 -t upload
    pio run -e hifi-esparagus-s3 -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.hifi-esp32;config/sdkconfig.defaults.bt" build
    idf.py -p /dev/ttyUSB0 flash
    ```

Обмен `config/sdkconfig.defaults.hifi-esp32-s3` после `idf.py set-target esp32s3`
    для ревизии S3 и отбросьте `config/sdkconfig.defaults.bt` для сборки без
    Bluetooth.

<a id="default-gpio-assignments"></a>
## Назначения GPIO по умолчанию

| Функция | ESP32 | ESP32-S3 | Заметки |
| --- | :-: | :-: | --- |
| I2S BCK | 26 | 14 | Битовые часы |
| I2S WS | 25 | 15 | Выбор слова (LRCLK) |
| I2S ДЕЛАТЬ | 22 | 16 | Последовательные аудиоданные |
| I2S MCLK | — | — | Не используется; PCM5100 восстанавливает собственную тактовую частоту |
| Светодиод состояния | 33 | 9 | Адресный RGB, только варианты Esparagus |
| СПИ СКЛК | 18 | 12 | Совместно используется Ethernet и дисплей |
| СПИ МОСИ | 23 | 11 | Совместно используется Ethernet и дисплей |
| СПИ МИСО | 19 | 13 | Только Ethernet |
| Ethernet CS | 5 | 10 | W5500 |
| Ethernet ИНТ | 35 | 6 | W5500 |
| Ethernet РСТ | 14 | 5 | W5500 |
| Показать CS | 15 | 39 | SH1106 OLED |
| Дисплей постоянного тока | 4 | 40 | SH1106 OLED |
| Показать РСТ | 32 | 38 | SH1106 OLED |

Варианты Esparagus используют те же контакты I2S и оставляют блок SPI ненастроенным.

<a id="related"></a>
## См. также

— [Loud-ESP32](loud-esp32.md) — та же схема с усилителями MAX98357A на борту
- [Amped-ESP32](amped-esp32.md) — PCM5100 с усилителем TPA31xx позади него.
- [Bluetooth A2DP](../features/bluetooth.md)
- [Ethernet (W5500)](../features/ethernet.md)
- [Среды сборки](../reference/build-environments.md)
