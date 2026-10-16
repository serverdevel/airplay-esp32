[English](../../boards/squeezeamp.md) | **Русский**

<a id="squeezeamp"></a>
# SqueezeAMP

!!! warning "Унаследованный непроверенный профиль"

    Эта страница описывает исходный код, унаследованный от основного проекта. Данный
    форк не тестирует эту плату, не публикует для неё готовый образ и не предоставляет
    официальную поддержку. Самостоятельная сборка и проверка выполняются на ваш риск.

[SqueezeAMP](https://github.com/philippe44/SqueezeAMP) — это плата ESP32 с
TAS575xx (комбинированный ЦАП и усилитель класса D). Подключите динамики
прямо на плату.

<a id="flashing"></a>
## Прошивка

=== "Образ релиза"

    Этот форк не публикует готовый образ. Соберите и проверьте профиль самостоятельно.

=== "PlatformIO"

    ```bash
    # AirPlay only
    pio run -e squeezeamp -t upload
    pio run -e squeezeamp -t uploadfs

    # AirPlay + Bluetooth A2DP
    pio run -e squeezeamp-bt -t upload
    pio run -e squeezeamp-bt -t uploadfs
    ```

=== "ESP-IDF"

    ```bash
    idf.py set-target esp32
    idf.py -DSDKCONFIG_DEFAULTS="config/sdkconfig.defaults;config/sdkconfig.defaults.squeezeamp" build
    idf.py -p /dev/ttyUSB0 flash
    ```

`idf.py flash` также записывает раздел SPIFFS `storage` из `data/`, поэтому
    Страницы captive-портала присутствуют при первой загрузке.

<a id="build-variants"></a>
## Варианты сборки

| Среда сборки | Флэш | Bluetooth | Заметки |
| --- | --- | :-: | --- |
| `squeezeamp` | 8 МБ | — | Только AirPlay |
| `squeezeamp-bt` | 8 МБ | да | Образ не публикуется |
| `squeezeamp-4m` | 4 МБ | — | Уменьшенная таблица разделов; образ не публикуется |

Bluetooth не помещается рядом с AirPlay в 4 МБ флэш-памяти, поэтому нет
`squeezeamp-4m-bt`.

<a id="what-the-build-configures"></a>
## Что настраивает сборка

Сборка SqueezeAMP автоматически выбирает драйвер ЦАП TAS57xx через Kconfig.
(`CONFIG_DAC_TAS57XX`) и устанавливает правильные контакты I2S и I2C. Аудио буферы уменьшены
от 5000 до 2500 кадров, чтобы соответствовать более ограниченной пропускной способности PSRAM оригинального ESP32.

<a id="hybrid-flow-dsp"></a>
## Гибридный поток DSP

TAS5754M процессора SqueezeAMP имеет ядро miniDSP, поэтому он может запускать процесс **HybridFlow** компании TI.
поток: полнодиапазонная стереоцепь с эквалайзером, усилением басов и компандером или двухполосная
двухамперный кроссовер. Прошивка поставляет базовые потоки и настраивает их в реальном времени с
Страница `/hf`.

TAS5754M — это часть, на которой все это было протестировано. См.
[HybridFlow DSP](../features/hybridflow.md) для потоков, рабочего процесса настройки и
макет файла.

!!! note

    Для HybridFlow требуется TAS57xx с miniDSP. Драйвер определяет семейство чипов при загрузке
    и пропускает потоковую загрузку на устройствах TAS578x, у которых нет ядра DSP.

См. [Файловая система SPIFFS](../reference/spiffs.md) для API управления файлами.

<a id="related"></a>
## См. также

- [HybridFlow DSP](../features/hybridflow.md)
- [Bluetooth A2DP](../features/bluetooth.md)
- [Среды сборки](../reference/build-environments.md)
