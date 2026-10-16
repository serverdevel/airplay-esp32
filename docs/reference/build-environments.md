**English** | [Русский](../ru/reference/build-environments.md)

# Build environments

Every PlatformIO environment defined in `platformio.ini`. Only `esp32s3` — ESP32-S3
N16R8 with PCM5102A — is built, tested and published by this fork. Every other entry on
this page is an inherited, unverified source profile with no release image.

## Generic boards

| Environment | Chip | Flash | Notes |
| --- | --- | --- | --- |
| `esp32s3` | ESP32-S3 | 16 MB | Default. External I2S DAC such as a PCM5102A |
| `esp32s3-jtag` | ESP32-S3 | 16 MB | Extends `esp32s3`, uploads over built-in USB JTAG |
| `waveshare-esp32s3` | ESP32-S3 | 16 MB | Waveshare ESP32-S3 pin arrangement |
| `esp32c5-xiao` | ESP32-C5 | 8 MB | Seeed XIAO, needs the community pioarduino platform |
| `esp32wrover-dev` | ESP32 | 4 MB | Freenove WROVER, includes Bluetooth |

## Amplifier boards

| Environment | Chip | DAC | Flash | Bluetooth |
| --- | --- | --- | --- | :-: |
| `squeezeamp` | ESP32 | TAS5756 | 8 MB | — |
| `squeezeamp-bt` | ESP32 | TAS5756 | 8 MB | yes |
| `squeezeamp-4m` | ESP32 | TAS5756 | 4 MB | — |
| `esparagus-audio-brick` | ESP32 | TAS58xx | 8 MB | — |
| `esparagus-audio-brick-bt` | ESP32 | TAS58xx | 8 MB | yes |
| `esparagus-audio-brick-s3` | ESP32-S3 | TAS58xx | 8 MB | — |
| `esparagus-audio-brick-dual-dac` | ESP32-S3 | 2× TAS58xx | 8 MB | — |
| `esparagus-audio-brick-dual-uac` | ESP32-S3 | 2× TAS58xx | 8 MB | — |
| `esparagus-louder` | ESP32 | TAS58xx | 8 MB | — |
| `esparagus-louder-bt` | ESP32 | TAS58xx | 8 MB | yes |
| `esparagus-louder-s3` | ESP32-S3 | TAS58xx | 8 MB | — |
| `smartamp` | ESP32 | — | 4 MB | yes |

Every Esparagus board is fitted with a TAS58xx amplifier, either a TAS5825M or a TAS5805M.
The driver reads the die ID at startup and configures whichever it finds, so the
environment does not have to know which part is on the board.

The dual-DAC environments drive an [Audio Brick Dual](../boards/esparagus-audio-brick-dual-dac.md)
with two amplifiers: stereo at I2C address 0x4C and a second at 0x4D, wired either as a
bridged (PBTL) mono output or as a second stereo pair. `-dual-uac` adds USB audio to the
same board.

## Sonocotta audio dock boards

The [HiFi](../boards/hifi-esp32.md), [Loud](../boards/loud-esp32.md),
[Amped](../boards/amped-esp32.md) and [Louder](../boards/louder-esp32.md) families all
come in an `-esp32` form with an Ethernet jack and an OLED header, and an `-esparagus`
form without either. Bluetooth Classic exists only on the original ESP32, so no S3
environment has a `-bt` variant.

| Environment | Chip | DAC / amp | Flash | Bluetooth |
| --- | --- | --- | --- | :-: |
| `hifi-esp32` | ESP32 | PCM5100 | 8 MB | — |
| `hifi-esp32-bt` | ESP32 | PCM5100 | 8 MB | yes |
| `hifi-esparagus` | ESP32 | PCM5100 | 8 MB | — |
| `hifi-esparagus-bt` | ESP32 | PCM5100 | 8 MB | yes |
| `hifi-esp32-s3` | ESP32-S3 | PCM5100 | 8 MB | — |
| `hifi-esparagus-s3` | ESP32-S3 | PCM5100 | 8 MB | — |
| `loud-esp32` | ESP32 | MAX98357A | 8 MB | — |
| `loud-esp32-bt` | ESP32 | MAX98357A | 8 MB | yes |
| `loud-esparagus` | ESP32 | 2× MAX98357A | 8 MB | — |
| `loud-esparagus-bt` | ESP32 | 2× MAX98357A | 8 MB | yes |
| `loud-esp32-s3` | ESP32-S3 | 2× MAX98357A | 8 MB | — |
| `esparagus-echo` | ESP32-S3 | 2× MAX98357A | 8 MB | — |
| `amped-esp32` | ESP32 | PCM5100 + TPA31xx | 8 MB | — |
| `amped-esp32-bt` | ESP32 | PCM5100 + TPA31xx | 8 MB | yes |
| `amped-esparagus` | ESP32 | PCM5100 + TPA31xx | 8 MB | — |
| `amped-esparagus-bt` | ESP32 | PCM5100 + TPA31xx | 8 MB | yes |
| `amped-esp32-s3` | ESP32-S3 | PCM5100 + TPA31xx | 8 MB | — |
| `louder-esp32` | ESP32 | TAS5805M | 8 MB | — |
| `louder-esp32-bt` | ESP32 | TAS5805M | 8 MB | yes |
| `louder-esp32-plus` | ESP32 | TAS5825M | 8 MB | — |
| `louder-esp32-plus-bt` | ESP32 | TAS5825M | 8 MB | yes |
| `louder-esp32-s3` | ESP32-S3 | TAS5805M | 8 MB | — |
| `louder-esp32-s3-plus` | ESP32-S3 | TAS5825M | 8 MB | — |

## Targets without a PlatformIO environment

These have sdkconfig defaults and are built through ESP-IDF directly.

| Target | Sdkconfig | Status |
| --- | --- | --- |
| ESP32-S2 | `config/sdkconfig.defaults.esp32s2` | Inherited and unverified; no release image |
| ESP32-P4 | `config/sdkconfig.defaults.esp32p4` | Experimental |

```bash
idf.py set-target esp32s2
idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s2" build
```

## Published release image

The release workflow builds only **`esp32s3`**. The browser installer exposes only the
matching `docs/firmware/esp32s3.json` manifest. Stable releases and beta builds must not
publish any other board profile.

All other environments are retained solely for upstream reference and manual porting.
Successful compilation, if it occurs, does not make a profile supported.

## How sdkconfig layering works

All board configuration lives in **`config/`**. The generated `sdkconfig` stays at the
project root — that one is a build artifact and is gitignored.

Environments compose their configuration by chaining sdkconfig files left to right, with
later files overriding earlier ones:

```ini
board_build.cmake_extra_args =
    "-DSDKCONFIG_DEFAULTS=config/sdkconfig.defaults;config/sdkconfig.defaults.squeezeamp;config/sdkconfig.defaults.bt"
```

Here the common defaults come first, then the SqueezeAMP board configuration, then the
Bluetooth overlay. Adding `config/sdkconfig.defaults.bt` to the end of any ESP32 board's chain is
how Bluetooth gets enabled.

!!! warning "Delete the cached sdkconfig after changing defaults"

    A generated `sdkconfig.<env>` file is cached in the project root. If you change any
    defaults, delete it before rebuilding or the old values are silently reused.

## Common commands

```bash
pio run -e <env> -t build      # Build
pio run -e <env> -t upload     # Build and flash over USB
pio run -e <env> -t uploadfs   # Flash the SPIFFS image from data/
pio run -e <env> -t monitor    # Serial monitor at 115200 baud
pio run -e <env> -t menuconfig # Kconfig configuration
```

To define your own environment without touching `platformio.ini`, see
[custom board configuration](../boards/custom.md).
