**English** | [Русский](../ru/getting-started/flashing.md)

# Flash the firmware

The published firmware is built and tested only for an **ESP32-S3 N16R8** with a
**PCM5102A** DAC wired as described in the [assembly guide](assembly.md).

> [!WARNING]
> Do not flash this image to an original ESP32, ESP32-S2, ESP32-C5, Waveshare board,
> SqueezeAMP, Esparagus or another integrated audio board. Profiles for those targets are
> inherited source code only and are not release-supported by this fork.

| Method | Use it when | Needs |
| --- | --- | --- |
| **[A — Browser](#option-a-install-from-your-browser)** | First installation on the supported board | Chrome, Edge or Opera |
| **[B — PlatformIO](#option-b-platformio)** | You are developing the firmware | Python and a clone of the repository |
| **[C — ESP-IDF](#option-c-esp-idf)** | You already work with ESP-IDF | ESP-IDF v5.5.5+ |

## Option A — Install from your browser

Connect the ESP32-S3 N16R8 over USB and click **Install**.

!!! info "Requirements"

    The installer works in desktop Chrome, Edge and Opera through the Web Serial API.
    Safari, Firefox, iOS and Android cannot use it.

<esp-web-install-button manifest="/airplay-esp32/firmware/esp32s3.json">
  <button slot="activate" class="md-button md-button--primary">Install on ESP32-S3 N16R8</button>
  <span slot="unsupported">Your browser cannot flash over USB. Use Chrome, Edge or Opera on desktop.</span>
  <span slot="not-allowed">Flashing needs a secure HTTPS connection.</span>
</esp-web-install-button>

The dashed beta button is shown only when a beta image for the same `esp32s3` target is
available. See [Beta builds](#beta-builds) before using it.

<esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esp32s3.json">
  <button slot="activate" class="md-button md-button--beta">Install beta</button>
  <span slot="unsupported"></span>
  <span slot="not-allowed"></span>
</esp-web-install-button>

After installation, unplug and reconnect the board. It starts in setup mode — continue
to [First boot](first-boot.md).

### Beta builds

Beta images use the latest build of the `staging` branch. They are intended for checking
a specific fix before the next release and may fail to boot. Installing the latest stable
`esp32s3` release restores the board.

!!! note "Prefer to flash manually?"

    Download the `airplay2-receiver-esp32s3-*-full.bin` asset from the
    [latest release](https://github.com/serverdevel/airplay-esp32/releases/latest) and
    flash it at offset **`0x0`** with `esptool` or the
    [esptool-js web tool](https://espressif.github.io/esptool-js/).

    The release also includes an `*-ota.bin` file for updates through the device web
    interface and a separate `*-spiffs.bin` filesystem image.

## Option B — PlatformIO

[PlatformIO](https://platformio.org/) configures the toolchain automatically.

```bash
# 1. Install the PlatformIO CLI
pip install platformio

# 2. Clone this fork, including submodules
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32

# 3. Flash the firmware
pio run -e esp32s3 -t upload

# 4. Flash the SPIFFS image containing the web UI and data files
pio run -e esp32s3 -t uploadfs

# 5. Optionally watch the serial output
pio run -e esp32s3 -t monitor
```

!!! warning "Step 4 is required"

    PlatformIO does **not** write SPIFFS as part of `-t upload`. Without `-t uploadfs`,
    the device boots but the setup portal and web interface are missing.

## Option C — ESP-IDF

```bash
# Install and activate ESP-IDF v5.5.5 or newer first
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32
source /path/to/esp-idf/export.sh

idf.py set-target esp32s3
idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s3" build
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB0 monitor
```

Unlike PlatformIO, `idf.py flash` writes the SPIFFS partition in the same operation.

## Next

Continue to [First boot](first-boot.md).
