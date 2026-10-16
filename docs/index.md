---
title: ESP32 AirPlay 2 Receiver
hide:
  - navigation
---

**English** | [Русский](ru/index.md)

# ESP32 AirPlay 2 Receiver

**Add AirPlay 2 to an amplifier with an ESP32-S3 N16R8 and a PCM5102A DAC.**

This firmware turns a cheap ESP32 board into a wireless AirPlay 2 speaker. Plug it into
an amplifier or powered speakers and it shows up on your iPhone, iPad or Mac just like a
HomePod or an AirPlay TV.

No cloud. No app. Just tap and play.

!!! tip "Already have a board? Install it right now"

    Plug it in over USB and click Install. No toolchain, no downloads, no command line
    — your browser talks to the board directly.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esp32s3.json">
      <button slot="activate" class="md-button md-button--primary">Install on ESP32-S3</button>
      <span slot="unsupported">Your browser cannot flash over USB. Use Chrome, Edge or Opera on desktop.</span>
      <span slot="not-allowed">Flashing needs a secure (HTTPS) connection.</span>
    </esp-web-install-button>

    This installer is only for the officially supported **ESP32-S3 N16R8 + PCM5102A**
    build. It requires Chrome, Edge or Opera on desktop.

<div class="grid cards" markdown>

-   __New here?__

    Buy two boards, plug them together, flash from your browser.

    [Start here](getting-started/index.md)

-   __Check your hardware__

    The ready-to-flash release requires an ESP32-S3 N16R8 and PCM5102A.

    [Hardware support](boards/index.md)

-   __Something not working?__

    No setup WiFi, no sound, missing web pages, build errors.

    [Troubleshooting](troubleshooting.md)

-   __Want to hack on it?__

    Build environments, audio pipeline, protocol stack.

    [Architecture](reference/architecture.md)

</div>

## What you are building

<p align="center">
  <img src="assets/build/esp32-pcm5102a-complete.jpg"
       alt="An assembled ESP32-S3 and PCM5102A AirPlay receiver with a 3.5 mm jack"
       width="600"><br>
  <em>Two boards and one soldered pin header — the 3.5 mm jack goes to your amplifier</em>
</p>

## How it works in 30 seconds

```mermaid
flowchart LR
    P["iPhone / Mac"]
    W(("WiFi"))
    E["ESP32<br/><small>this firmware</small>"]
    D["DAC"]
    S["Your speakers"]

    P -->|AirPlay| W --> E -->|I2S| D -->|analog| S

    classDef hi stroke:#26a69a,stroke-width:3px
    class E hi
```

Your phone sees an AirPlay speaker on the network. The ESP32 receives the encrypted
stream, decodes it, keeps it clock-synced to the sender, and pushes the audio out over I2S
to a DAC. The DAC drives your amplifier. Full detail in
[architecture](reference/architecture.md).

## Officially supported hardware

Ready-to-flash releases from this fork are built and tested only for:

- **ESP32-S3 N16R8** — 16 MB flash and 8 MB octal PSRAM
- **PCM5102A I2S DAC** — connected using the documented GPIO10–GPIO14 header

See [ESP32-S3 + PCM5102A](boards/esp32s3-pcm5102a.md) for the exact board requirements,
wiring and solder bridges.

Other chip and board profiles remain in the source tree because they were inherited from
the upstream project. They are not tested by this fork, are not included in releases and
are not officially supported. See [hardware support](boards/index.md) before attempting a
source build for one of them.

## Features

- **AirPlay 2** — appears natively in Control Center and every AirPlay-capable app
- **Apple Home integration** — add the receiver to the Home app, transfer playback from
  a HomePod and keep the pairing after a reboot
- **ALAC and AAC decoding** — handles both live streaming (Siri, calls) and music playback
- **Multi-room** — PTP-based timing for synchronised playback across devices
- **Acoustic sync compensation** — adjust the receiver by −1000 to +1000 ms from the
  web interface to align it with a HomePod; changes apply live and remain saved
- **Web configuration** — set WiFi and device name from a browser
- **OTA updates** — update over WiFi; USB is only needed for the first flash
- **48 kHz output** — optional 44.1 → 48 kHz conversion for DACs and S/PDIF receivers that need it
- **Displays** — optional OLED or 320×170 colour TFT showing track metadata and progress
- **Hardware buttons** — optional physical play/pause, volume and track-skip buttons

### Limitations

- Audio only — no AirPlay video or photos
- One speaker per ESP32 board
- Needs a decent WiFi signal for stable streaming

## Acknowledgements

- [Shairport Sync](https://github.com/mikebrady/shairport-sync) — the reference AirPlay implementation
- [openairplay/airplay2-receiver](https://github.com/openairplay/airplay2-receiver) — Python AirPlay 2 implementation
- [Espressif](https://github.com/espressif) — ESP-IDF framework and codec libraries

## Legal

**Non-commercial use only.** Commercial use requires explicit permission — see
[LICENSE](https://github.com/serverdevel/airplay-esp32/blob/homekit-0.2.1.4/LICENSE).

This is an independent project based on protocol analysis. It is not affiliated with
Apple Inc., is not guaranteed to work with future iOS or macOS versions, and is provided
as-is without warranty.
