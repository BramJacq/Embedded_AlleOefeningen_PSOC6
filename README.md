# Embedded_PSOC6_AllExercises

## TFT Display – Oefeningen

### Gebruik maken van het TFT display

---

### Oefening 1 – Basis initialisatie

**Doel**  
Het TFT-scherm correct initialiseren en een eenvoudige tekst weergeven met de `GUI_DispString()` API.

---

### Opdracht

1. Maak een **Empty App** aan in ModusToolbox.
2. Open de **Library Manager** en voeg de **CY8CKIT-028-TFT** toe.  
   Vergeet niet om de libraries te **updaten**.
3. Open de documentatie van de TFT-controller en volg de **Quick Start Guide**.
4. Zorg ervoor dat **"Hello world"** op het scherm wordt weergegeven.
5. Voeg vervolgens een **tweede tekstregel** toe op het display.

---

### Opmerking

De **Library Manager** installeert automatisch alle benodigde libraries voor de componenten op het **CY8CKIT-028-TFT Shield**.

Dit shield bevat de volgende hardware:

- 2.4 inch TFT Display (**ST7789V**)
- Motion Sensor (**BMI-160**)
- Ambient Light Sensor (**TEMT6000X01**)
- PDM Microphone (**SPK0838HT4HB**)
- Audio Codec (**AK4954A**)

---

### Benodigde libraries

- EmWin  
- CY8CKIT-028-TFT

---

### Makefile configuratie

Voeg de volgende regel toe aan je `Makefile`:

```makefile
COMPONENTS+=EMWIN_NOSNTS
```

---

## Oefening 2 – Gebruik van het shield (optimalisatie)

**Doel**  
tonen dat gebruik van de cy8ckit_028_tft-library de code vereenvoudigt.

---

We maakten gebruik van de mtb_st7789v librarie waardoor we de pinnen apart moeten declareren en initialiseren.  
Als we echter gaan werken met de cy8ckit_028_tft librarie (het shieldje) dan kan de code er veel compacter uitzien.

---

### Opdracht

- Include nu enkel `#include "cy8ckit_028_tft.h"` en `#include "GUI.h"`, naast de gebruikelijke initialisaties voor de PSoC6.
- We moeten geen `const mtb_st7789v_pins_t tft_pins` declareren.
- Gebruik de kortere initialisatieversie:  
  `cy8ckit_028_tft_init (NULL, NULL, NULL, NULL);`
- Je code is nu vereenvoudigd tot slechts **17 regels**.
- Maak eventueel eens gebruik om de tekst op een andere positie te plaatsen met `GUI_DispStringAt()`.

---

### Benodigde libraries

- EmWin  
- CY8CKIT-028-TFT

---

### Makefile configuratie

Voeg de volgende regel toe aan je `Makefile`:

```makefile
COMPONENTS+=EMWIN_NOSNTS
```

---

## Oefening 3 – emWin API's leren gebruiken

**Doel**  
Werken met fonts en kleuren.

---

Open de documentatie van de **SEGGER emWin graphics library** en open de **emWin User Guide**.  
Hierin kan je alle API Calls terugvinden die nodig zijn om het scherm aan te sturen.

Voor de volgende oefening kan je best de volgende API's uit **hoofdstuk 5** eens doornemen:

- Text API > Displaying text  
- Text API > Position  
- Font API > Common font-related functions  
- Color API > Basic functions  

---

### Opdracht

- Toon met de standaard font de tekst **"Hello world"** op positie **x = 40** en **y = 100**.
- Toon op de volgende regel de tekst **"Opnieuw welkom"** met de volgende eigenschappen:
  - Font: **16_ASCII**
  - Background color: **Red**
  - Font color: **Black**

---

### Benodigde libraries

- EmWin  
- CY8CKIT-028-TFT

---

### Makefile configuratie

Voeg de volgende regel toe aan je `Makefile`:

```makefile
COMPONENTS+=EMWIN_NOSNTS
```

---

## Oefening 4 – Dynamische tekst (aftellen)

**Doel**  
werken met tekstupdates en timing.

---

Toon in het midden van het display de tekst **"De bom gaat af in 9"** en laat dit getal aftellen tot **0**.  
Probeer enkel de character van de timer te veranderen en niet de ganse tekstregel.

---

### Opdracht

- Toon **"De bom gaat af in 9"**.
- Laat het getal aftellen tot **0**, waarbij enkel de cijferpositie wordt overschreven (iedere **1 s**).
- Laat na **0** het aftellen opnieuw starten.
---

### Benodigde libraries

- EmWin  
- CY8CKIT-028-TFT

---

### Makefile configuratie

Voeg de volgende regel toe aan je `Makefile`:

```makefile
COMPONENTS+=EMWIN_NOSNTS
```

---
