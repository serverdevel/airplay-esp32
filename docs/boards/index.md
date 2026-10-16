**English** | [Русский](../ru/boards/index.md)

# Hardware support

## Official release target

This fork publishes and tests ready-to-flash firmware for exactly one hardware
configuration:

| Board | Memory | Audio output | Release image | Status |
| --- | --- | --- | :-: | --- |
| [ESP32-S3 N16R8 + PCM5102A](esp32s3-pcm5102a.md) | 16 MB flash, 8 MB octal PSRAM | External I2S DAC | yes | **Supported and tested** |

The expected wiring uses GPIO10–GPIO14 and the solder bridges documented in the
[assembly guide](../getting-started/assembly.md). Other ESP32-S3 memory variants and
pinouts are not interchangeable with the published image.

!!! warning "Check the module marking"

    The release requires an **N16R8** module. A board merely labelled "ESP32-S3" is not
    enough: variants with less flash, no PSRAM or a different PSRAM mode may fail to boot
    or run out of memory.

## Inherited source profiles

The source tree retains the following profiles from the upstream project. They are useful
as porting references and may still compile, but this fork does **not** test them, publish
release images for them or provide hardware support for them:

- [SqueezeAMP](squeezeamp.md)
- [Esparagus Audio Brick and Esparagus Louder](esparagus-audio-brick.md)
- [Esparagus Audio Brick Dual](esparagus-audio-brick-dual-dac.md)
- [HiFi-ESP32 and HiFi-Esparagus](hifi-esp32.md)
- [Loud-ESP32, Loud-Esparagus and Esparagus Echo](loud-esp32.md)
- [Amped-ESP32 and Amped-Esparagus](amped-esp32.md)
- [Louder-ESP32](louder-esp32.md)
- [Seeed XIAO ESP32-C5](xiao-esp32c5.md)
- ESP32-S2, Waveshare ESP32-S3, ESP32-WROVER and custom profiles

Use these configurations only if you are prepared to build from source, diagnose board-
specific issues and validate the result yourself. Their presence in `platformio.ini` or
`config/` does not mean they are supported release targets.

## Full build environment list

The inherited PlatformIO and ESP-IDF profiles are documented under
[build environments](../reference/build-environments.md).
