# Assembly

No soldering skills needed. The PCM5102A plugs directly onto the ESP32 pins through a
female header — no breadboard, no jumper wires.

## Step 1 — Prepare the ESP32

The pins on **one side** of the ESP32 need to be removed, or simply not soldered on, so
the assembly fits inside the 3D-printed case. Only the side carrying GPIO11–GPIO14 needs
pins.

If your board arrived with pins already soldered on both sides, carefully desolder or clip
the pins on the opposite side.

## Step 2 — Plug the DAC onto the ESP32

Take a **female 2.54 mm pin header** (6 pins) and push it onto the ESP32 pins on the
GPIO11–14 side. Then insert the PCM5102A into the female header from the other side.

The connections made through the header are:

```mermaid
flowchart LR
    subgraph esp["ESP32-S3"]
        direction TB
        P5["5V"]
        P11["GPIO11"]
        P12["GPIO12"]
        P13["GPIO13"]
        P14["GPIO14"]
    end

    subgraph dac["PCM5102A"]
        direction TB
        VIN["VIN"]
        BCK["BCK"]
        DIN["DIN"]
        LCK["LCK"]
        GND["GND"]
    end

    P5 ---|power| VIN
    P11 ---|bit clock| BCK
    P12 ---|audio data| DIN
    P13 ---|L/R select| LCK
    P14 ---|software ground| GND
```

| ESP32-S3 pin | PCM5102A pin | Function |
| --- | --- | --- |
| 5V | VIN | Power for the DAC |
| GPIO11 | BCK | Bit clock (audio timing) |
| GPIO12 | DIN | Audio data |
| GPIO13 | LCK | Left/right channel select |
| GPIO14 | GND | Software ground, pulled low by the firmware |
| GND | GND | Ground — optional, the GPIO14 software ground is sufficient |

!!! warning "Bridge VIN/VOUT on the ESP32-S3"

    On the ESP32-S3 board, bridge the VIN/VOUT solder pads if they are not already
    connected. This lets the board take 5 V power directly. Without it the DAC will not
    be powered.

## Step 3 — Check the result

Your assembly should look like this:

<div class="grid" markdown>

<figure markdown>
  ![Front view of the assembled ESP32 and PCM5102A](../assets/ESP_PCM_front.png){ width="200" }
  <figcaption>Front</figcaption>
</figure>

<figure markdown>
  ![Back view of the assembled ESP32 and PCM5102A](../assets/ESP_PCM_back.png){ width="200" }
  <figcaption>Back</figcaption>
</figure>

<figure markdown>
  ![Side view of the assembled ESP32 and PCM5102A](../assets/ESP32_PCM_side.png){ width="150" }
  <figcaption>Side</figcaption>
</figure>

</div>

The PCM5102A sits on top of the ESP32 with the 3.5 mm audio jack sticking out the end.
Plug a USB-C cable into the ESP32 for power.

## Step 4 — Print the case (optional)

A 3D-printable enclosure and two matching rear covers are provided:

| Part | STL file | Notes |
| --- | --- | --- |
| Enclosure | [`esp32-airplay-enclosure.stl`](../assets/3d-models/esp32-airplay-enclosure.stl) | Main body |
| Standard rear cover | [`esp32-airplay-rear-cover-standard.stl`](../assets/3d-models/esp32-airplay-rear-cover-standard.stl) | 0.30 mm guide clearance; print this one first |
| Tight rear cover | [`esp32-airplay-rear-cover-tight.stl`](../assets/3d-models/esp32-airplay-rear-cover-tight.stl) | 0.20 mm guide clearance for a firmer fit |

The rear covers have a 35 × 22 mm outer face matching the enclosure, so the
four outside surfaces meet flush. Print a cover with its flat exterior face on
the build plate and its retaining guides facing upward. Standard PLA settings,
a 0.4 mm nozzle, 0.2 mm layers and three perimeters work well; no supports are
required for the cover.

The enclosure is designed for an assembly with pins on one side only, as
described in step 1. Actual cover fit depends on printer calibration and first
layer expansion; use the tight version only if the standard cover is loose.

## Next

Head to [Flash the firmware](flashing.md).
