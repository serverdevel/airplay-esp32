[English](../../getting-started/flashing.md) | **Русский**

<a id="flash-the-firmware"></a>
# Установка прошивки

Опубликованная прошивка собирается и проверяется только для **ESP32-S3 N16R8** с
ЦАП **PCM5102A**, подключённым по схеме из [руководства по сборке](assembly.md).

> [!WARNING]
> Не устанавливайте этот образ на обычный ESP32, ESP32-S2, ESP32-C5, плату Waveshare,
> SqueezeAMP, Esparagus или другую готовую аудиоплату. Их профили унаследованы вместе
> с исходным кодом и не поддерживаются релизами этого форка.

| Способ | Когда использовать | Что понадобится |
| --- | --- | --- |
| **[A — Браузер](#option-a-install-from-your-browser)** | Первая установка на поддерживаемую плату | Chrome, Edge или Opera |
| **[B — PlatformIO](#option-b-platformio)** | Разработка прошивки | Python и локальная копия репозитория |
| **[C — ESP-IDF](#option-c-esp-idf)** | Вы уже работаете с ESP-IDF | ESP-IDF v5.5.5+ |

<a id="option-a-install-from-your-browser"></a>
## Вариант А — установка из браузера

Подключите ESP32-S3 N16R8 по USB и нажмите **«Установить»**.

!!! info "Требования"

    Установщик работает в настольных версиях Chrome, Edge и Opera через Web Serial API.
    Safari, Firefox, iOS и Android его не поддерживают.

<esp-web-install-button manifest="/airplay-esp32/firmware/esp32s3.json">
  <button slot="activate" class="md-button md-button--primary">Установить на ESP32-S3 N16R8</button>
  <span slot="unsupported">Ваш браузер не поддерживает прошивку по USB. Используйте Chrome, Edge или Opera на компьютере.</span>
  <span slot="not-allowed">Для прошивки требуется защищённое соединение HTTPS.</span>
</esp-web-install-button>

Пунктирная кнопка отображается только при наличии бета-образа для той же цели `esp32s3`.
Перед использованием прочитайте раздел [«Бета-версии»](#beta-builds).

<esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esp32s3.json">
  <button slot="activate" class="md-button md-button--beta">Установить бета-версию</button>
  <span slot="unsupported"></span>
  <span slot="not-allowed"></span>
</esp-web-install-button>

После установки отключите и снова подключите плату. Она запустится в режиме настройки —
переходите к разделу [«Первый запуск»](first-boot.md).

<a id="beta-builds"></a>
### Бета-версии

Бета-образ собирается из последнего состояния ветки `staging`. Он предназначен для
проверки конкретного исправления до следующего релиза и может не загрузиться. Повторная
установка последней стабильной версии `esp32s3` возвращает плату в рабочее состояние.

!!! note "Предпочитаете ручную прошивку?"

    Скачайте файл `airplay2-receiver-esp32s3-*-full.bin` из
    [последнего релиза](https://github.com/serverdevel/airplay-esp32/releases/latest) и
    запишите его со смещения **`0x0`** с помощью `esptool` или
    [веб-инструмента esptool-js](https://espressif.github.io/esptool-js/).

    В релиз также входят `*-ota.bin` для обновления через веб-интерфейс устройства и
    отдельный образ файловой системы `*-spiffs.bin`.

<a id="option-b-platformio"></a>
## Вариант Б — PlatformIO

[PlatformIO](https://platformio.org/) автоматически настраивает набор инструментов.

```bash
# 1. Установите PlatformIO CLI
pip install platformio

# 2. Клонируйте этот форк вместе с подмодулями
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32

# 3. Запишите прошивку
pio run -e esp32s3 -t upload

# 4. Запишите SPIFFS с веб-интерфейсом и файлами данных
pio run -e esp32s3 -t uploadfs

# 5. При необходимости откройте последовательный журнал
pio run -e esp32s3 -t monitor
```

!!! warning "Шаг 4 обязателен"

    PlatformIO **не** записывает SPIFFS как часть `-t upload`. Без `-t uploadfs`
    устройство загрузится, но портал настройки и веб-интерфейс будут отсутствовать.

<a id="option-c-esp-idf"></a>
## Вариант C — ESP-IDF

```bash
# Сначала установите и активируйте ESP-IDF v5.5.5 или новее
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32
source /path/to/esp-idf/export.sh

idf.py set-target esp32s3
idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s3" build
idf.py -p /dev/ttyUSB0 flash
idf.py -p /dev/ttyUSB0 monitor
```

В отличие от PlatformIO, `idf.py flash` записывает раздел SPIFFS в той же операции.

<a id="next"></a>
## Дальше

Перейдите к [первому запуску](first-boot.md).
