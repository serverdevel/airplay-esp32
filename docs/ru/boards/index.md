[English](../../boards/index.md) | **Русский**

<a id="supported-boards"></a>
# Поддержка оборудования

<a id="official-release-target"></a>
## Официальная конфигурация релиза

Этот форк публикует и проверяет готовую прошивку только для одной конфигурации:

| Плата | Память | Аудиовыход | Образ в релизе | Статус |
| --- | --- | --- | :-: | --- |
| [ESP32-S3 N16R8 + PCM5102A](esp32s3-pcm5102a.md) | 16 МБ flash, 8 МБ octal PSRAM | Внешний I2S-ЦАП | да | **Поддерживается и проверяется** |

Используется распиновка GPIO10–GPIO14 и положение перемычек, описанное в
[руководстве по сборке](../getting-started/assembly.md). Другие варианты памяти и
распиновки ESP32-S3 не являются взаимозаменяемыми с опубликованным образом.

!!! warning "Проверьте маркировку модуля"

    Для релиза нужен модуль **N16R8**. Надписи «ESP32-S3» недостаточно: плата с меньшим
    объёмом flash, без PSRAM или с другим режимом PSRAM может не загрузиться либо
    столкнуться с нехваткой памяти.

<a id="inherited-source-profiles"></a>
## Унаследованные профили исходного кода

В репозитории сохранены следующие профили основного проекта. Они могут пригодиться как
примеры портирования и всё ещё могут собираться, но этот форк их **не тестирует, не
публикует для них готовые образы и не предоставляет поддержку оборудования**:

- [SqueezeAMP](squeezeamp.md)
- [Esparagus Audio Brick и Esparagus Louder](esparagus-audio-brick.md)
- [Esparagus Audio Brick Dual](esparagus-audio-brick-dual-dac.md)
- [HiFi-ESP32 и HiFi-Esparagus](hifi-esp32.md)
- [Loud-ESP32, Loud-Esparagus и Esparagus Echo](loud-esp32.md)
- [Amped-ESP32 и Amped-Esparagus](amped-esp32.md)
- [Louder-ESP32](louder-esp32.md)
- [Seeed XIAO ESP32-C5](xiao-esp32c5.md)
- ESP32-S2, Waveshare ESP32-S3, ESP32-WROVER и пользовательские профили

Используйте их только при готовности самостоятельно собрать прошивку, найти проблемы,
связанные с конкретной платой, и проверить результат. Наличие профиля в `platformio.ini`
или `config/` не означает, что он является поддерживаемой целью релиза.

<a id="full-build-environment-list"></a>
## Полный список сред сборки

Унаследованные профили PlatformIO и ESP-IDF перечислены в разделе
[«Среды сборки»](../reference/build-environments.md).
