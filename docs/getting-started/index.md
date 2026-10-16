**English** | [Русский](../ru/getting-started/index.md)

# Getting started

Building an AirPlay speaker from scratch takes four steps and about half an hour, most of
which is waiting for a firmware flash.

```mermaid
flowchart LR
    A["1. Shopping list<br/><small>~$10, two boards</small>"]
    B["2. Assembly<br/><small>basic soldering</small>"]
    C["3. Flash<br/><small>from your browser</small>"]
    D["4. First boot<br/><small>join setup WiFi</small>"]
    E(["Playing music"])

    A --> B --> C --> D --> E

    classDef done stroke:#26a69a,stroke-width:2px
    class E done
```

1. **[Shopping list](shopping-list.md)** — two boards and a pin header, roughly $10
2. **[Assembly](assembly.md)** — solder the DAC directly below the ESP32
3. **[Flash the firmware](flashing.md)** — from your browser, or with PlatformIO / ESP-IDF
4. **[First boot](first-boot.md)** — join the setup WiFi and point it at your network

!!! tip "Which exact board should I buy?"

    Buy an **ESP32-S3 N16R8**: 16 MB flash and 8 MB octal PSRAM. This is the only
    configuration covered by the ready-to-flash release. Other ESP32 variants and
    integrated audio boards are inherited source profiles and are not tested here.
