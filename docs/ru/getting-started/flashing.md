[English](../../getting-started/flashing.md) | **Русский**

<a id="flash-the-firmware"></a>
# Установка прошивки

Прошивку можно установить тремя способами. Если вам не нужен конкретный инструмент,
используйте установщик в браузере.

| Способ | Когда использовать | Что понадобится |
| --- | --- | --- |
| **[A — Браузер](#option-a-install-from-your-browser)** | Вам просто нужен работающий динамик | Chrome, Edge или Opera |
| **[B — PlatformIO](#option-b-platformio)** | Нужно изменить параметры сборки или для платы нет готового образа | Python и локальная копия репозитория |
| **[C — ESP-IDF](#option-c-esp-idf)** | Вы уже работаете с ESP-IDF | ESP-IDF v5.5.5+ |

<a id="option-a-install-from-your-browser"></a>
## Вариант А — установка из браузера

Выберите плату и нажмите «Установить». Ничего скачивать не нужно: не потребуются ни
среда разработки, ни командная строка.

!!! info "Требования"

    Установщик работает в настольных версиях Chrome, Edge и Opera. Он использует
    Web Serial API, которого нет в Safari, Firefox, iOS и Android. Перед нажатием
    кнопки «Установить» подключите плату по USB.

Для каждой платы есть кнопка **Установить** с последним стабильным выпуском. Рядом
расположена пунктирная кнопка **Установить бета-версию** со сборкой текущей ветки
`staging`. Перед её использованием прочитайте раздел [«Бета-версии»](#beta-builds).

<a id="generic-boards"></a>
### Универсальные платы

<div class="grid cards" markdown>

-   __ESP32-S3 + внешний ЦАП__

    Стандартная сборка для ESP32-S3 с PCM5102A или другим I2S-ЦАП.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esp32s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esp32s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __ESP32-S2 + внешний ЦАП__

    Для плат ESP32-S2 с внешним I2S-ЦАП.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esp32s2.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esp32s2.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Waveshare ESP32-S3__

    Для плат Waveshare ESP32-S3.

    <esp-web-install-button manifest="/airplay-esp32/firmware/waveshare-esp32s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/waveshare-esp32s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="amplifier-boards"></a>
### Платы усилителей

<div class="grid cards" markdown>

-   __SqueezeAMP__

    ESP32 + TAS5756. Поддерживает Bluetooth A2DP. Для плат с 8 МБ флеш-памяти.

    <esp-web-install-button manifest="/airplay-esp32/firmware/squeezeamp-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/squeezeamp-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __SqueezeAMP (флэш-память 4 МБ)__

    Для варианта с 4 МБ флеш-памяти. Bluetooth не включён: для него недостаточно места.

    <esp-web-install-button manifest="/airplay-esp32/firmware/squeezeamp-4m.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/squeezeamp-4m.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __SmartAmp__

    ESP32 + Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/smartamp.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/smartamp.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="esparagus-boards"></a>
### Платы Esparagus

На каждой плате Esparagus установлен усилитель **TAS58xx** — TAS5825M или TAS5805M.
Модель определяется при запуске, поэтому один образ подходит для обоих вариантов.
Платы Audio Brick также оснащены Ethernet-контроллером W5500. Bluetooth A2DP доступен
только на оригинальном ESP32.

<div class="grid cards" markdown>

-   __Esparagus Audio Brick__

    ESP32 + TAS58xx. Включает Bluetooth A2DP и ​​W5500 Ethernet.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-audio-brick-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-audio-brick-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Audio Brick S3__

    ESP32-S3 + TAS58xx, с W5500 Ethernet.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-audio-brick-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-audio-brick-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Audio Brick Dual__

    ESP32-S3 + два усилителя: стерео плюс мостовой моно сабвуфер.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-audio-brick-dual-dac.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-audio-brick-dual-dac.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Audio Brick Dual + аудио USB__

    Dual, также обозначаемый как динамик USB. См. [аудио USB](../features/usb-audio.md).

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-audio-brick-dual-uac.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-audio-brick-dual-uac.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Louder__

    ESP32 + TAS58xx. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-louder-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-louder-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Louder S3__

    ESP32-S3 + TAS58xx.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-louder-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-louder-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="hifi-boards"></a>
### HiFi-платы

[HiFi-ESP32 и HiFi-Esparagus](../boards/hifi-esp32.md) оснащены ЦАП **PCM5100**
с линейным выходом, но без усилителя: их подключают к внешнему усилителю или активным
колонкам. У плат `-ESP32` есть Ethernet W5500 и OLED, у вариантов Esparagus — нет.

<div class="grid cards" markdown>

-   __HiFi-ESP32__

    ESP32 + PCM5100, Ethernet и OLED. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/hifi-esp32-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/hifi-esp32-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __HiFi-Esparagus__

    Только ESP32 + PCM5100, WiFi. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/hifi-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/hifi-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __HiFi-ESP32-S3__

    ESP32-S3 + PCM5100, Ethernet и OLED.

    <esp-web-install-button manifest="/airplay-esp32/firmware/hifi-esp32-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/hifi-esp32-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __HiFi-Esparagus-S3__

    Только ESP32-S3 + PCM5100, WiFi.

    <esp-web-install-button manifest="/airplay-esp32/firmware/hifi-esparagus-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/hifi-esparagus-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="loud-and-echo-boards"></a>
### Платы Loud и Echo

[Loud-ESP32, Loud-Esparagus и Esparagus Echo](../boards/loud-esp32.md) напрямую
управляют усилителями **MAX98357A** — динамики подключаются к самой плате.

<div class="grid cards" markdown>

-   __Loud-ESP32__

    ESP32 + MAX98357A, Ethernet и OLED. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/loud-esp32-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/loud-esp32-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Loud-Esparagus__

    Только ESP32 + двойной MAX98357A, WiFi. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/loud-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/loud-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Loud-ESP32-S3__

    ESP32-S3 + двойной MAX98357A, Ethernet и OLED.

    <esp-web-install-button manifest="/airplay-esp32/firmware/loud-esp32-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/loud-esp32-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Esparagus Echo__

    ESP32-S3 + двойной MAX98357A, Ethernet, без дисплея.

    <esp-web-install-button manifest="/airplay-esp32/firmware/esparagus-echo.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/esparagus-echo.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="amped-boards"></a>
### Платы Amped

В [Amped-ESP32 и Amped-Esparagus](../boards/amped-esp32.md) ЦАП **PCM5100** установлен
перед усилителем **TPA3110/TPA3128**. Динамики подключаются к самой плате.

<div class="grid cards" markdown>

-   __Amped-ESP32__

    ESP32 + PCM5100 + TPA31xx, Ethernet и OLED. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/amped-esp32-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/amped-esp32-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Amped-Esparagus__

    ESP32 rev M, Ethernet и поворотный энкодер. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/amped-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/amped-esparagus-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Amped-ESP32-S3__

    ESP32-S3 + PCM5100 + TPA31xx, Ethernet и OLED.

    <esp-web-install-button manifest="/airplay-esp32/firmware/amped-esp32-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/amped-esp32-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

<a id="louder-boards"></a>
### Платы Louder

[Louder-ESP32](../boards/louder-esp32.md) оснащены ЦАП и усилителем **TAS58xx**.
В вариантах **Plus** установлен TAS5825M, в обычных — TAS5805M. Выберите карточку,
которая соответствует вашей плате: распиновка у них различается.

<div class="grid cards" markdown>

-   __Louder-ESP32__

    ESP32 + TAS5805M, Ethernet и OLED. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/louder-esp32-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/louder-esp32-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Louder-ESP32-Plus__

    ESP32 + TAS5825M, Ethernet и OLED. Включает Bluetooth A2DP.

    <esp-web-install-button manifest="/airplay-esp32/firmware/louder-esp32-plus-bt.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/louder-esp32-plus-bt.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Louder-ESP32-S3__

    ESP32-S3 + TAS5805M, Ethernet и OLED.

    <esp-web-install-button manifest="/airplay-esp32/firmware/louder-esp32-s3.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/louder-esp32-s3.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

-   __Louder-ESP32-S3-Plus__

    ESP32-S3 + TAS5825M, Ethernet и OLED.

    <esp-web-install-button manifest="/airplay-esp32/firmware/louder-esp32-s3-plus.json">
      <button slot="activate" class="md-button md-button--primary">Установить</button>
      <span slot="unsupported">Ваш браузер не может прошить USB. Используйте Chrome, Edge или Opera на компьютере.</span>
      <span slot="not-allowed"> Для прошивки требуется безопасное (HTTPS) соединение. </span>
    </esp-web-install-button><esp-web-install-button class="install-beta" manifest="/airplay-esp32/firmware/beta/louder-esp32-s3-plus.json">
      <button slot="activate" class="md-button md-button--beta">Установить бета-версию </button>
      <span slot="unsupported"></span>
      <span slot="not-allowed"></span>
    </esp-web-install-button>

</div>

После завершения установки отключите и снова подключите плату. Она загрузится в режиме
настройки — переходите к разделу [«Первый запуск»](first-boot.md).

<a id="beta-builds"></a>
### Бета-версии

Пунктирные кнопки **Установить бета-версию** устанавливают последнюю сборку ветки
`staging`, которая обновляется при каждом изменении. Исправления сначала попадают
именно туда, поэтому бета-версия позволяет проверить новое исправление или убедиться,
что обнаруженная вами ошибка устранена.

Это ещё не выпущенный код. Бета-версии собираются тем же CI, что и стабильные релизы,
но могут быть не проверены на реальном оборудовании. Если устройство не загрузилось,
[сообщите об этом](https://github.com/rbouteiller/airplay-esp32/issues). Повторная
установка стабильной версии всегда возвращает плату в рабочее состояние.

Кнопка отображается только при наличии соответствующей сборки. Поэтому между
обновлениями ветки `staging` кнопки бета-версий могут временно отсутствовать. Для платы,
добавленной после последнего релиза, до следующего выпуска может быть доступна только бета-версия.

!!! note "Предпочитаете ручную прошивку?"

    Каждая перечисленная выше сборка также публикуется в виде объединённого файла `.bin`:
    стабильные версии находятся на [странице релизов](https://github.com/rbouteiller/airplay-esp32/releases/latest),
    а текущая промежуточная сборка — под тегом [`beta`](https://github.com/rbouteiller/airplay-esp32/releases/tag/beta).
    Объединённый образ записывается со смещения **`0x0`** с помощью `esptool` или
    [веб-инструмента esptool-js](https://espressif.github.io/esptool-js/).

    Публикуются только перечисленные выше варианты. Остальные
    [среды сборки](../reference/build-environments.md) необходимо собирать самостоятельно.

<a id="option-b-platformio"></a>
## Вариант Б — PlatformIO

[PlatformIO](https://platformio.org/) автоматически настроит набор инструментов сборки.

```bash
# 1. Install the PlatformIO CLI
pip install platformio

# 2. Clone the project, including submodules
git clone --recursive https://github.com/rbouteiller/airplay-esp32
cd airplay-esp32

# 3. Plug the board in over USB and flash the firmware
pio run -e esp32s3 -t upload

# 4. Flash the SPIFFS image containing the web UI and data files
pio run -e esp32s3 -t uploadfs

# 5. Optionally watch the serial output
pio run -e esp32s3 -t monitor
```

!!! warning "Шаг 4 обязателен"

    PlatformIO **не** записывает раздел SPIFFS как часть `-t upload`. Если пропустить
    `-t uploadfs`, устройство загрузится, но портал настройки и страницы веб-интерфейса будут отсутствовать,
    и во время установки вы получаете ошибки «файл не найден». См.
    [Файловая система SPIFFS](../reference/spiffs.md).

Замените `esp32s3` на ту среду, которая соответствует вашему оборудованию — см.
[среды сборки](../reference/build-environments.md) для получения полного списка.

<a id="option-c-esp-idf"></a>
## Вариант C — ESP-IDF

```bash
# 1. Install ESP-IDF v5.5.5 or newer:
#    https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

# 2. Clone the project, including submodules
git clone --recursive https://github.com/rbouteiller/airplay-esp32
cd airplay-esp32

# 3. Activate the ESP-IDF environment
source /path/to/esp-idf/export.sh

# 4. Build and flash, including the SPIFFS "storage" partition from data/
idf.py set-target esp32s3
idf.py build
idf.py -p /dev/ttyUSB0 flash

# 5. Optionally monitor the serial output
idf.py -p /dev/ttyUSB0 monitor
```

В отличие от PlatformIO, `idf.py flash` записывает раздел SPIFFS на том же этапе, поэтому
не нужно запоминать отдельную загрузку файловой системы.

<a id="next"></a>
## Дальше

Перейдите к [Первой загрузке](first-boot.md).
