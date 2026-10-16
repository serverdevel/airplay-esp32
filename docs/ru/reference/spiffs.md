[English](../../reference/spiffs.md) | **Русский**

<a id="spiffs-filesystem"></a>
# Файловая система SPIFFS

Прошивка хранит свои веб-страницы и файлы конфигурации DAC в разделе **SPIFFS** в
flash, поэтому вы можете обновлять веб-интерфейс и программы DSP без перекомпиляции.

<a id="partition-layout"></a>
## Расположение разделов

В таблицу разделов добавляется раздел `storage`:

| Совет | Размер раздела | Адрес |
| --- | --- | --- |
| SqueezeAMP (8 МБ или более) | 316 КБ | 0x5B1000 |
| SqueezeAMP 4M | 192 КБ | 0x3D1000 |

Он монтируется по адресу `/spiffs` при загрузке.

<a id="data-directory"></a>
## Каталог данных

`data/` в корне проекта содержит файлы, которые передаются в раздел:

```text
data/
├── www/               # Web interface pages
│   ├── index.html     # Setup and control panel
│   ├── logs.html      # Live log viewer
│   ├── bq.html        # Parametric biquad chains (TAS5825M boards)
│   ├── hf.html        # Hybrid flow tuning (SqueezeAMP)
│   └── speedtest.html # Network throughput test
├── hf/                # DSP programs loaded at boot
│   ├── base-hf1-44100.bin  # Hybrid flow 1 base image (SqueezeAMP)
│   ├── base-hf3-44100.bin  # Hybrid flow 3 base image (SqueezeAMP)
│   └── tas5825m_fw-44100.bin # PPC3 dump, if you supply one (TAS5825M boards)
└── bg/                # ST7789 background image
    └── background.bin  # if you supply one
```

Имена `hf/` содержат частоту дискретизации, для которой было создано изображение DSP, и 48000 двойных посадочных мест.
рядом с каждым. С репозиторием поставляются только базовые образы гибридного потока; дамп PPC3 это
ваше экспортируйте и закидывайте, как и фоновое изображение — в 106 КБ оно не помещается
вместе с веб-интерфейсом на плате размером 4 МБ.

<a id="compression"></a>
## Сжатие

`data/` не прошивается дословно. `scripts/gen_spiffs_image.py` сначала размещает его и сжимает в архив.
каждый `.html`, поэтому изображение содержит `index.html.gz`, а не `index.html`. Это требует
полезная нагрузка с 256 КБ до 101 КБ, что важно, поскольку самый маленький макет дает только SPIFFS
188 КБ — одни страницы переполняют его в несжатом виде. Страницы также загружаются заметно быстрее
WiFi.

В образе всегда хранится только `.gz`, поэтому веб-сервер сначала пробует простое имя и падает.
вернемся к `<path>.gz`, установив `Content-Encoding: gzip`, когда он обслуживает один; браузеры
прозрачно распаковать. Именно этот порядок делает `/api/fs/upload` полезным — загруженный
`index.html` заменяет отправленную страницу, а ее повторное удаление восстанавливает встроенную
один. Двоичные файлы `hf/` и `bg/` считываются ЦАП напрямую из файловой системы и
драйверы дисплея, которые не могут быть распакованы, поэтому они копируются нетронутыми.

Промежуточный этап также удаляет то, что сборка не может использовать. Оба драйвера ЦАП сохраняют свои изображения DSP в
`hf/`, поэтому каждая сборка содержит только то семейство, которое она может загрузить: `base-hf*.bin` и
`tas57xx_fw*.bin` нужен `CONFIG_DAC_TAS57XX`, `tas5825m_fw*.bin` нужен `CONFIG_DAC_TAS58XX`.
Это возвращает еще 24 КБ любой плате без TAS57xx, увеличивая размер образа до 78 КБ.

Обе системы сборки проходят этот этап подготовки. ESP-IDF запускает его из `CMakeLists.txt`.
перед `spiffs_create_partition_image` и PlatformIO, которые скорее упаковывают сам `data/`
чем использовать сборки образа CMake — запускает его из `scripts/pio_stage_spiffs.py`, подключенного как
крючок `extra_scripts`. Итак, `idf.py flash`, `pio run -t uploadfs` и предварительно собранная версия.
все двоичные файлы имеют одну и ту же файловую систему.

<a id="flashing-the-image"></a>
## Запись образа

!!! warning "PlatformIO не сделает это за вас"

    `pio run -t upload` пишет только прошивку. Без отдельного `-t uploadfs`
    устройство загружается, но Captive-портал и веб-интерфейс отсутствуют, что отображается как
    "Файл не найден" во время установки. Это самая распространенная проблема установки.

```bash
# PlatformIO — firmware first, then the filesystem
pio run -e <env> -t upload
pio run -e <env> -t uploadfs

# ESP-IDF — firmware, partition table and SPIFFS in one step
idf.py -p /dev/ttyUSB0 flash
```

**Обновление сборки без раздела хранения** должно выполняться через последовательный порт.
меняется сама таблица разделов, и OTA не может ее переписать.

Как только раздел существует, вы можете обновлять отдельные файлы через WiFi с помощью API, представленного ниже, или
перепрошить весь образ по серийнику.

<a id="file-management-api"></a>
## API управления файлами

Три конечных точки HTTP управляют файлами SPIFFS через WiFi без перепрошивки.

**Загрузить файл:**

```bash
curl -X POST "http://<device-ip>/api/fs/upload?path=/spiffs/hf/my_flow.bin" \
     --data-binary @my_flow.bin
```

**Удалить файл:**

```bash
curl -X POST "http://<device-ip>/api/fs/delete?path=/spiffs/hf/old_flow.bin"
```

**Укажите каталог:**

```bash
curl "http://<device-ip>/api/fs/list?dir=/spiffs/hf"
```

Пути ограничены `/spiffs/`, а обход каталога через `..` отклоняется.
максимальный размер загрузки — 64 КБ.

<a id="what-lives-on-spiffs"></a>
## Что хранится в SPIFFS

| Путь | Используется |
| --- | --- |
| `/spiffs/www/` | Веб-сервер — портал настройки, логи, эквалайзер |
| `/spiffs/hf/base-hf<n>-<rate>.bin` | [HybridFlow DSP](../features/hybridflow.md) |
| `/spiffs/hf/tas5825m_fw-<rate>.bin` | [Полная настройка PPC3](../boards/esparagus-audio-brick.md#full-ppc3-tuning) |
| `/spiffs/bg/background.bin` | [Фоновое изображение ST7789](../features/tft-display.md#background-image) |
