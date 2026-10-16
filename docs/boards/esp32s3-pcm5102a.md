**English** | [Русский](../ru/boards/esp32s3-pcm5102a.md)

# ESP32-S3 N16R8 + PCM5102A

The officially supported build uses an **ESP32-S3 N16R8** module — 16 MB flash and
8 MB octal PSRAM — with an external PCM5102A I2S DAC plugged straight onto its pins.
This is the `esp32s3` build environment and the only configuration for which this fork
publishes and tests ready-to-flash firmware.

For the parts list and step-by-step assembly, see the
[shopping list](../getting-started/shopping-list.md) and
[assembly guide](../getting-started/assembly.md).

## Default I2S pins

| Function | GPIO | PCM5102A pin |
| --- | --- | --- |
| System-clock header position | 10 | SCK |
| Bit clock | 11 | BCK |
| Audio data | 12 | DIN |
| Word select | 13 | LRCK |
| Software ground | 14 | GND |
| Power | 5V | VIN |

The six-pin direct-stack header physically connects SCK to GPIO10. On the documented
PCM5102A module, the solder bridge beside SCK is closed and the DAC recovers its system
clock from BCK, so GPIO10 is not driven as MCLK. The firmware still routes optional MCLK
to GPIO8 for converters that require it.

Pins can be changed under **Board Configuration → Pin Configuration** in `menuconfig`,
but a custom pinout is no longer the tested release configuration.

> [!WARNING]
> **Bridge VIN/VOUT.** Most ESP32-S3 boards ship with the VIN/VOUT solder pads open.
> Bridge them, or the DAC receives no 5 V power and produces no sound.

## Flashing

=== "Browser"

    Use the ESP32-S3 N16R8 installer on the [flashing page](../getting-started/flashing.md).

=== "PlatformIO"

    ```bash
    pio run -e esp32s3 -t upload
    pio run -e esp32s3 -t uploadfs
    ```

    The second command is required — it writes the web UI to SPIFFS.

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32s3
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s3" build
    idf.py -p /dev/ttyUSB0 flash
    ```

## No Bluetooth A2DP

The ESP32-S3 has Bluetooth LE only, not Bluetooth Classic, so A2DP audio is unavailable.
The supported `esp32s3` release contains no Bluetooth audio support.
