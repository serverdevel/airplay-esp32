[English](../../boards/esp32s3-pcm5102a.md) | **Русский**

<a id="esp32-s3-pcm5102a"></a>
# ESP32-S3 + PCM5102A

Самый недорогой и распространённый вариант: обычная отладочная плата ESP32-S3 с
внешним I2S-ЦАП PCM5102A, подключённым непосредственно к её контактам. Для этой схемы
предназначена среда сборки по умолчанию (`esp32s3`), и именно на ней ведётся основная разработка.

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

Прямая шестиконтактная гребёнка физически соединяет SCK с GPIO10. На используемом здесь
модуле PCM5102A перемычка рядом с SCK замкнута, поэтому ЦАП восстанавливает системную
тактовую частоту из BCK, а GPIO10 не используется как MCLK. Универсальная прошивка при
необходимости выводит MCLK на GPIO8 — например, для моста I2S → S/PDIF на WM8805.

Назначение контактов можно изменить в `menuconfig`: **Board Configuration → Pin Configuration**.

> [!WARNING]
> **Перемычка VIN/VOUT.** На большинстве плат ESP32-S3 эти контактные площадки с завода
> разомкнуты. Соедините их припоем, иначе на ЦАП не поступит питание 5 В и звука не будет.

Точная установка гребёнки и всех перемычек показана в [руководстве по сборке](../getting-started/assembly.md).

<a id="flashing"></a>
## Прошивка

=== "Браузер"

    Используйте установщик на [странице прошивки](../getting-started/flashing.md).

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
## Почему на ESP32-S3 нет Bluetooth A2DP

ESP32-S3 поддерживает только Bluetooth LE, но не Bluetooth Classic, поэтому звук A2DP
на нём недоступен. Сборка `esp32s3` не содержит поддержки Bluetooth. Если она нужна,
используйте плату на обычном ESP32, например [SqueezeAMP](squeezeamp.md) или
[Esparagus Audio Brick](esparagus-audio-brick.md).

<a id="variants"></a>
## Другие варианты

<a id="waveshare-esp32-s3"></a>
### Waveshare ESP32-S3

Платы Waveshare ESP32-S3 используют другую распиновку, поэтому для них предусмотрены
отдельная среда и готовый образ:

```bash
pio run -e waveshare-esp32s3 -t upload
pio run -e waveshare-esp32s3 -t uploadfs
```

<a id="jtag-debugging"></a>
### Отладка JTAG

Среда `esp32s3-jtag` наследуется от `esp32s3` и загружает прошивку через встроенный
мост USB-JTAG, а не через последовательный загрузчик:

```bash
pio run -e esp32s3-jtag -t upload
```

<a id="esp32-s2"></a>
### ESP32-S2

Сборка ESP32-S2 создаётся в CI и публикуется как `airplay2-receiver-esp32s2.bin`; её
можно записать через [установщик в браузере](../getting-started/flashing.md). Среды
PlatformIO для неё нет, поэтому локальная сборка выполняется через ESP-IDF:

```bash
idf.py set-target esp32s2
idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s2" build
```

<a id="esp32-wrover"></a>
### ESP32-WROVER

Для старых модулей WROVER с 4 МБ флеш-памяти предназначена среда `esp32wrover-dev`.
Она рассчитана на плату Freenove WROVER и поддерживает Bluetooth:

```bash
pio run -e esp32wrover-dev -t upload
```
