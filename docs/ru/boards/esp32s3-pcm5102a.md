[English](../../boards/esp32s3-pcm5102a.md) | **Русский**

<a id="esp32-s3-pcm5102a"></a>
# ESP32-S3 N16R8 + PCM5102A

Официально поддерживаемая сборка использует модуль **ESP32-S3 N16R8** — 16 МБ flash
и 8 МБ octal PSRAM — с внешним I2S-ЦАП PCM5102A, подключённым непосредственно к
контактам платы. Для этой схемы предназначена среда `esp32s3`; только для неё этот
форк публикует и проверяет готовую прошивку.

Список компонентов и пошаговые инструкции находятся на страницах
[«Что купить»](../getting-started/shopping-list.md) и [«Сборка»](../getting-started/assembly.md).

<a id="default-i2s-pins"></a>
## Контакты I2S по умолчанию

| Сигнал | GPIO ESP32-S3 | Контакт PCM5102A |
| --- | --- | --- |
| Позиция системной тактовой частоты | 10 | SCK |
| Битовая тактовая частота | 11 | BCK |
| Аудиоданные | 12 | DIN |
| Выбор канала | 13 | LRCK |
| Программная земля | 14 | GND |
| Питание | 5V | VIN |

Прямая шестиконтактная гребёнка физически соединяет SCK с GPIO10. На используемом
модуле PCM5102A перемычка рядом с SCK замкнута, поэтому ЦАП восстанавливает системную
тактовую частоту из BCK, а GPIO10 не используется как MCLK. При необходимости прошивка
выводит дополнительный MCLK на GPIO8.

Назначение контактов можно изменить в `menuconfig`: **Board Configuration → Pin Configuration**,
но другая распиновка уже не относится к проверенной конфигурации релиза.

> [!WARNING]
> **Перемычка VIN/VOUT.** На большинстве плат ESP32-S3 эти площадки с завода
> разомкнуты. Соедините их припоем, иначе на ЦАП не поступит питание 5 В и звука не будет.

<a id="flashing"></a>
## Прошивка

=== "Браузер"

    Используйте установщик ESP32-S3 N16R8 на [странице прошивки](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    pio run -e esp32s3 -t upload
    pio run -e esp32s3 -t uploadfs
    ```

    Вторая команда обязательна: она записывает веб-интерфейс в SPIFFS.

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32s3
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s3" build
    idf.py -p /dev/ttyUSB0 flash
    ```

<a id="no-bluetooth-on-the-s3"></a>
## Нет Bluetooth A2DP

ESP32-S3 поддерживает только Bluetooth LE, но не Bluetooth Classic, поэтому звук A2DP
недоступен. Поддерживаемый релиз `esp32s3` не содержит Bluetooth-аудио.
