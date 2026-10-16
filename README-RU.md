[English](README.md) | **Русский**

<div align="center">

<img src="docs/assets/logo_airplay_esp32.png" alt="AirPlay ESP32" width="400">

# AirPlay 2-приёмник на ESP32

**Передавайте музыку с устройств Apple или любого телефона через Bluetooth на любые колонки примерно за 10 долларов**

[![Звёзды GitHub](https://img.shields.io/github/stars/rbouteiller/airplay-esp32?style=flat-square)](https://github.com/rbouteiller/airplay-esp32/stargazers)
[![Форки GitHub](https://img.shields.io/github/forks/rbouteiller/airplay-esp32?style=flat-square)](https://github.com/rbouteiller/airplay-esp32/network)
[![Лицензия](https://img.shields.io/badge/license-Non--Commercial-blue?style=flat-square)](LICENSE)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v5.5+-red?style=flat-square)](https://docs.espressif.com/projects/esp-idf/)
[![Платформа](https://img.shields.io/badge/platform-ESP32%20%7C%20S2%20%7C%20S3%20%7C%20C5-green?style=flat-square)](https://www.espressif.com/en/products/socs)

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

Поддерживаются **ESP32**, **ESP32-S2**, **ESP32-S3** и **ESP32-C5**, включая
[SqueezeAMP](https://github.com/philippe44/SqueezeAMP) на ESP32 с TAS5756 и
[Esparagus Audio Brick](https://sonocotta.com/espragus-audio-brick/) на ESP32 с
TAS5825M — эти платы уже содержат усилитель.

Платы на классическом ESP32 также поддерживают **Bluetooth A2DP**, поэтому на них
можно передавать звук с любого телефона или планшета, когда AirPlay не используется.
Esparagus Audio Brick дополнительно поддерживает проводную сеть через модуль W5500.

**Без облака. Без отдельного приложения. Просто выберите устройство и включите музыку.**

## Быстрый старт

Самый простой способ — установить прошивку прямо из браузера, без командной строки
и настройки среды разработки:

**[→ Установить из браузера](docs/ru/getting-started/flashing.md)**

Для самостоятельной сборки понадобятся плата ESP32-S3, ЦАП PCM5102A,
шестиконтактная штырьковая гребёнка и базовые инструменты для пайки. Общая
стоимость деталей — около 10 долларов. Подробности приведены в
[инструкции по сборке](docs/ru/getting-started/assembly.md).

Сборка из исходного кода:

```bash
git clone --recursive https://github.com/rbouteiller/airplay-esp32
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
- **декодирование ALAC и AAC** — музыка, звонки и трансляции в реальном времени;
- **мультирум** — синхронизация воспроизведения по PTP;
- **Bluetooth A2DP** — приём звука с телефонов и планшетов на платах ESP32;
- **Ethernet W5500** — проводная сеть с автоматическим переключением на Wi-Fi;
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
| [Поддерживаемые платы](docs/ru/boards/index.md) | SqueezeAMP, Esparagus Audio Brick, XIAO ESP32-C5 и пользовательские платы |
| [Функции](docs/ru/features/bluetooth.md) | Bluetooth, Ethernet, дисплеи, кнопки и настройка AirPlay |
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
