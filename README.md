# ScaleShow STM32F746G Discovery

[🇺🇸 English Version](#english-version) | [🇮🇹 Versione Italiana](#versione-italiana)

---

<a name="versione-italiana"></a>
## 🇮🇹 Versione Italiana

### Descrizione
**ScaleShow** è un'applicazione interattiva sviluppata per la scheda di sviluppo **STM32F746G-DISCOVERY**. Permette di esplorare in tempo reale scale musicali, accordi, notazioni alfabetiche e di solfeggio, offrendo un feedback audio diretto tramite il codec audio integrato e un'interfaccia touch screen avanzata.

### Caratteristiche Principali
* **Esplorazione Scale:** Navigazione tra 36 differenti scale musicali (Maggiore, Minore, Blues, Pentatoniche, ecc.).
* **Visualizzazione Doppia:** Mostra simultaneamente le note in formato alfabetico ($C, D, E...$) e in solfeggio tradizionale ($Do, Re, Mi...$).
* **Calcolo Accordi:** Selezione e visualizzazione di molteplici accordi con calcolo preciso degli intervalli semitonali rispetto alla fondamentale.
* **Feedback Audio:** Riproduzione tonale delle scale e degli accordi direttamente dallo speaker della board.
* **Screensaver di Standby:** Dopo 60 secondi di inattività, lo schermo diventa nero e attiva un'animazione a rimbalzo con le informazioni di stato e contatto:
  * `STANDBY (60s)`
  * `Touch screen to reactivate`
  * `(c) ScordaSoftware`
  * `maxscorda@gmail.com`
  * *Il sistema si ripristina istantaneamente al tocco.*

### Requisiti e Installazione
1. **Hardware:** Scheda STM32F746G-DISCOVERY.
2. **Software:** Arduino IDE con supporto per schede STM32 e librerie BSP dedicate (`stm32746g_discovery`).
3. Estrai l'archivio del progetto nella tua cartella degli sketch Arduino, apri `ScaleShow_STM32.ino`, seleziona la scheda corretta e compila/carica il codice.

---

<a name="english-version"></a>
## 🇺🇸 English Version

### Description
**ScaleShow** is an interactive application designed for the **STM32F746G-DISCOVERY** development board. It allows users to explore musical scales, chords, alphabetical and solfege notations in real-time, providing direct audio feedback and an intuitive touch screen interface.

### Key Features
* **Scale Exploration:** Browse through 36 different musical scales (Major, Minor, Blues, Pentatonic, etc.).
* **Dual Notation:** Simultaneously displays notes in alphabetical format ($C, D, E...$) and traditional solfege ($Do, Re, Mi...$).
* **Chord Calculation:** Select and view multiple chord types with precise semitone interval calculations relative to the root note.
* **Audio Feedback:** Play scales and tones directly through the onboard speaker.
* **Standby Screensaver:** After 60 seconds of inactivity, the screen turns black and activates a bouncing animation displaying status and contact information:
  * `STANDBY (60s)`
  * `Touch screen to reactivate`
  * `(c) ScordaSoftware`
  * `maxscorda@gmail.com`
  * *The system instantly wakes up upon touching the screen.*

### Requirements & Setup
1. **Hardware:** STM32F746G-DISCOVERY board.
2. **Software:** Arduino IDE with STM32 board support packages and the corresponding BSP libraries (`stm32746g_discovery`).
3. Extract the project files into your Arduino sketches folder, open `ScaleShow_STM32.ino`, select the board, and compile/upload.
