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

---


