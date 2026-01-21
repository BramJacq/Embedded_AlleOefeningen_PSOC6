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

### 2. Gebruik van het Shield (Optimalisatie)
**Doel:** De code vereenvoudigen door gebruik te maken van de specifieke shield-library.
* **Focus:** Vervang handmatige pin-declaraties door `cy8ckit_028_tft_init(NULL, NULL, NULL, NULL)`.
* **Taak:** Reduceer de code tot circa 17 regels en experimenteer met `GUI_DispStringAt()`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex2_optimalisatie/main.c)

### 3. emWin API's & Styling
**Doel:** Werken met fonts, kleuren en tekstpositionering.
* **Focus:** Gebruik maken van de SEGGER emWin User Guide (Hoofdstuk 5).
* **Taak:** Toon "Hello world" op specifieke coördinaten en voeg gekleurde tekst toe met font `16_ASCII`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex3_APIs/main.c)

### 4. Dynamische Tekst (Aftellen)
**Doel:** Real-time updates van het display zonder het volledige scherm te verversen.
* **Taak:** Maak een timer die aftelt van 9 naar 0. Zorg dat enkel het cijfer wordt overschreven voor maximale efficiëntie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TFT_ex4_dynamisch/main.c)

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

### 2. Ultrasone Afstandsmeting (Capture/PWM)
**Doel:** Afstand bepalen met de **HC-SR04** sensor via PDL (Peripheral Driver Library).
* **Concept:** * **TCPWM 1 (PWM):** Genereert de 10µs triggerpuls op `P9_0`.
    * **TCPWM 2 (Capture):** Meet de tijdsduur van het ECHO-signaal op `P9_1`.
* **Berekening:** $Afstand (cm) = \frac{Tijd (\mu s) \times 343}{2 \times 10000}$
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/TCPWM_ex2_UltrasoneAfstandsMeting/main.c)
<img width="1913" height="774" alt="image" src="https://github.com/user-attachments/assets/c129945d-3c28-4963-812d-839eca10064a" />
<img width="1919" height="783" alt="image" src="https://github.com/user-attachments/assets/59c91e95-2c7f-4c7f-bf37-0be16bbbea3a" />

---

## 🕒 FreeRTOS Oefeningen

Multitasking op de PSoC 6 met taken (threads), semaphores en queues.

### 🧵 Taken & Threads

#### Oefening 1 – Delays
**Doel:** Gebruik maken van non-blocking delays (`vTaskDelay`).
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex1_delays/main.c)

#### Oefening 2 – Priority
**Doel:** Begrijpen hoe de scheduler omgaat met taakprioriteiten.
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex2_priority/main.c)

#### Oefening 3 – Taakbeheer (Idle/Halted/Running)
**Doel:** Handmatig de status van een taak manipuleren (Suspend/Resume).
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex3_idlehaltedrunning/main.c)

---

### 🚦 Semaphores

#### Oefening 4 – Binary Semaphore
**Doel:** Synchronisatie tussen taken en interrupts afdwingen.
* **Library:** Voeg **Retarget-IO** toe voor UART feedback.
* **Taak:** Gebruik `xSemaphoreTake` en `xSemaphoreGive` om kritieke secties te beschermen.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex4_Semaphore/main.c)

---

### 📬 Queue Management

#### Oefening 5 – Queues & PWM
**Doel:** Veilige datacommunicatie tussen taken.
* **Library:** Voeg **Retarget-IO** toe voor UART input/output.
* **Taak:** Stuur PWM-waarden van een `uartTask` naar een `pwmTask` via een Queue.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/RTOS_ex5_Queue/main.c)

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

### 2. WDT Basics (Watchdog Timer)
**Doel:** Het implementeren van een beveiliging tegen software- of hardware-lockups.
* **Taak:** Reduceer de standaard "Watchdog Timer" template tot een minimalistische versie (±70 regels). Experimenteer met `ENABLE_BLOCKING_FUNCTION` om te zien hoe de WDT de PSoC 6 reset wanneer de code vastloopt.
* **Inzicht:** WDT is essentieel voor IoT-devices die autonoom moeten blijven functioneren zonder menselijke interventie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex2_WDT/main.c)

> [!NOTE]
> **RTC vs WDT:** > De **RTC** wordt gebruikt voor tijdstempels en kalenderfuncties (wanneer gebeurde iets?), terwijl de **WDT** een veiligheidsmechanisme is (draait de code nog?). De RTC loopt door in low-power modes, terwijl de WDT de processor dwingt te herstarten bij fouten.

### 3. Memory Basics (External QSPI Flash)
**Doel:** Werken met non-volatile geheugen voor data-opslag.
* **Taak:** Gebruik het "QSPI flash read and write" template. Schrijf de tekst "Hello World!" naar het externe Flash-geheugen (U4) en verifieer de geschreven bytes via een Hex-to-Text converter.
* **Focus:** Begrijp hoe kritieke data (configuraties of sensor logs) bewaard blijven na een stroomonderbreking.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/SmartDev_ex3_Memory/main.c)

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

---


## 🌐 WiFi & Connectiviteit (AnyCloud)

In dit hoofdstuk leer je de PSoC 6 te verbinden met het internet, TCP-communicatie op te zetten, JSON-data te parsen en te werken met MQTT.

### 📶 WiFi Basis (Station Mode)

#### Oefening 1 – Attach to WiFi
**Doel:** Verbinding maken met een beveiligd WPA2 netwerk.
* **Taak:** Wijzig de SSID en het wachtwoord in de code om te verbinden met je eigen netwerk.
* **📂 Project:** [WiFi_ex01_attach](ModToolBox_AlleOefeningen/WiFi_ex01_attach)

#### Oefening 2 – Open Network
**Doel:** Verbinden met een onbeveiligd netwerk.
* **Taak:** Bestudeer wat er in de configuratie verandert wanneer er geen wachtwoord vereist is.
* **📂 Project:** [WiFi_ex02_open](ModToolBox_AlleOefeningen/WiFi_ex02_open)

#### Oefening 3 – IP Adres Octetten
**Doel:** Het verkregen IP-adres uitlezen en formatteren.
* **Taak:** Analyseer hoe de individuele octetten uit het IPv4-adres worden geëxtraheerd voor weergave.
* **📂 Project:** [WiFi_ex03_print](ModToolBox_AlleOefeningen/WiFi_ex03_print)

#### Oefening 4 – Multi-Network Support
**Doel:** Redundantie inbouwen door meerdere SSID's op te slaan.
* **Taak:** Pas de code aan zodat het systeem na $x$ pogingen automatisch overschakelt naar een alternatief netwerk.
* **📂 Project:** [WiFi_ex04_multi](ModToolBox_AlleOefeningen/WiFi_ex04_multi)

---

### 🔌 TCP Client Communicatie

#### Oefening 5 – Connect to TCP Server
**Doel:** Low-level socket communicatie en RTOS integratie.
* **Inzicht:** Leer het gebruik van Semaphores en `xTaskNotify` binnen netwerk-callbacks.
* **Taak:** Verbind de PSoC met een externe server (bijv. Hercules op je PC) via een fixed IP en poort.
* **📂 Project:** [WiFi_ex05_client](ModToolBox_AlleOefeningen/WiFi_ex05_client)

#### Oefening 6 – TCP Response & Commando's
**Doel:** Bidirectionele communicatie.
* **Taak:** Breid de client uit zodat deze reageert op commando's vanuit de server. Implementeer logica voor "ON", "OFF" en "TOGGLE".
* **📂 Project:** [WiFi_ex06_client_response](ModToolBox_AlleOefeningen/WiFi_ex06_client_response)

---

### 📦 JSON & API's

#### Oefening 7 – Parse JSON (cJSON)
**Doel:** Gestructureerde data verwerken met de cJSON library.
* **Taak:** Bouw een JSON-object en extraheer specifieke velden zoals "name" en "student" om een geformatteerde string te printen.
* **📂 Project:** [WiFi_ex07_json](ModToolBox_AlleOefeningen/WiFi_ex07_json)

#### Oefening 8 – JSON in Callbacks
**Doel:** Efficiënt data parsen zodra deze binnenkomt.
* **Taak:** Verplaats de parse-logica naar de `jsonCallback` functie.
* **📂 Project:** [WiFi_ex08_jsonparser](ModToolBox_AlleOefeningen/WiFi_ex08_jsonparser)

---

### 🌍 HTTP Requests (Optioneel)

#### Oefening 9 – HTTP GET
**Doel:** Data ophalen van een webserver.
* **Taak:** Vraag data op via `httpbin.org/anything` en bestudeer de headers.
* **📂 Project:** [WiFi_ex09_get](ModToolBox_AlleOefeningen/WiFi_ex09_get)

#### Oefening 10 – HTTP POST & PostBin
**Doel:** Data versturen naar een cloud-service.
* **Taak:** Maak een bin aan op PostBin en stuur een JSON-body met je StudentID en een LED-status via een HTTPS POST request.
* **📂 Project:** [WiFi_ex10_post](ModToolBox_AlleOefeningen/WiFi_ex10_post)

---

### 🔋 Advanced & IoT

#### Oefening 11 – Low Power WiFi
**Doel:** Stroomverbruik minimaliseren terwijl de WiFi-verbinding behouden blijft.
* **Focus:** Bestudeer de WLAN Low Power modes en DTIM-intervallen.
* **📂 Project:** [WiFi_ex11_wlan_low_power](ModToolBox_AlleOefeningen/WiFi_ex11_wlan_low_power)

#### Oefening 12 – MQTT Client
**Doel:** Pub/Sub communicatie voor IoT toepassingen.
* **Taak:** Gebruik de HiveMQ broker om data uit te wisselen op het topic `PLX_psoc`. Analyseer de RTOS queue die de inkomende berichten beheert.
* **📂 Project:** [WiFi_ex12_mqtt](ModToolBox_AlleOefeningen/WiFi_ex12_mqtt)

---


## 🛠️ HAL & PDL Peripherals

In dit hoofdstuk leer je de randapparatuur van de PSoC™ 6 aansturen via twee verschillende lagen: de gebruiksvriendelijke **HAL** (Hardware Abstraction Layer) en de meer gedetailleerde **PDL** (Peripheral Driver Library).

### 🟢 HAL Oefeningen (High-Level)

#### 1. GPIO: Blink an LED
**Doel:** Een LED laten knipperen met de Hardware Abstraction Layer.
* **Projectnaam:** `ch02_ex01_HAL_blinkled`
* **Taak:** Initialiseer `CYBSP_USER_LED` als output en toggle deze elke 250ms met `cyhal_system_delay_ms`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex01_blinkled/main.c)

#### 2. Debug Printing via UART
**Doel:** Seriële communicatie toevoegen voor debugging.
* **Projectnaam:** `ch03_ex02_HAL_blinkled_print`
* **Library:** Voeg de **Retarget-IO** library toe.
* **Taak:** Initialiseer de UART-poort en print "LED ON" en "LED OFF" naar de seriële terminal.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex02_blinkled_print/main.c)

#### 3. Button Input
**Doel:** De status van een fysieke drukknop inlezen via polling.
* **Projectnaam:** `ch02_ex03_HAL_button`
* **Taak:** Configureer `CYBSP_USER_BTN` met een pull-up weerstand. Zet de LED aan zolang de knop ingedrukt wordt.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex03_button/main.c)

#### 4. GPIO Interrupts
**Doel:** Reageren op input via hardware interrupts.
* **Projectnaam:** `ch02_ex04_HAL_interrupt`
* **Taak:** Registreer een callback functie op de falling edge van de knop om de LED te toggelen zonder de CPU constant te belasten.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex04_interrupt/main.c)

#### 5. PWM: LED Brightness
**Doel:** De intensiteit van een LED regelen middels pulsbreedtemodulatie.
* **Projectnaam:** `ch02_ex09_HAL_pwm`
* **Taak:** Gebruik een PWM-blok om de LED aan te sturen. Varieer de duty cycle in de main loop voor een "fading" effect.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex05_pwm/main.c)

#### 6. UART Receive
**Doel:** Interactie met de PSoC vanaf je computer.
* **Projectnaam:** `ch02_ex16_HAL_uartreceive`
* **Taak:** Gebruik `cyhal_uart_getc` om te luisteren naar '1' (LED aan) of '0' (LED uit).
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex06_uart_receive/main.c)

#### 7. UART Send (Button Count)
**Doel:** Data terugsturen naar de terminal.
* **Projectnaam:** `ch02_ex17_HAL_uartsend`
* **Taak:** Tel knopdrukken (0-9) en stuur de waarde als karakter terug naar de PC via `cyhal_uart_putc`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/HAL_ex07_uart_send/main.c)

---

### 🔵 PDL Oefeningen (Low-Level)

#### 1. GPIO: Blink an LED (PDL)
**Doel:** LED aansturing via de Peripheral Driver Library.
* **Projectnaam:** `ch02_ex05_PDL_blinkled`
* **Taak:** Configureer de pin in de **Device Configurator**. Gebruik `Cy_GPIO_Write` en `Cy_SysLib_Delay` voor de implementatie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex01_blinkled/main.c)

#### 2. Debug Printing (PDL)
**Doel:** UART configuratie op register-niveau.
* **Projectnaam:** `ch02_ex06_PDL_blinkled_print`
* **Taak:** Configureer het SCB-blok (UART) in de Device Configurator en gebruik `Cy_SCB_UART_PutString` voor output.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex02_blinkled_print/main.c)

#### 3. Button Input (PDL)
**Doel:** Directe pin-uitlezing met PDL.
* **Projectnaam:** `ch02_ex07_PDL_button`
* **Taak:** Gebruik de Device Configurator voor de pull-up instellingen en controleer de status met `Cy_GPIO_Read`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex03_button/main.c)

#### 4. GPIO Interrupts (PDL)
**Doel:** Handmatige interrupt configuratie via SysInt.
* **Projectnaam:** `ch02_ex08_PDL_interrupt`
* **Taak:** Configureer `Cy_SysInt_Init` en `NVIC_EnableIRQ`. Vergeet niet de interrupt vlag te wissen in de ISR met `Cy_GPIO_ClearInterrupt`.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex04_interrupt/main.c)

#### 5. PWM: LED Brightness (PDL)
**Doel:** Het TCPWM-blok direct aansturen.
* **Projectnaam:** `ch02_ex10_PDL_pwm`
* **Taak:** Koppel een TCPWM-kanaal aan de LED-pin in de configurator en gebruik `Cy_TCPWM_PWM_SetCompare0` voor de helderheid.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex05_pwm/main.c)

#### 6. UART Receive (PDL)
**Doel:** Ontvangen van seriële data via PDL-functies.
* **Projectnaam:** `ch02_ex18_PDL_uartreceive`
* **Taak:** Gebruik `Cy_SCB_UART_Get` om de inkomende karakters te verwerken en de LED te sturen.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex06_uart_receive/main.c)

#### 7. UART Send (PDL)
**Doel:** Het verzenden van individuele karakters via PDL.
* **Projectnaam:** `ch02_ex19_PDL_uartsend`
* **Taak:** Stuur de button-count naar de terminal met de `Cy_SCB_UART_Put` functie.
* **🔗 Code:** [main.c](ModToolBox_AlleOefeningen/PDL_ex07_uart_send/main.c)

---
* **🔗 Code:** [Houd hier plaats voor de link naar main.c]

---
