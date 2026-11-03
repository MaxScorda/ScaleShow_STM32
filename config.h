#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Global activity tracking for screen saver timeout
extern uint32_t lastActivityTime;
extern bool isScreenReversed;
const uint32_t INACTIVITY_TIMEOUT = 60000; // 60 seconds standby timeout

// Alphabetical note representations (Sharp/Flat context)
String scoreb[] = {"C", "Db", "D", "Eb",
                   "E", "F", "Gb", "G",
                   "Ab", "A", "Bb", "B"};

// Traditional Solfege representations (Do Re Mi)
String scoreN[] = {"Do", "Reb", "Re", "Mib",
                   "Mi", "Fa", "Sob", "Sol",
                   "Lab", "La", "Sib", "Si"};

// Base frequency table for notes stored in program memory (PROGMEM)
const uint16_t allNotes[] PROGMEM = {262, 277, 294, 311,
                                     330, 349, 370, 392,
                                     415, 440, 466, 494};

// Scale modulation offset tables (semitone intervals relative to root note)
PROGMEM const uint16_t scaleMod[][13] = {
  {0, 2, 4, 5, 7, 9, 11, 99},                // 0 Major
  {0, 2, 3, 5, 7, 8, 10, 99},                // 1 Minor
  {0, 1, 3, 4, 6, 8, 10, 99},                // 2 Altered
  {0, 3, 4, 7, 8, 11, 99},                   // 3 Augmented
  {0, 2, 4, 5, 7, 9, 10, 11, 99},            // 4 Bebop dominant
  {0, 2, 4, 5, 7, 8, 9, 11, 99},             // 5 Bebop major
  {0, 3, 5, 6, 7, 10, 99},                   // 6 Blues
  {0, 2, 3, 4, 7, 9, 99},                    // 7 Blues major
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 99},// 8 Chromatic
  {0, 1, 3, 4, 6, 7, 9, 10, 99},             // 9 Diminished half
  {0, 2, 3, 5, 6, 8, 9, 11, 99},             // 10 Diminished whole
  {0, 2, 3, 5, 7, 9, 10, 99},                // 11 Dorian
  {0, 1, 4, 6, 8, 10, 11, 99},               // 12 Enigmatic
  {0, 2, 3, 5, 7, 8, 10, 99},                // 13 Aeolian
  {0, 1, 3, 5, 7, 8, 10, 99},                // 14 Phrygian
  {0, 1, 4, 5, 7, 8, 10, 99},                // 15 Phrygian Dominant
  {0, 1, 5, 7, 10, 99},                      // 16 Japanese
  {0, 2, 3, 7, 8, 99},                       // 17 Hirajoshi
  {0, 1, 5, 6, 10, 99},                      // 18 Iwato
  {0, 2, 4, 6, 7, 9, 10, 99},                // 19 Lydian Dominant
  {0, 2, 4, 6, 7, 9, 11, 99},                // 20 Lydian
  {0, 1, 3, 5, 6, 8, 10, 99},                // 21 Locrian
  {0, 2, 4, 5, 7, 8, 11, 99},                // 22 Major Harmonic
  {0, 2, 3, 5, 7, 8, 11, 99},                // 23 Minor Harmonic
  {0, 2, 3, 5, 7, 9, 11, 99},                // 24 Minor Melodic
  {0, 2, 4, 5, 7, 9, 10, 99},                // 25 Mixolydian
  {0, 1, 3, 5, 7, 8, 11, 99},                // 26 Neapolitan Minor
  {0, 1, 3, 5, 7, 9, 11, 99},                // 27 Neapolitan Major
  {0, 1, 4, 5, 7, 8, 11, 99},                // 28 Oriental
  {0, 2, 4, 7, 9, 99},                       // 29 Pentatonic Major
  {0, 3, 5, 7, 10, 99},                      // 30 Pentatonic Minor
  {0, 1, 4, 5, 6, 8, 11, 99},                // 31 Persian
  {0, 2, 4, 6, 9, 10, 99},                   // 32 Prometheus
  {0, 2, 4, 6, 8, 10, 99},                   // 33 Whole Tone
  {0, 2, 3, 6, 7, 8, 11, 99},                // 34 Hungarian Minor
  {0, 3, 4, 6, 7, 9, 10, 99},                // 35 Hungarian Major
};

const char scaleNames[][12] PROGMEM = {
  "Maggiore", "Minore", "Alterata", "Aumentata", "Bebop dom", "Bebop mag",
  "Blues", "Blues mag", "Cromatica", "Dim mezzo", "Diminuita", "Dorico",
  "Enigmatica", "Eolio", "Frigio", "Frigio Dom", "Giapponese", "Hirajoshi",
  "Iwato", "Lidia dom", "Lidio", "Locrio", "Mag armon", "Min armon",
  "Min melod", "Misolidio", "Nap minore", "Napoletana", "Orientale", "Penta mag",
  "Penta min", "Persiana", "Prometheus", "Toni interi", "Ungh min", "Ungherese"
};

const uint8_t NUM_SCALES = sizeof(scaleMod) / sizeof(scaleMod[0]);

const char chordNames[][12] PROGMEM = {
  "", "Maj/Min", "Sesta", "6/9", "7a Magg", "Min 7a Mag", "Settima",
  "Minore 7a", "Dim7", "m7b5", "9a Agg", "Magg.9a", "Nona", "9a aum",
  "9a min", "11a", "11a aum", "Maj7 #11", "Lidia Dom", "13a", "Sus2",
  "Sus4", "7sus4", "5a aum", "Dim"
};

// Absolute semitone interval formulas for precise chord calculations
PROGMEM const int8_t chordIntervals[][9] = {
  {99},
  {0, 3, 7, 99},          // 1 Maj/Min
  {0, 4, 7, 9, 99},       // 2 Sesta
  {0, 4, 7, 9, 14, 99},   // 3 6/9
  {0, 4, 7, 11, 99},      // 4 7a Magg
  {0, 3, 7, 11, 99},      // 5 Min 7a Mag
  {0, 4, 7, 10, 99},      // 6 Settima
  {0, 3, 7, 10, 99},      // 7 Minore 7a
  {0, 3, 6, 9, 99},       // 8 Dim7
  {0, 3, 6, 10, 99},      // 9 m7b5
  {0, 4, 7, 10, 14, 99},  // 10 9a Agg
  {0, 4, 7, 11, 14, 99},  // 11 Magg.9a
  {0, 4, 7, 10, 14, 99},  // 12 Nona
  {0, 4, 7, 10, 15, 99},  // 13 9a aum
  {0, 4, 7, 10, 13, 99},  // 14 9a min
  {0, 4, 7, 10, 17, 99},  // 15 11a
  {0, 4, 7, 10, 18, 99},  // 16 11a aum
  {0, 4, 7, 11, 18, 99},  // 17 Maj7 #11
  {0, 4, 7, 10, 18, 99},  // 18 Lidia Dom
  {0, 4, 7, 10, 21, 99},  // 19 13a
  {0, 2, 7, 99},          // 20 Sus2
  {0, 5, 7, 99},          // 21 Sus4
  {0, 5, 7, 10, 99},      // 22 7sus4
  {0, 4, 8, 99},          // 23 5a aum
  {0, 3, 6, 99},          // 24 Dim
};

const uint8_t NUM_CHORDS = 25;

#endif
