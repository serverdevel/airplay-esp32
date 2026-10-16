[English](../../reference/build-environments.md) | **Русский**

<a id="build-environments"></a>
# Среды сборки

Каждая среда PlatformIO, определенная в `platformio.ini`. По умолчанию — `esp32s3`.

<a id="generic-boards"></a>
## Общие платы

| Среда сборки | Чип | Флэш | Заметки |
| --- | --- | --- | --- |
| `esp32s3` | ESP32-S3 | 16 МБ | По умолчанию. Внешний ЦАП I2S, например PCM5102A |
| `esp32s3-jtag` | ESP32-S3 | 16 МБ | Расширяет `esp32s3`, загружает через встроенный USB JTAG |
| `waveshare-esp32s3` | ESP32-S3 | 16 МБ | Расположение контактов Waveshare ESP32-S3 |
| `esp32c5-xiao` | ESP32-C5 | 8 МБ | Seeed XIAO, нуждается в платформе Pioarduino сообщества |
| `esp32wrover-dev` | ESP32 | 4 МБ | Freenove WROVER, включает Bluetooth |

<a id="amplifier-boards"></a>
## Платы усилителей

| Среда сборки | Чип | ЦАП | Флэш | Bluetooth |
| --- | --- | --- | --- | :-: |
| `squeezeamp` | ESP32 | ТАС5756 | 8 МБ | — |
| `squeezeamp-bt` | ESP32 | ТАС5756 | 8 МБ | да |
| `squeezeamp-4m` | ESP32 | ТАС5756 | 4 МБ | — |
| `esparagus-audio-brick` | ESP32 | ТАС58хх | 8 МБ | — |
| `esparagus-audio-brick-bt` | ESP32 | ТАС58хх | 8 МБ | да |
| `esparagus-audio-brick-s3` | ESP32-S3 | ТАС58хх | 8 МБ | — |
| `esparagus-audio-brick-dual-dac` | ESP32-S3 | 2× ТАС58хх | 8 МБ | — |
| `esparagus-audio-brick-dual-uac` | ESP32-S3 | 2× ТАС58хх | 8 МБ | — |
| `esparagus-louder` | ESP32 | ТАС58хх | 8 МБ | — |
| `esparagus-louder-bt` | ESP32 | ТАС58хх | 8 МБ | да |
| `esparagus-louder-s3` | ESP32-S3 | ТАС58хх | 8 МБ | — |
| `smartamp` | ESP32 | — | 4 МБ | да |

Каждая плата Esparagus оснащена усилителем TAS58xx: TAS5825M или TAS5805M.
Драйвер считывает идентификатор кристалла при запуске и настраивает тот, который находит, поэтому
среде сборки не обязательно знать, какая часть находится на плате.

В средах с двумя ЦАП используется [Audio Brick Dual](../boards/esparagus-audio-brick-dual-dac.md)
с двумя усилителями: стерео по адресу I2C по адресу 0x4C и второй по 0x4D, подключенный либо как
мостовой (PBTL) моновыход или в качестве второй стереопары. `-dual-uac` добавляет звук USB в
та же плата.

<a id="sonocotta-audio-dock-boards"></a>
## Платы аудиодок-станции Sonocotta

[HiFi](../boards/hifi-esp32.md), [Громкий](../boards/loud-esp32.md),
Все семейства [Amped](../boards/amped-esp32.md) и [Louder](../boards/louder-esp32.md)
выпускаются в форме `-esp32` с разъемом Ethernet и разъемом OLED, а также в форме `-esparagus`.
форма без того и другого. Bluetooth Classic существует только на оригинальном ESP32, поэтому S3 нет.
В среде есть вариант `-bt`.

| Среда сборки | Чип | ЦАП/усилитель | Флэш | Bluetooth |
| --- | --- | --- | --- | :-: |
| `hifi-esp32` | ESP32 | PCM5100 | 8 МБ | — |
| `hifi-esp32-bt` | ESP32 | PCM5100 | 8 МБ | да |
| `hifi-esparagus` | ESP32 | PCM5100 | 8 МБ | — |
| `hifi-esparagus-bt` | ESP32 | PCM5100 | 8 МБ | да |
| `hifi-esp32-s3` | ESP32-S3 | PCM5100 | 8 МБ | — |
| `hifi-esparagus-s3` | ESP32-S3 | PCM5100 | 8 МБ | — |
| `loud-esp32` | ESP32 | MAX98357A | 8 МБ | — |
| `loud-esp32-bt` | ESP32 | MAX98357A | 8 МБ | да |
| `loud-esparagus` | ESP32 | 2 × MAX98357A | 8 МБ | — |
| `loud-esparagus-bt` | ESP32 | 2 × MAX98357A | 8 МБ | да |
| `loud-esp32-s3` | ESP32-S3 | 2 × MAX98357A | 8 МБ | — |
| `esparagus-echo` | ESP32-S3 | 2 × MAX98357A | 8 МБ | — |
| `amped-esp32` | ESP32 | PCM5100 + TPA31xx | 8 МБ | — |
| `amped-esp32-bt` | ESP32 | PCM5100 + TPA31xx | 8 МБ | да |
| `amped-esparagus` | ESP32 | PCM5100 + TPA31xx | 8 МБ | — |
| `amped-esparagus-bt` | ESP32 | PCM5100 + TPA31xx | 8 МБ | да |
| `amped-esp32-s3` | ESP32-S3 | PCM5100 + TPA31xx | 8 МБ | — |
| `louder-esp32` | ESP32 | ТАС5805М | 8 МБ | — |
| `louder-esp32-bt` | ESP32 | ТАС5805М | 8 МБ | да |
| `louder-esp32-plus` | ESP32 | ТАС5825М | 8 МБ | — |
| `louder-esp32-plus-bt` | ESP32 | ТАС5825М | 8 МБ | да |
| `louder-esp32-s3` | ESP32-S3 | ТАС5805М | 8 МБ | — |
| `louder-esp32-s3-plus` | ESP32-S3 | ТАС5825М | 8 МБ | — |

<a id="targets-without-a-platformio-environment"></a>
## Цели без среды PlatformIO

Они имеют настройки по умолчанию sdkconfig и собираются напрямую через ESP-IDF.

| Цель | Сдкконфиг | Статус |
| --- | --- | --- |
| ESP32-S2 | `config/sdkconfig.defaults.esp32s2` | Встроенный в CI, опубликованный готовый образ |
| ESP32-P4 | `config/sdkconfig.defaults.esp32p4` | Экспериментальный |

```bash
idf.py set-target esp32s2
idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s2" build
```

<a id="which-builds-get-a-prebuilt-binary"></a>
## Для каких сред публикуются готовые образы

CI создает подмножество сред и присоединяет их к каждому выпуску. Это те
доступно в [установщике браузера](../getting-started/flashing.md):

`esp32s3`, `waveshare-esp32s3`, `esp32s2`, `squeezeamp-bt`, `squeezeamp-4m`, `smartamp`,
`esparagus-audio-brick-bt`, `esparagus-audio-brick-s3`, `esparagus-audio-brick-dual-dac`,
`esparagus-audio-brick-dual-uac`, `esparagus-louder-bt`, `esparagus-louder-s3`,
`esparagus-echo`, `hifi-esp32-bt`, `hifi-esparagus-bt`, `hifi-esp32-s3`,
`hifi-esparagus-s3`, `loud-esp32-bt`, `loud-esparagus-bt`, `loud-esp32-s3`,
`amped-esp32-bt`, `amped-esparagus-bt`, `amped-esp32-s3`, `louder-esp32-bt`,
`louder-esp32-plus-bt`, `louder-esp32-s3`, `louder-esp32-s3-plus`.

Список находится в `.github/workflows/targets.json`, и каждой записи требуется соответствие.
Манифест `docs/firmware/<name>.json`, который может предложить установщик.

Все остальное вы строите сами. На плате ESP32, поддерживающей Bluetooth, опубликованный
двоичный файл всегда включает его, поэтому готовых `squeezeamp`, `esparagus-audio-brick` нет,
`esparagus-louder`, `hifi-esp32`, `loud-esp32`, `amped-esp32` или `louder-esp32` — сборка
один из них, если вам нужна оперативная память и флэш-память.

Тот же список запускается при каждом нажатии на `staging` и публикует скользящий список.
[бета](../getting-started/flashing.md#beta-builds) предварительная версия, поэтому каждая из этих плат
также имеется непроверенная версия текущего совета по разработке. Создается запрос на включение
только записи с пометкой `"core": true`, которые охватывают каждый чип и каждую поддерживаемую плату.
каталог без задания на вариант, да и матрица быстро не выходит из строя, поэтому одна плата
неудачная компиляция больше не останавливает публикацию остальных.

<a id="how-sdkconfig-layering-works"></a>
## Как объединяются файлы sdkconfig

Вся конфигурация платы находится в **`config/`**. Сгенерированный `sdkconfig` остается на
корень проекта — это артефакт сборки и игнорируется git.

Среды составляют свою конфигурацию путем объединения файлов sdkconfig слева направо с помощью
более поздние файлы переопределяют более ранние:

```ini
board_build.cmake_extra_args =
    "-DSDKCONFIG_DEFAULTS=config/sdkconfig.defaults;config/sdkconfig.defaults.squeezeamp;config/sdkconfig.defaults.bt"
```

Здесь сначала идут общие настройки по умолчанию, затем конфигурация платы SqueezeAMP, а затем
Наложение Bluetooth. Добавление `config/sdkconfig.defaults.bt` в конец любой цепочки плат ESP32
как включается Bluetooth.

!!! warning "Удалить кэшированный файл sdkconfig после изменения настроек по умолчанию"

    Созданный файл `sdkconfig.<env>` кэшируется в корне проекта. Если вы измените какой-либо
    по умолчанию, удалите его перед пересборкой, иначе старые значения будут повторно использованы без уведомления.

<a id="common-commands"></a>
## Общие команды

```bash
pio run -e <env> -t build      # Build
pio run -e <env> -t upload     # Build and flash over USB
pio run -e <env> -t uploadfs   # Flash the SPIFFS image from data/
pio run -e <env> -t monitor    # Serial monitor at 115200 baud
pio run -e <env> -t menuconfig # Kconfig configuration
```

Чтобы определить собственную среду, не касаясь `platformio.ini`, см.
[Пользовательская конфигурация платы](../boards/custom.md).
