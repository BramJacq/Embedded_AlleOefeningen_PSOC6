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
