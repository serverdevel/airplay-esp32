[English](../../boards/custom.md) | **Русский**

<a id="custom-board-configuration"></a>
# Пользовательская конфигурация платы

Если вы выполняете портирование на собственное оборудование, вы можете определить собственную среду сборки без
касаясь `platformio.ini`. Создайте файл **`user_platformio.ini`** — основной конфиг.
уже подхватывает его через `extra_configs`, поэтому PlatformIO подхватывает его автоматически.

<a id="how-it-works"></a>
## Как это работает

1. Выберите существующую среду для расширения, например `esp32s3` или `esp32wrover-dev`.
2. Создайте файл `config/sdkconfig.user.<your_board>`, содержащий Kconfig для вашей платы.
   переопределяет: контакты GPIO, выбор ЦАП, настройки дисплея и так далее.
3. Добавьте в `user_platformio.ini` среду, которая связывает ваш файл sdkconfig после
   базовые настройки по умолчанию.

<a id="example"></a>
## Пример

Предположим, у вас есть специальная плата ESP32 под названием «myboard» с ЦАП SqueezeAMP-compatible, но
различные назначения GPIO и OLED-дисплей. Создайте два файла.

`config/sdkconfig.user.myboard` — переопределения для вашей платы:

```ini
# I2S pin assignments
CONFIG_I2S_BCK_PIN=5
CONFIG_I2S_WS_PIN=18
CONFIG_I2S_DO_PIN=19

# Enable OLED display
CONFIG_DISPLAY_ENABLED=y
CONFIG_DISPLAY_I2C_SDA=21
CONFIG_DISPLAY_I2C_SCL=22
```

`user_platformio.ini` — ваша среда сборки:

```ini
[env:myboard]
extends = env:esp32s3
board_build.cmake_extra_args =
    "-DSDKCONFIG_DEFAULTS=config/sdkconfig.defaults;config/sdkconfig.defaults.esp32s3;config/sdkconfig.user.myboard"
```

Затем соберите и прошейте:

```bash
pio run -e myboard -t upload
pio run -e myboard -t uploadfs
```

<a id="notes"></a>
## Примечания

- Значения Sdkconfig по умолчанию применяются **слева направо** — более поздние файлы переопределяют более ранние, поэтому
  ваш `config/sdkconfig.user.*` должен быть последним.
— Файлы `config/sdkconfig.user.*` игнорируются git, поэтому не будут загрязнять репозиторий.
- Если вы измените какие-либо настройки sdkconfig по умолчанию, удалите кэшированный файл `sdkconfig.<env>` перед этим.
  перестроение, в противном случае старые значения будут использоваться повторно.
- Вы можете расширить любую базовую среду: используйте `squeezeamp` или `squeezeamp-bt` для TAS57xx.
  платы `esparagus-audio-brick` или `esparagus-audio-brick-bt` для плат TAS58xx и
  `esp32s3` для плат на базе S3.

<a id="related"></a>
## См. также

- [Среды сборки](../reference/build-environments.md)
- [Архитектура](../reference/architecture.md)
