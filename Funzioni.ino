#include "config.h"

#define AUDIO_SAMPLE_RATE 8000
int16_t audioBuffer[256];
bool audioInitialized = false;

// Initialize hardware display layers and audio subsystem safely
void initDisplay() {
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(0);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_DisplayOn();

  if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_SPEAKER, 40, AUDIO_SAMPLE_RATE) == AUDIO_OK) {
    audioInitialized = true;
  }
}

// Generate and play a sinusoidal tone via audio DMA output
void playTone(uint16_t frequency, uint16_t durationMs) {
  if (mute || !audioInitialized || frequency == 0) return;

  uint32_t sampleCount = 128;
  for (uint32_t i = 0; i < sampleCount; i++) {
    float t = (float)i / (float)AUDIO_SAMPLE_RATE;
    audioBuffer[i] = (int16_t)(3000.0 * sin(2.0 * 3.1415926535 * frequency * t));
  }

  BSP_AUDIO_OUT_Play((uint16_t*)audioBuffer, sampleCount * 2);
  HAL_Delay(durationMs);
  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
}

// Calculate frequency for specific pitch class and semitone offset
int toneAt(uint8_t pc, int semis) {
  int nota = pgm_read_word(&allNotes[rootNote]);
  int base = nota;
  while (semis >= 12) {
    nota *= 2;
    semis -= 12;
  }
  int step = pgm_read_word(&allNotes[pc]);
  if (step < base) step *= 2;
  return (int)((long)nota * step / base);
}

// Play full musical scale sequentially note by note
void playScale() {
  if (mute) return;
  uint8_t n = scaleLen(scaleIdx);

  for (uint8_t i = 0; i < n; i++) {
    int iv = pgm_read_word(&scaleMod[scaleIdx][i]);
    uint8_t pc = (rootNote + iv) % 12;
    int freq = toneAt(pc, iv);
    
    playTone(freq, 80);
    HAL_Delay(10);
  }
}

// Read touchscreen inputs and dispatch user navigation commands
void LeggiPulsantiTouch() {
  BSP_TS_GetState(&TS_State);
  if (TS_State.touchDetected) {
    // Reset inactivity timer on any user touch interaction
    lastActivityTime = millis();

    // Wake up from screen saver standby mode if active
    if (isScreenReversed) {
      isScreenReversed = false;
      drawUI();
      HAL_Delay(200);
      return;
    }

    uint16_t tx = TS_State.touchX[0];
    uint16_t ty = TS_State.touchY[0];

    // Handle touch actions within sidebar region (X >= 400)
    if (tx >= 400) {
      if (ty >= 0 && ty <= 32) {
        scaleIdx = (scaleIdx + 1) % NUM_SCALES;
        onScaleChanged();
      } 
      else if (ty >= 35 && ty <= 67) {
        scaleIdx = (scaleIdx + NUM_SCALES - 1) % NUM_SCALES;
        onScaleChanged();
      } 
      else if (ty >= 70 && ty <= 102) {
        uint8_t old = rootNote;
        rootNote = (rootNote + 11) % 12;
        onRootChanged(old);
      } 
      else if (ty >= 105 && ty <= 137) {
        uint8_t old = rootNote;
        rootNote = (rootNote + 1) % 12;
        onRootChanged(old);
      } 
      else if (ty >= 140 && ty <= 172) {
        chordIdx = (chordIdx + 1) % NUM_CHORDS;
        if (chordIdx == 0) chordIdx = 1;
        printAcc();
      } 
      else if (ty >= 175 && ty <= 207) {
        chordIdx = (chordIdx <= 1) ? (NUM_CHORDS - 1) : (chordIdx - 1);
        printAcc();
      } 
      else if (ty >= 210 && ty <= 242) {
        playScale();
      } 
      else if (ty >= 245 && ty <= 271) {
        mute = !mute;
        drawHeader();
      }
      HAL_Delay(200);
    }
  }
}

// Callback triggered when root note changes
void onRootChanged(uint8_t oldNote) {
  drawHeader();
  drawScaleSection();
  drawChordSection();
}

// Callback triggered when scale type changes
void onScaleChanged() {
  drawHeader();
  drawScaleSection();
  drawChordSection();
}

// Calculate total number of notes present in given scale
uint8_t scaleLen(uint8_t idx) {
  uint8_t n = 0;
  while (n < 13 && pgm_read_word(&scaleMod[idx][n]) != 99) n++;
  return n;
}

// Retrieve pitch class for scale degree
uint8_t scaleNote(uint8_t idx, uint8_t deg) {
  return (rootNote + pgm_read_word(&scaleMod[idx][deg])) % 12;
}
