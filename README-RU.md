[English](README.md) | **Русский**

<div align="center">

<img src="docs/assets/logo_airplay_esp32.png" alt="AirPlay ESP32" width="400">

# AirPlay 2-приёмник на ESP32

**Добавьте AirPlay 2 к домашней аудиосистеме с помощью ESP32-S3 N16R8 и ЦАП PCM5102A**

[![Звёзды GitHub](https://img.shields.io/github/stars/serverdevel/airplay-esp32?style=flat-square)](https://github.com/serverdevel/airplay-esp32/stargazers)
[![Форки GitHub](https://img.shields.io/github/forks/serverdevel/airplay-esp32?style=flat-square)](https://github.com/serverdevel/airplay-esp32/network)
[![Лицензия](https://img.shields.io/badge/license-Non--Commercial-blue?style=flat-square)](LICENSE)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.5+-red?style=flat-square)](https://docs.espressif.com/projects/esp-idf/)
[![Платформа](https://img.shields.io/badge/platform-ESP32--S3%20N16R8-green?style=flat-square)](https://www.espressif.com/en/products/socs/esp32-s3)

### [Документация](docs/ru/index.md) · [Установка из браузера](docs/ru/getting-started/flashing.md) · [Устранение неполадок](docs/ru/troubleshooting.md)

</div>

---

## Что это такое?

Эта прошивка превращает недорогую плату ESP32 в беспроводной динамик AirPlay 2.
Подключите её к усилителю или активным колонкам — устройство появится на iPhone,
iPad или Mac так же, как HomePod или телевизор с AirPlay.

<p align="center">
  <img src="docs/assets/build/esp32-pcm5102a-complete.jpg"
       alt="Собранный AirPlay-приёмник на ESP32-S3 и PCM5102A" width="720">
</p>

Готовые релизы этого форка собираются и проверяются только для **ESP32-S3 N16R8**
(16 МБ flash и 8 МБ octal PSRAM), подключённой к ЦАП **PCM5102A** по указанной ниже
распиновке.

В репозитории сохранены унаследованные от исходного проекта профили сборки для других
чипов ESP32 и готовых аудиоплат. В этом форке они не тестируются, не входят в релизы
и официально не поддерживаются.

**Без облака. Без отдельного приложения. Просто выберите устройство и включите музыку.**

## Быстрый старт

Самый простой способ — установить прошивку прямо из браузера, без командной строки
и настройки среды разработки:

**[→ Установить из браузера](docs/ru/getting-started/flashing.md)**

Для самостоятельной сборки понадобятся плата ESP32-S3 N16R8, ЦАП PCM5102A,
шестиконтактная штырьковая гребёнка и базовые инструменты для пайки. Общая
стоимость деталей — около 10 долларов. Подробности приведены в
[инструкции по сборке](docs/ru/getting-started/assembly.md).

Сборка из исходного кода:

```bash
git clone --recursive https://github.com/serverdevel/airplay-esp32
cd airplay-esp32
pio run -e esp32s3 -t upload
pio run -e esp32s3 -t uploadfs   # required — writes the web UI to SPIFFS
```

## Корпус для 3D-печати

В репозитории находятся корпус для сборки ESP32-S3 + PCM5102A и две задние
крышки. Наружная поверхность крышек имеет размер **35 × 22 мм** и стыкуется с
корпусом без ступеньки.

| Модель | Скачать | Посадка |
| --- | --- | --- |
| Корпус | [esp32-airplay-enclosure.stl](docs/assets/3d-models/esp32-airplay-enclosure.stl) | Основная деталь |
| Стандартная задняя крышка | [esp32-airplay-rear-cover-standard.stl](docs/assets/3d-models/esp32-airplay-rear-cover-standard.stl) | Зазор направляющих 0,30 мм; рекомендуется печатать первой |
| Плотная задняя крышка | [esp32-airplay-rear-cover-tight.stl](docs/assets/3d-models/esp32-airplay-rear-cover-tight.stl) | Зазор направляющих 0,20 мм |

Печатайте крышку плоской наружной стороной на столе, направляющими вверх.
Дополнительные рекомендации находятся в [инструкции по сборке](docs/ru/getting-started/assembly.md#step-5-print-the-case-optional).

## Возможности

- **AirPlay 2** — устройство отображается в Пункте управления и приложениях с поддержкой AirPlay;
- **интеграция с Apple Home («Дом»)** — приёмник добавляется в «Дом», принимает
  воспроизведение с HomePod и сохраняет сопряжение после перезагрузки;
- **декодирование ALAC и AAC** — музыка, звонки и трансляции в реальном времени;
- **мультирум** — синхронизация воспроизведения по PTP;
- **компенсация акустической задержки** — настройка от −1000 до +1000 мс через
  веб-интерфейс для совмещения звука с HomePod; применяется сразу и сохраняется;
- **веб-интерфейс и OTA-обновления** — USB нужен только для первой прошивки;
- **выход 48 кГц** — дополнительное преобразование 44,1 → 48 кГц sinc-ресемплером;
- **дисплеи** — OLED или цветной TFT 320 × 170 с информацией о треке;
- **аппаратные кнопки** — воспроизведение, пауза, громкость и переключение треков.

Поддерживается один аудиовыход на плату; для стабильной работы требуется хороший
сигнал Wi-Fi.

## Документация

| Раздел | Содержание |
| --- | --- |
| [Начало работы](docs/ru/getting-started/index.md) | Покупка деталей, сборка, прошивка и первый запуск |
| [Оборудование](docs/ru/boards/index.md) | Официальная сборка ESP32-S3 N16R8 и непроверенные унаследованные профили |
| [Функции](docs/ru/features/airplay-tuning.md) | Дисплеи, кнопки и настройка AirPlay |
| [Справочник](docs/ru/reference/build-environments.md) | Среды сборки, SPIFFS, OTA и архитектура |
| [Устранение неполадок](docs/ru/troubleshooting.md) | Нет звука, не появляется сеть настройки, обрывы и ошибки сборки |

## Участие в разработке

См. [CONTRIBUTING.md](CONTRIBUTING.md) и русскую
[инструкцию для участников](docs/ru/contributing.md). Документация находится в
каталоге [`docs/`](docs/) и собирается с помощью [Zensical](https://zensical.org/).

## Благодарности

- [Shairport Sync](https://github.com/mikebrady/shairport-sync) — эталонная реализация AirPlay;
- [openairplay/airplay2-receiver](https://github.com/openairplay/airplay2-receiver) — реализация AirPlay 2 на Python;
- [Espressif](https://github.com/espressif) — платформа ESP-IDF и библиотеки кодеков.

## Правовая информация

**Только для некоммерческого использования.** Коммерческое использование требует
явного разрешения — см. [LICENSE](LICENSE).

Это независимый проект, созданный на основе анализа протокола и не связанный с
Apple Inc. Совместимость с будущими версиями iOS и macOS не гарантируется.
Проект предоставляется «как есть», без каких-либо гарантий.
