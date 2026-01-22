# Embedded PSoC 6 - Alle Oefeningen

Dit repository bevat een verzameling oefeningen voor de **PSoC 6 WiFi-BT Pioneer Kit**, gericht op het aansturen van een TFT-display en het gebruik van de TCPWM-modules (Timers, Counters, PWM).

---

## 📺 TFT Display Oefeningen

Deze reeks oefeningen focust op het initialiseren en aansturen van het **CY8CKIT-028-TFT** shield.

### 1. Basis Initialisatie
**Doel:** Het scherm correct opstarten en tekst weergeven met de `GUI_DispString()` API.
* **Hardware:** CY8CKIT-028-TFT (ST7789V controller).
* **Taak:** Initialiseer de bibliotheek en toon "Hello World" gevolgd door een tweede regel tekst.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex1_Basic/main.c)
> **Hoe moet je dit doen?** > Maak een 'Empty App' aan in Project Creator. Voeg de bibliotheken `display-tft-st7789v` en `emWin` toe via de Library Manager. Configureer de SPI-pinnen in de Device Configurator.  
> **Wat gebeurt hier?** > Initialisatie van de ST7789V controller via de emWin bibliotheek. Gebruik van `GUI_Init()` en `GUI_DispString()` om tekst weer te geven via de SPI-interface van het TFT-shield.

### 2. Gebruik van het Shield (Optimalisatie)
**Doel:** De code vereenvoudigen door gebruik te maken van de specifieke shield-library.
* **Focus:** Vervang handmatige pin-declaraties door `cy8ckit_028_tft_init(NULL, NULL, NULL, NULL)`.
* **Taak:** Reduceer de code tot circa 17 regels en experimenteer met `GUI_DispStringAt()`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex2_optimalisatie/main.c)
> **Hoe moet je dit doen?** > Gebruik het vorige project als template. Voeg de `cy8ckit-028-tft` shield-library toe. Vervang alle handmatige SPI-initialisaties door de specifieke shield-init functie.  
> **Wat gebeurt hier?** > Gebruik van de `cy8ckit_028_tft_init()` functie om alle pinnen (SPI, Reset, Backlight) in één keer correct te configureren. Dit optimaliseert de code aanzienlijk.

### 3. emWin API's & Styling
**Doel:** Werken met fonts, kleuren en tekstpositionering.
* **Focus:** Gebruik maken van de SEGGER emWin User Guide (Hoofdstuk 5).
* **Taak:** Toon "Hello world" op specifieke coördinaten en voeg gekleurde tekst toe met font `16_ASCII`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex3_APIs/main.c)
> **Hoe moet je dit doen?** > Raadpleeg de emWin User Guide. Gebruik API's zoals `GUI_SetFont` en `GUI_SetColor` in je code voor styling.  
> **Wat gebeurt hier?** > Gebruik van fonts (`16_ASCII`) en kleuren. Tekst wordt gepositioneerd op basis van X/Y coördinaten uit de SEGGER emWin User Guide om een interface-layout te maken.

### 4. Dynamische Tekst (Aftellen)
**Doel:** Real-time updates van het display zonder het volledige scherm te verversen.
* **Taak:** Maak een timer die aftelt van 9 naar 0. Zorg dat enkel het cijfer wordt overschreven voor maximale efficiëntie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex4_dynamisch/main.c)
> **Hoe moet je dit doen?** > Maak een variabele die aftelt in een loop. Gebruik `GUI_DispDecAt` om getallen weer te geven en zorg dat de achtergrondkleur van de tekstregio niet het hele scherm wist.  
> **Wat gebeurt hier?** > Een efficiënte loop die aftelt van 9 naar 0. Alleen de tekstregio wordt ververst om flikkeringen te voorkomen, gecombineerd met `cyhal_system_delay_ms()`.

> [!IMPORTANT]
> **Configuratie voor TFT Oefeningen:**
> Voeg voor alle bovenstaande oefeningen de volgende regel toe aan je **Makefile**:
> `COMPONENTS+=EMWIN_NOSNTS`

---

## ⚙️ TCPWM Oefeningen

In deze integratieoefeningen leer je de kracht van de **Timer, Counter, PWM (TCPWM)** module kennen.

### 1. Rotatiesnelheid meten (Counter)
**Doel:** Meten van externe pulsen (bijv. van een encoder) om RPM te berekenen.
* **Hardware:** Gebruik een functiegenerator of sensor op pin `P10_0`.
* **Concept:** Gebruik één TCPWM als Counter voor pulsen en één als Timer voor de tijdsbasis.
* **Berekening:** $RPM = \frac{PulsenPerSeconde}{PulsenPerOmwenteling} \times 60$
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TCPWM_ex1_RotatiesnelheidMotor/main.c)
> **Hoe moet je dit doen?** > Configureer in de Device Configurator één TCPWM-blok als 'Timer' (1s interval) en één als 'Counter' (input op `P10_0`). Schakel interrupts in voor de Timer.  
> **Wat gebeurt hier?** > Gebruik van een TCPWM in Counter mode en een tweede in Timer mode voor de tijdsbasis. Berekent RPM via de formule op basis van inkomende pulsen.

### 2. Ultrasone Afstandsmeting (Capture/PWM)
**Doel:** Afstand bepalen met de **HC-SR04** sensor via PDL (Peripheral Driver Library).
* **Concept:** * **TCPWM 1 (PWM):** Genereert de 10µs triggerpuls op `P9_0`.
    * **TCPWM 2 (Capture):** Meet de tijdsduur van het ECHO-signaal op `P9_1`.
* **Berekening:** $Afstand (cm) = \frac{Tijd (\mu s) \times 343}{2 \times 10000}$
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TCPWM_ex2_UltrasoneAfstandsMeting/main.c)
<img width="1913" height="774" alt="image" src="https://github.com/user-attachments/assets/c129945d-3c28-4963-812d-839eca10064a" />
<img width="1919" height="783" alt="image" src="https://github.com/user-attachments/assets/59c91e95-2c7f-4c7f-bf37-0be16bbbea3a" />
> **Hoe moet je dit doen?** > Stel één TCPWM in als PWM voor de 10µs trigger. Stel een tweede TCPWM in op 'Capture' mode. Koppel de Echo-pin aan de capture-trigger. Gebruik PDL-functies om de counter-waarde uit te lezen.  
> **Wat gebeurt hier?** > TCPWM PWM genereert een 10µs trigger op `P9_0`. TCPWM Capture meet de ECHO-puls op `P9_1`. De tijdsduur tussen de flanken wordt omgezet naar cm.

---

## 🕒 FreeRTOS Oefeningen

Multitasking op de PSoC 6 met taken (threads), semaphores en queues.

### 🧵 Taken & Threads

#### Oefening 1 – Delays
**Doel:** Gebruik maken van non-blocking delays (`vTaskDelay`).
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex1_delays/main.c)
> **Hoe moet je dit doen?** > Voeg `FREERTOS` toe aan je Makefile. Maak twee taken aan met `xTaskCreate`. Gebruik `vTaskDelay` in plaats van de HAL-delay.  
> **Wat gebeurt hier?** > Gebruik van `vTaskDelay` (non-blocking). Toont hoe de scheduler prioriteit geeft aan taken en hoe taken de CPU vrijgeven tijdens het wachten.

#### Oefening 2 – Priority
**Doel:** Begrijpen hoe de scheduler omgaat met taakprioriteiten.
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex2_priority/main.c)
> **Hoe moet je dit doen?** > Maak meerdere taken aan met verschillende prioriteiten in `xTaskCreate`. Log de uitvoering via UART.  
> **Wat gebeurt hier?** > Er worden taken met verschillende prioriteitsniveaus aangemaakt. Via de UART wordt zichtbaar gemaakt welke taak de CPU krijgt (pre-emptive scheduling).

#### Oefening 3 – Taakbeheer (Idle/Halted/Running)
**Doel:** Handmatig de status van een taak manipuleren (Suspend/Resume).
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex3_idlehaltedrunning/main.c)
> **Hoe moet je dit doen?** > Gebruik `vTaskSuspend` en `vTaskResume` functies op basis van een trigger (bijv. UART input of timer).  
> **Wat gebeurt hier?** > Een controller-taak zet een worker-taak tijdelijk op pauze en hervat deze. Dit demonstreert handmatig taakbeheer binnen het RTOS.

---

### 🚦 Semaphores

#### Oefening 4 – Binary Semaphore
**Doel:** Synchronisatie tussen taken en interrupts afdwingen.
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **Taak:** Gebruik `xSemaphoreTake` en `xSemaphoreGive` om kritieke secties te beschermen.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex4_Semaphore/main.c)
> **Hoe moet je dit doen?** > Initialiseer een Binary Semaphore met `xSemaphoreCreateBinary`. Gebruik `xSemaphoreGiveFromISR` in de button-callback en `xSemaphoreTake` in de taak.  
> **Wat gebeurt hier?** > Gebruik van een Binary Semaphore om een taak te synchroniseren met een hardware-interrupt (drukknop). De taak 'slaapt' tot de knop wordt ingedrukt.

---

### 📬 Queue Management

#### Oefening 5 – Queues & PWM
**Doel:** Veilige datacommunicatie tussen taken.
* **Library:** Voeg **Retarget-IO** toe voor UART input/output.
* **Taak:** Stuur PWM-waarden van een `uartTask` naar een `pwmTask` via een Queue.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex5_Queue/main.c)
> **Hoe moet je dit doen?** > Maak een queue aan met `xQueueCreate`. Gebruik `xQueueSend` in de producer-taak (UART) en `xQueueReceive` in de consumer-taak (PWM).  
> **Wat gebeurt hier?** > Veilige data-overdracht tussen threads: Een `uartTask` stuurt nieuwe helderheidswaarden naar een `pwmTask` via een Queue om race-conditions te vermijden.

---

> [!IMPORTANT]
> **Configuratie voor RTOS Oefeningen:**
> Zorg dat de FreeRTOS library aanwezig is en voeg dit toe aan je **Makefile**:
> `COMPONENTS= FREERTOS`

---

## 📱 Smart Devices Oefeningen

In dit hoofdstuk verkennen we de geavanceerde functies van de PSoC 6, zoals de interne klok (RTC), beveiligingsmechanismen (WDT) en extern geheugen (QSPI Flash).

### 1. RTC Basics (Real-Time Clock)
**Doel:** Het bijhouden en weergeven van de actuele datum en tijd.
* **Taak:** Gebruik de HAL-documentatie om de RTC te configureren. Print bij het opstarten en bij een druk op **SW2** de huidige tijd. Laat elke seconde een "Tick!" zien in de terminal om de status te controleren.
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex1_RTC/main.c)
> **Hoe moet je dit doen?** > Activeer de RTC in de Device Configurator. Gebruik de HAL-functies `cyhal_rtc_init` en `cyhal_rtc_write/read`.  
> **Wat gebeurt hier?** > De interne Real-Time Clock wordt geconfigureerd. Het programma print de tijd via UART bij boot en bij elke druk op SW2. Een seconde-interrupt zorgt voor de "Tick!" melding.

### 2. WDT Basics (Watchdog Timer)
**Doel:** Het implementeren van een beveiliging tegen software- of hardware-lockups.
* **Taak:** Reduceer de standaard "Watchdog Timer" template tot een minimalistische versie (±70 regels). Experimenteer met `ENABLE_BLOCKING_FUNCTION` om te zien hoe de WDT de PSoC 6 reset wanneer de code vastloopt.
* **Inzicht:** WDT is essentieel voor IoT-devices die autonoom moeten blijven functioneren zonder menselijke interventie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex2_WDT/main.c)
> **Hoe moet je dit doen?** > Stel de timeout in de configurator in. Gebruik `cyhal_wdt_kick` in de main loop om resets te voorkomen. Test door de kick-functie uit te schakelen.  
> **Wat gebeurt hier?** > Integratie van de Watchdog. Als de software 'hangt' (gesimuleerd door een blocking function), zal de WDT de PSoC resetten omdat de timer niet tijdig 'gekickt' wordt.

> [!NOTE]
> **RTC vs WDT:** > De **RTC** wordt gebruikt voor tijdstempels en kalenderfuncties (wanneer gebeurde iets?), terwijl de **WDT** een veiligheidsmechanisme is (draait de code nog?). De RTC loopt door in low-power modes, terwijl de WDT de processor dwingt te herstarten bij fouten.

### 3. Memory Basics (External QSPI Flash)
**Doel:** Werken met non-volatile geheugen voor data-opslag.
* **Taak:** Gebruik het "QSPI flash read and write" template. Schrijf de tekst "Hello World!" naar het externe Flash-geheugen (U4) en verifieer de geschreven bytes via een Hex-to-Text converter.
* **Focus:** Begrijp hoe kritieke data (configuraties of sensor logs) bewaard blijven na een stroomonderbreking.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex3_Memory/main.c)
> **Hoe moet je dit doen?** > Voeg de `serial-flash` library toe. Gebruik de QSPI Configurator tool om de pinnen voor flashgeheugen U4 in te stellen.  
> **Wat gebeurt hier?** > Communicatie met het externe NOR Flash geheugen via het QSPI-protocol. De tekst "Hello World!" wordt naar een specifiek adres geschreven en weer uitgelezen ter verificatie.

---

### 🔍 Memory Configuratie & Recap
Bij het zelf opbouwen van een Memory project zijn de volgende stappen cruciaal:

1. **Library & Includes:** De `serial-flash` library moet aanwezig zijn.

   <img width="767" height="407" alt="image" src="https://github.com/user-attachments/assets/40289200-cec3-46cf-a340-96391b138523" />  

2. **QSPI Configurator:** Gebruik de tool om de geheugeninstellingen te genereren. Dit creëert de benodigde `.c` en `.h` bestanden in de `mem_config` folder.

   <img width="768" height="149" alt="image" src="https://github.com/user-attachments/assets/9fa83523-87d1-4dcc-a6b2-8c907aea4668" />  

3. **Vergelijking:** Met tools zoals WinMerge kun je zien dat de gegenereerde code sterk overeenkomt met de standaard templates.

   <img width="710" height="408" alt="image" src="https://github.com/user-attachments/assets/c573dc3f-ec64-4991-a8c0-dbb18c4a426b" />  

---

### 4. Smart Sensor (Integratieproject)
**Doel:** Het combineren van alle geleerde technieken (TFT, QSPI, RTC en Low Power) in een realistische smart-sensor workflow.

In deze oefening bouw je een systeem dat de volgende logica volgt:
1. **Configuratie:** Het apparaat wordt geconfigureerd via UART.
2. **Meting:** Er wordt een sensor-meting uitgevoerd.
3. **Visualisatie:** De data wordt getoond op het TFT-display.
4. **Opslag:** Data wordt gebufferd in het non-volatile geheugen (Flash).
5. **Low Power:** Het systeem gaat in een energiebesparende modus (Deep Sleep).
6. **Herhaal:** De RTC of een timer wekt het systeem voor de volgende meting.

**Gebruik van het geheugen:**
Het non-volatile geheugen houdt kritieke parameters bij, zoals:
* **Sensor data:** Kalibratiewaarden en gesamplede data.
* **Gebruikersinstellingen:** Idle/sleep tijd en het aantal samples per flush.
* **TFT-configuratie:** Instellingen zoals achtergrondkleur of tekst-lay-out.

* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex4_SmartSensor/main.c)
> **Hoe moet je dit doen?** > Integreer alle voorgaande libraries (TFT, QSPI, RTC). Implementeer `cyhal_system_deepsleep` om stroomverbruik te verlagen tussen meet-intervallen door.  
> **Wat gebeurt hier?** > Complex integratieproject: Combineert TFT, QSPI, RTC en Deep Sleep. Het systeem logt data in Flash, toont dit op het scherm en slaapt vervolgens tot de volgende RTC-trigger.

---


## 🌐 WiFi & Connectiviteit (AnyCloud)

In dit hoofdstuk leer je de PSoC 6 te verbinden met het internet, TCP-communicatie op te zetten, JSON-data te parsen en te werken met MQTT.

### 📶 WiFi Basis (Station Mode)

#### Oefening 1 – Attach to WiFi
**Doel:** Verbinding maken met een beveiligd WPA2 netwerk.
* **Taak:** Wijzig de SSID en het wachtwoord in de code om te verbinden met je eigen netwerk.
* **📂 Project:** [WiFi_ex01_attach](ModToolBox_AlleOefeningen/WiFi_ex01_attach)
> **Hoe moet je dit doen?** > Voeg de `wifi-connection-manager` toe. Definieer je netwerkgegevens in de code en gebruik de connect-functie van AnyCloud.  
> **Wat gebeurt hier?** > Gebruik van de AnyCloud stack om verbinding te maken met een beveiligd WPA2 Access Point.

#### Oefening 2 – Open Network
**Doel:** Verbinden met een onbeveiligd netwerk.
* **Taak:** Bestudeer wat er in de configuratie verandert wanneer er geen wachtwoord vereist is.
* **📂 Project:** [WiFi_ex02_open](ModToolBox_AlleOefeningen/WiFi_ex02_open)
> **Hoe moet je dit doen?** > Pas de security instellingen in de wifi-configuratie aan naar 'Open'.  
> **Wat gebeurt hier?** > Er wordt verbinding gemaakt met een netwerk zonder encryptie.

#### Oefening 3 – IP Adres Octetten
**Doel:** Het verkregen IP-adres uitlezen en formatteren.
* **Taak:** Analyseer hoe de individuele octetten uit het IPv4-adres worden geëxtraheerd voor weergave.
* **📂 Project:** [WiFi_ex03_print](ModToolBox_AlleOefeningen/WiFi_ex03_print)
> **Hoe moet je dit doen?** > Gebruik bit-shifting of hulpmiddelen uit de netwerk-library om het 32-bits IP-adres op te splitsen in vier octetten.  
> **Wat gebeurt hier?** > Analyse van het IPv4-adres voor weergave in de terminal.

#### Oefening 4 – Multi-Network Support
**Doel:** Redundantie inbouwen door meerdere SSID's op te slaan.
* **Taak:** Pas de code aan zodat het systeem na $x$ pogingen automatisch overschakelt naar een alternatief netwerk.
* **📂 Project:** [WiFi_ex04_multi](ModToolBox_AlleOefeningen/WiFi_ex04_multi)
> **Hoe moet je dit doen?** > Maak een array van SSID's en implementeer een retry-teller die bij falen indexeert naar het volgende netwerk.  
> **Wat gebeurt hier?** > Redundantie-logica voor betrouwbare connectiviteit.

---

### 🔌 TCP Client Communicatie

#### Oefening 5 – Connect to TCP Server
**Doel:** Low-level socket communicatie en RTOS integratie.
* **Inzicht:** Leer het gebruik van Semaphores en `xTaskNotify` binnen netwerk-callbacks.
* **Taak:** Verbind de PSoC met een externe server (bijv. Hercules op je PC) via een fixed IP en poort.
* **📂 Project:** [WiFi_ex05_client](ModToolBox_AlleOefeningen/WiFi_ex05_client)
> **Hoe moet je dit doen?** > Maak een socket aan en gebruik `connect()` naar het IP van de server. Gebruik Semaphores voor synchronisatie.  
> **Wat gebeurt hier?** > Low-level socket communicatie. Gebruik van Semaphores en `xTaskNotify` om netwerk-events veilig af te handelen.

#### Oefening 6 – TCP Response & Commando's
**Doel:** Bidirectionele communicatie.
* **Taak:** Breid de client uit zodat deze reageert op commando's vanuit de server. Implementeer logica voor "ON", "OFF" en "TOGGLE".
* **📂 Project:** [WiFi_ex06_client_response](ModToolBox_AlleOefeningen/WiFi_ex06_client_response)
> **Hoe moet je dit doen?** > Implementeer een 'receive' callback die binnenkomende strings vergelijkt met bekende commando's.  
> **Wat gebeurt hier?** > Bidirectionele communicatie waarbij de PSoC acties uitvoert op basis van server-commando's.

---

### 📦 JSON & API's

#### Oefening 7 – Parse JSON (cJSON)
**Doel:** Gestructureerde data verwerken met de cJSON library.
* **Taak:** Bouw een JSON-object en extraheer specifieke velden zoals "name" en "student" om een geformatteerde string te printen.
* **📂 Project:** [WiFi_ex07_json](ModToolBox_AlleOefeningen/WiFi_ex07_json)
> **Hoe moet je dit doen?** > Voeg de `cjson` library toe. Gebruik `cJSON_Parse` om een string om te zetten naar een doorzoekbaar object.  
> **Wat gebeurt hier?** > Verwerking van gestructureerde data (bijv. studentgegevens) met de cJSON bibliotheek.

#### Oefening 8 – JSON in Callbacks
**Doel:** Efficiënt data parsen zodra deze binnenkomt.
* **Taak:** Verplaats de parse-logica naar de `jsonCallback` functie.
* **📂 Project:** [WiFi_ex08_jsonparser](ModToolBox_AlleOefeningen/WiFi_ex08_jsonparser)
> **Hoe moet je dit doen?** > Integreer de cJSON parse-logica direct in de ontvangst-callback van je netwerktaak.  
> **Wat gebeurt hier?** > Dynamische parsing van JSON-data (naam, student nr, city) zodra deze via een callback binnenkomt.

---

### 🌍 HTTP Requests (Optioneel)

#### Oefening 9 – HTTP GET
**Doel:** Data ophalen van een webserver.
* **Taak:** Vraag data op via `httpbin.org/anything` en bestudeer de headers.
* **📂 Project:** [WiFi_ex09_get](ModToolBox_AlleOefeningen/WiFi_ex09_get)
> **Hoe moet je dit doen?** > Gebruik de HTTP client library om een GET-request te sturen naar een REST-endpoint.  
> **Wat gebeurt hier?** > Ophalen en analyseren van webserver data en headers.

#### Oefening 10 – HTTP POST & PostBin
**Doel:** Data versturen naar een cloud-service.
* **Taak:** Maak een bin aan op PostBin en stuur een JSON-body met je StudentID en een LED-status via een HTTPS POST request.
* **📂 Project:** [WiFi_ex10_post](ModToolBox_AlleOefeningen/WiFi_ex10_post)
> **Hoe moet je dit doen?** > Bouw een JSON-body en verstuur deze met een POST-request inclusief de nodige HTTPS-headers.  
> **Wat gebeurt hier?** > Verzenden van data naar een cloud-service via een beveiligd HTTPS-kanaal.

---

### 🔋 Advanced & IoT

#### Oefening 11 – Low Power WiFi
**Doel:** Stroomverbruik minimaliseren terwijl de WiFi-verbinding behouden blijft.
* **Focus:** Bestudeer de WLAN Low Power modes en DTIM-intervallen.
* **📂 Project:** [WiFi_ex11_wlan_low_power](ModToolBox_AlleOefeningen/WiFi_ex11_wlan_low_power)
> **Hoe moet je dit doen?** > Configureer de WLAN-chip in low-power modus via AnyCloud instellingen.  
> **Wat gebeurt hier?** > Optimalisatie van stroomverbruik met behoud van connectiviteit via DTIM-intervallen.

#### Oefening 12 – MQTT Client
**Doel:** Pub/Sub communicatie voor IoT toepassingen.
* **Taak:** Gebruik de HiveMQ broker om data uit te wisselen op het topic `PLX_psoc`. Analyseer de RTOS queue die de inkomende berichten beheert.
* **📂 Project:** [WiFi_ex12_mqtt](ModToolBox_AlleOefeningen/WiFi_ex12_mqtt)
> **Hoe moet je dit doen?** > Voeg de `paho-mqtt` library toe. Maak verbinding met de broker en implementeer een queue voor berichtafhandeling.  
> **Wat gebeurt hier?** > IoT-communicatie via MQTT op topic `PLX_psoc`. Inkomende berichten sturen hardware-acties aan via een RTOS Queue.

---


## 🛠️ HAL & PDL Peripherals

In dit hoofdstuk leer je de randapparatuur van de PSoC™ 6 aansturen via twee verschillende lagen: de gebruiksvriendelijke **HAL** (Hardware Abstraction Layer) en de meer gedetailleerde **PDL** (Peripheral Driver Library).

### 🟢 HAL Oefeningen (High-Level)

#### 1. GPIO: Blink an LED
**Doel:** Een LED laten knipperen met de Hardware Abstraction Layer.
* **Projectnaam:** `ch02_ex01_HAL_blinkled`
* **Taak:** Initialiseer `CYBSP_USER_LED` als output en toggle deze elke 250ms met `cyhal_system_delay_ms`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex01_blinkled/main.c)
> **Hoe moet je dit doen?** > Initialiseer de pin `CYBSP_USER_LED` met `cyhal_gpio_init`. Gebruik `cyhal_gpio_write` in een loop.  
> **Wat gebeurt hier?** > Basisvorm van pin-aansturing via de HAL-laag met een eenvoudige delay.

#### 2. Debug Printing via UART
**Doel:** Seriële communicatie toevoegen voor debugging.
* **Projectnaam:** `ch03_ex02_HAL_blinkled_print`
* **Library:** Voeg de **Retarget-IO** library toe.
* **Taak:** Initialiseer de UART-poort en print "LED ON" en "LED OFF" naar de seriële terminal.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex02_blinkled_print/main.c)
> **Hoe moet je dit doen?** > Voeg `retarget-io` toe in de Library Manager. Gebruik `cy_retarget_io_init`.  
> **Wat gebeurt hier?** > Initialisatie van UART voor debugging. Statusberichten worden naar de terminal gestuurd.

#### 3. Button Input
**Doel:** De status van een fysieke drukknop inlezen via polling.
* **Projectnaam:** `ch02_ex03_HAL_button`
* **Taak:** Configureer `CYBSP_USER_BTN` met een pull-up weerstand. Zet de LED aan zolang de knop ingedrukt wordt.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex03_button/main.c)
> **Hoe moet je dit doen?** > Configureer de knop als input met pull-up. Gebruik `cyhal_gpio_read` in de main loop.  
> **Wat gebeurt hier?** > De LED status wordt direct gekoppeld aan de knop-uitlezing via polling (continue controle).

#### 4. GPIO Interrupts
**Doel:** Reageren op input via hardware interrupts.
* **Projectnaam:** `ch02_ex04_HAL_interrupt`
* **Taak:** Registreer een callback functie op de falling edge van de knop om de LED te toggelen zonder de CPU constant te belasten.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex04_interrupt/main.c)
> **Hoe moet je dit doen?** > Gebruik `cyhal_gpio_register_callback` en activeer het event met `cyhal_gpio_enable_event`.  
> **Wat gebeurt hier?** > De LED toggelt alleen wanneer er een hardware interrupt (falling edge) op de knop plaatsvindt. Dit is efficiënter dan polling.

#### 5. PWM: LED Brightness
**Doel:** De intensiteit van een LED regelen middels pulsbreedtemodulatie.
* **Projectnaam:** `ch02_ex09_HAL_pwm`
* **Taak:** Gebruik een PWM-blok om de LED aan te sturen. Varieer de duty cycle in de main loop voor een "fading" effect.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex05_pwm/main.c)
> **Hoe moet je dit doen?** > Initialiseer een PWM-object met `cyhal_pwm_init`. Pas de duty cycle aan met `cyhal_pwm_set_duty_cycle`.  
> **Wat gebeurt hier?** > De helderheid van de LED verandert vloeiend door de duty cycle van het PWM-signaal te variëren.

#### 6. UART Receive
**Doel:** Interactie met de PSoC vanaf je computer.
* **Projectnaam:** `ch02_ex16_HAL_uartreceive`
* **Taak:** Gebruik `cyhal_uart_getc` om te luisteren naar '1' (LED aan) of '0' (LED uit).
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex06_uart_receive/main.c)
> **Hoe moet je dit doen?** > Gebruik `cyhal_uart_getc` in een loop om binnenkomende karakters te lezen.  
> **Wat gebeurt hier?** > De PSoC luistert naar commando's ('1' of '0') vanuit de terminal om de LED te sturen.

#### 7. UART Send (Button Count)
**Doel:** Data terugsturen naar de terminal.
* **Projectnaam:** `ch02_ex17_HAL_uartsend`
* **Taak:** Tel knopdrukken (0-9) en stuur de waarde als karakter terug naar de PC via `cyhal_uart_putc`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex07_uart_send/main.c)
> **Hoe moet je dit doen?** > Tel events in de button-callback en stuur de waarde naar de terminal met `cyhal_uart_putc`.  
> **Wat gebeurt hier?** > Feedback naar de gebruiker: Elke knopdruk verhoogt een teller die live wordt doorgegeven via UART.

---

### 🔵 PDL Oefeningen (Low-Level)

#### 1. GPIO: Blink an LED (PDL)
**Doel:** LED aansturing via de Peripheral Driver Library.
* **Projectnaam:** `ch02_ex05_PDL_blinkled`
* **Taak:** Configureer de pin in de **Device Configurator**. Gebruik `Cy_GPIO_Write` en `Cy_SysLib_Delay` voor de implementatie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex01_blinkled/main.c)
> **Hoe moet je dit doen?** > Stel de pin in de Device Configurator in (Strong drive). Gebruik PDL-functies in de code.  
> **Wat gebeurt hier?** > Basis-aansturing op een lager niveau (register-georiënteerd) met PDL-functies.
<img width="522" height="37" alt="image" src="https://github.com/user-attachments/assets/70b3480c-df9f-48fe-8576-4c40e2e48fd6" />

<img width="536" height="36" alt="image" src="https://github.com/user-attachments/assets/402017f3-65ed-42c0-bed7-cc666b8aafa1" />  


#### 2. Debug Printing (PDL)
**Doel:** UART configuratie op register-niveau.
* **Projectnaam:** `ch02_ex06_PDL_blinkled_print`
* **Taak:** Configureer het SCB-blok (UART) in de Device Configurator en gebruik `Cy_SCB_UART_PutString` voor output.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex02_blinkled_print/main.c)
> **Hoe moet je dit doen?** > Configureer een SCB-blok als UART in de configurator. Gebruik `Cy_SCB_UART_PutString`.  
> **Wat gebeurt hier?** > Low-level UART configuratie voor statusberichten.
<img width="522" height="37" alt="image" src="https://github.com/user-attachments/assets/70b3480c-df9f-48fe-8576-4c40e2e48fd6" />

<img width="536" height="36" alt="image" src="https://github.com/user-attachments/assets/402017f3-65ed-42c0-bed7-cc666b8aafa1" />  

<img width="510" height="61" alt="image" src="https://github.com/user-attachments/assets/41c0a51a-96ac-431b-8812-5b1eb566888e" />  

<img width="734" height="651" alt="image" src="https://github.com/user-attachments/assets/412499a6-be20-4f39-8e18-f79cf01bb107" />  

<img width="716" height="635" alt="image" src="https://github.com/user-attachments/assets/5761e014-e653-413a-bb0b-db683e5d7c9b" />  

<img width="442" height="26" alt="image" src="https://github.com/user-attachments/assets/16908632-6349-48a2-8482-117765b9dda6" />  

<img width="655" height="30" alt="image" src="https://github.com/user-attachments/assets/05d9fd1a-808b-4477-aa77-4579508b1a4f" />  

<img width="849" height="60" alt="image" src="https://github.com/user-attachments/assets/8db939cd-7872-47f4-a4f2-e88f5bb3dfd1" />  


#### 3. Button Input (PDL)
**Doel:** Directe pin-uitlezing met PDL.
* **Projectnaam:** `ch02_ex07_PDL_button`
* **Taak:** Gebruik de Device Configurator voor de pull-up instellingen en controleer de status met `Cy_GPIO_Read`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex03_button/main.c)
> **Hoe moet je dit doen?** > Stel de pull-up in de configurator in. Gebruik `Cy_GPIO_Read` op de juiste poort en pin.  
> **Wat gebeurt hier?** > Rechtstreekse uitlezing van de knopstatus via PDL register-level functies.
<img width="518" height="39" alt="image" src="https://github.com/user-attachments/assets/882d74e9-0d09-46a2-ab84-a3458700c511" />

<img width="532" height="34" alt="image" src="https://github.com/user-attachments/assets/6ea14d8d-d794-4da0-9ecf-df3e03d55b8a" />  

<img width="508" height="27" alt="image" src="https://github.com/user-attachments/assets/1872116e-4cbf-4ed5-8a48-2b3eca8b9319" />  

<img width="691" height="33" alt="image" src="https://github.com/user-attachments/assets/5c0c2295-9ceb-4097-b1dc-41c69d0cb5c6" />  


#### 4. GPIO Interrupts (PDL)
**Doel:** Handmatige interrupt configuratie via SysInt.
* **Projectnaam:** `ch02_ex08_PDL_interrupt`
* **Taak:** Configureer `Cy_SysInt_Init` en `NVIC_EnableIRQ`. Vergeet niet de interrupt vlag te wissen in de ISR met `Cy_GPIO_ClearInterrupt`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex04_interrupt/main.c)
> **Hoe moet je dit doen?** > Stel de ISR-vector in met `Cy_SysInt_Init`. Schakel de interrupt in op de NVIC en wis de vlag handmatig.  
> **Wat gebeurt hier?** > Volledig handmatige interrupt-afhandeling op register-niveau, essentieel voor low-level optimalisatie.
<img width="518" height="39" alt="image" src="https://github.com/user-attachments/assets/882d74e9-0d09-46a2-ab84-a3458700c511" />

<img width="532" height="34" alt="image" src="https://github.com/user-attachments/assets/6ea14d8d-d794-4da0-9ecf-df3e03d55b8a" />  

<img width="715" height="39" alt="image" src="https://github.com/user-attachments/assets/e417d926-28e3-4e4c-89ee-4f4409d78d1e" />  

<img width="508" height="27" alt="image" src="https://github.com/user-attachments/assets/1872116e-4cbf-4ed5-8a48-2b3eca8b9319" />  

<img width="691" height="33" alt="image" src="https://github.com/user-attachments/assets/5c0c2295-9ceb-4097-b1dc-41c69d0cb5c6" />  


#### 5. PWM: LED Brightness (PDL)
**Doel:** Het TCPWM-blok direct aansturen.
* **Projectnaam:** `ch02_ex10_PDL_pwm`
* **Taak:** Koppel een TCPWM-kanaal aan de LED-pin in de configurator en gebruik `Cy_TCPWM_PWM_SetCompare0` voor de helderheid.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex05_pwm/main.c)
> **Hoe moet je dit doen?** > Koppel een TCPWM blok aan een pin in de configurator. Gebruik `Cy_TCPWM_PWM_SetCompare0` om registers direct te schrijven.  
> **Wat gebeurt hier?** > Helderheidsregeling door directe manipulatie van de PWM compare-registers via PDL.
<img width="517" height="33" alt="image" src="https://github.com/user-attachments/assets/59cad46c-4796-4164-b34d-ae70085e39bb" />  

<img width="708" height="39" alt="image" src="https://github.com/user-attachments/assets/b376860a-19c9-4816-a66b-479407d9dbf1" />  

<img width="738" height="32" alt="image" src="https://github.com/user-attachments/assets/eb8dff99-968a-439b-b267-c98b6bbbcba2" />  

<img width="673" height="171" alt="image" src="https://github.com/user-attachments/assets/0b8981cf-4bfc-4aa3-a589-60bf60932d34" />  

<img width="512" height="26" alt="image" src="https://github.com/user-attachments/assets/52de8081-5e81-4367-ac72-b7c8f1c97874" />


<img width="349" height="401" alt="image" src="https://github.com/user-attachments/assets/d2c86613-6abe-4ac3-bc56-01f36e14900d" />  

<img width="873" height="724" alt="image" src="https://github.com/user-attachments/assets/8c228ee2-dbc7-42db-8ad3-9aed1aa9b14f" />  

<img width="319" height="28" alt="image" src="https://github.com/user-attachments/assets/3db69478-66dd-425d-8cfc-5024231b4420" />  


#### 6. UART Receive (PDL)
**Doel:** Ontvangen van seriële data via PDL-functies.
* **Projectnaam:** `ch02_ex18_PDL_uartreceive`
* **Taak:** Gebruik `Cy_SCB_UART_Get` om de inkomende karakters te verwerken en de LED te sturen.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex06_uart_receive/main.c)
> **Hoe moet je dit doen?** > Gebruik `Cy_SCB_UART_Get` in een loop om de RX-FIFO van de UART uit te lezen.  
> **Wat gebeurt hier?** > Karakter-verwerking via de PDL-laag om acties op de LED uit te voeren.
<img width="517" height="34" alt="image" src="https://github.com/user-attachments/assets/edda9ebf-c535-4840-911f-56c386bc402f" />

<img width="629" height="43" alt="image" src="https://github.com/user-attachments/assets/52f214d7-db21-4d15-8995-9c7740e8aa79" />  

<img width="509" height="28" alt="image" src="https://github.com/user-attachments/assets/b50af2d7-c70c-4dd8-9c94-dd9e07da9ad2" />  

<img width="713" height="562" alt="image" src="https://github.com/user-attachments/assets/6f7aff27-95ee-4943-9598-c08d46391088" /> 

<img width="480" height="29" alt="image" src="https://github.com/user-attachments/assets/7a83670f-6397-4ce2-b1db-eff1094e9459" />  

<img width="729" height="570" alt="image" src="https://github.com/user-attachments/assets/de97cd55-9faa-4d4c-b6ef-6e7ef7aa39d7" />  

<img width="690" height="30" alt="image" src="https://github.com/user-attachments/assets/adebbd5c-55b6-41f0-a867-ae216a6a371f" />  

<img width="857" height="755" alt="image" src="https://github.com/user-attachments/assets/b58c9677-b4b6-45c7-b85c-9cc0edb0b836" />


#### 7. UART Send (PDL)
**Doel:** Het verzenden van individuele karakters via PDL.
* **Projectnaam:** `ch02_ex19_PDL_uartsend`
* **Taak:** Stuur de button-count naar de terminal met de `Cy_SCB_UART_Put` functie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex07_uart_send/main.c)
> **Hoe moet je dit doen?** > Gebruik `Cy_SCB_UART_Put` om een byte direct naar de TX-FIFO van de UART te sturen.  
> **Wat gebeurt hier?** > Efficiënte verzending van teller-data zonder gebruik van printf, via low-level PDL functies.
<img width="506" height="26" alt="image" src="https://github.com/user-attachments/assets/03ac3216-e8e5-40cd-9a5e-36f6797bfba2" />

<img width="719" height="339" alt="image" src="https://github.com/user-attachments/assets/aeca84da-b7cf-450e-9f75-c488b26bff51" />

<img width="508" height="35" alt="image" src="https://github.com/user-attachments/assets/00577b9c-088e-4a4c-b6ad-d1004f33e247" />  

<img width="742" height="224" alt="image" src="https://github.com/user-attachments/assets/995717df-5c09-47d7-99f8-df04ee73d1f6" />  

<img width="445" height="29" alt="image" src="https://github.com/user-attachments/assets/52fdfa76-fefe-4afa-9d92-eb28653480e6" />  

<img width="698" height="572" alt="image" src="https://github.com/user-attachments/assets/e2b37adc-c95a-4192-ae5e-530b94404f08" />  

<img width="467" height="26" alt="image" src="https://github.com/user-attachments/assets/07987a39-ea11-4a77-baa8-16a5e3003a16" />  

<img width="659" height="565" alt="image" src="https://github.com/user-attachments/assets/6506919d-7773-453f-b1be-51ae24d5111b" />  

<img width="734" height="29" alt="image" src="https://github.com/user-attachments/assets/a88fef36-d2f9-4939-b4d0-59e46cd3f7e4" />  

<img width="834" height="721" alt="image" src="https://github.com/user-attachments/assets/0ad2a69a-acca-47b7-acfa-81f1b89c3827" />  


---
