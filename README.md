**English** | [Русский](README-RU.md)

<div align="center">

<img src="docs/assets/logo_airplay_esp32.png" alt="AirPlay ESP32" width="400">

# ESP32 AirPlay 2 Receiver

**Add AirPlay 2 to an amplifier with an ESP32-S3 N16R8 and a PCM5102A DAC**

[![GitHub stars](https://img.shields.io/github/stars/serverdevel/airplay-esp32?style=flat-square)](https://github.com/serverdevel/airplay-esp32/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/serverdevel/airplay-esp32?style=flat-square)](https://github.com/serverdevel/airplay-esp32/network)
[![License](https://img.shields.io/badge/license-Non--Commercial-blue?style=flat-square)](LICENSE)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.5+-red?style=flat-square)](https://docs.espressif.com/projects/esp-idf/)
[![Platform](https://img.shields.io/badge/platform-ESP32--S3%20N16R8-green?style=flat-square)](https://www.espressif.com/en/products/socs/esp32-s3)

### [Documentation](docs/index.md) · [Install from your browser](docs/getting-started/flashing.md) · [Troubleshooting](docs/troubleshooting.md)

</div>

---

## What is this?

This turns a cheap ESP32 board into a wireless AirPlay 2 speaker. Plug it into any
amplifier or powered speakers and it shows up on your iPhone, iPad or Mac just like a
HomePod or an AirPlay TV.

<p align="center">
  <img src="docs/assets/build/esp32-pcm5102a-complete.jpg"
       alt="Assembled ESP32-S3 and PCM5102A AirPlay receiver" width="720">
</p>

Ready-to-flash releases from this fork are built and tested only for an
**ESP32-S3 N16R8** (16 MB flash, 8 MB octal PSRAM) connected to a **PCM5102A** DAC
with the pinout documented below.

The repository still contains build profiles inherited from the upstream project for
other ESP32 chips and integrated audio boards. They are not tested by this fork, are not
included in its releases and are not officially supported.

**No cloud. No app. Just tap and play.**

## Quick start

The fastest route is the browser installer — no toolchain, no command line:

**[→ Install from your browser](docs/getting-started/flashing.md)**

Building from parts instead? You need an ESP32-S3 N16R8 dev board, a PCM5102A DAC, a
six-pin straight header and basic soldering equipment, roughly $10 total. See the
[assembly guide](docs/getting-started/assembly.md).

Building from source:

```bash
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32
pio run -e esp32s3 -t upload
pio run -e esp32s3 -t uploadfs   # required — writes the web UI to SPIFFS
```

## 3D-printable enclosure

The repository includes a printable enclosure for the ESP32-S3 + PCM5102A
assembly and two matching rear covers. The covers have a **35 × 22 mm** outer
face that sits flush with the enclosure.

| Model | Download | Fit |
| --- | --- | --- |
| Enclosure | [esp32-airplay-enclosure.stl](docs/assets/3d-models/esp32-airplay-enclosure.stl) | Main body |
| Standard rear cover | [esp32-airplay-rear-cover-standard.stl](docs/assets/3d-models/esp32-airplay-rear-cover-standard.stl) | 0.30 mm guide clearance; recommended first print |
| Tight rear cover | [esp32-airplay-rear-cover-tight.stl](docs/assets/3d-models/esp32-airplay-rear-cover-tight.stl) | 0.20 mm guide clearance |

Print the rear cover with its flat exterior face on the build plate and the
retaining guides facing upward. See the [assembly guide](docs/getting-started/assembly.md#step-5-print-the-case-optional)
for details.

## Features

- **AirPlay 2** — appears natively in Control Center and every AirPlay-capable app
- **ALAC and AAC decoding** — live streaming (Siri, calls) and music playback
- **Multi-room** — PTP-based timing for synchronised playback
- **Web configuration** and **OTA updates** — USB is only needed for the first flash
- **48 kHz output** — optional 44.1 → 48 kHz conversion via a sinc resampler
- **Displays** — optional OLED or 320×170 colour TFT with track metadata
- **Hardware buttons** — optional play/pause, volume and track skip

Audio only, one speaker per board, and a decent WiFi signal is required.

## Documentation

| | |
| --- | --- |
| [Getting started](docs/getting-started/index.md) | Shopping list, assembly, flashing, first boot |
| [Hardware](docs/boards/index.md) | Official ESP32-S3 N16R8 build and unverified inherited profiles |
| [Features](docs/features/airplay-tuning.md) | Displays, buttons and AirPlay tuning |
| [Reference](docs/reference/build-environments.md) | Build environments, SPIFFS, OTA, architecture |
| [Troubleshooting](docs/troubleshooting.md) | No sound, no setup WiFi, dropouts, build errors |

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) and the
[contributing guide](docs/contributing.md).
Documentation lives in [`docs/`](docs/) and is built with [Zensical](https://zensical.org/)
— every page on the site has an edit link that takes you straight to the GitHub editor.

## Acknowledgements

- [Shairport Sync](https://github.com/mikebrady/shairport-sync) — the reference AirPlay implementation
- [openairplay/airplay2-receiver](https://github.com/openairplay/airplay2-receiver) — Python AirPlay 2 implementation
- [Espressif](https://github.com/espressif) — ESP-IDF framework and codec libraries

## Legal

**Non-commercial use only.** Commercial use requires explicit permission — see [LICENSE](LICENSE).

This is an independent project based on protocol analysis. Not affiliated with Apple Inc.
Not guaranteed to work with future iOS or macOS versions. Provided as-is without warranty.
