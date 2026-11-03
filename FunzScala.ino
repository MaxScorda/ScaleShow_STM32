#include "config.h"

extern int16_t bounceX;
extern int16_t bounceY;
extern int8_t speedX;
extern int8_t speedY;

void drawUI() {
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  drawHeader();
  drawScaleSection();
  drawChordSection();
  drawSidebar();
}

void drawHeader() {
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillRect(0, 0, 399, 35);
  
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font16);

  char titleBuf[45];
  char sName[12];
  strncpy_P(sName, scaleNames[scaleIdx], 11);
  sName[11] = 0;
  
  sprintf(titleBuf, " Scala: %s (%s)", sName, scoreb[rootNote].c_str());
  BSP_LCD_DisplayStringAt(5, 8, (uint8_t*)titleBuf, LEFT_MODE);

  if (mute) {
    BSP_LCD_DisplayStringAt(330, 8, (uint8_t*)"[MUTE]", LEFT_MODE);
  }
}

void drawScaleSection() {
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillRect(0, 36, 399, 138);

  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_FillRect(5, 40, 390, 20);

  BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(10, 42, (uint8_t*)" Note Alfabetiche:", LEFT_MODE);

  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

  uint8_t n = scaleLen(scaleIdx);
  char noteBuf[128] = "";
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(scaleIdx, i);
    strcat(noteBuf, scoreb[ni].c_str());
    if (i < n - 1) strcat(noteBuf, " ");
  }

  if (scaleIdx == 8 || strlen(noteBuf) > 26) {
    BSP_LCD_SetFont(&Font16);
  } else if (strlen(noteBuf) > 20) {
    BSP_LCD_SetFont(&Font20);
  } else {
    BSP_LCD_SetFont(&Font24);
  }
  BSP_LCD_DisplayStringAt(10, 68, (uint8_t*)noteBuf, LEFT_MODE);

  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_FillRect(5, 103, 390, 20);

  BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(10, 105, (uint8_t*)" Solfeggio (Do Re Mi):", LEFT_MODE);

  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

  char solBuf[128] = "";
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(scaleIdx, i);
    strcat(solBuf, scoreN[ni].c_str());
    if (i < n - 1) strcat(solBuf, " ");
  }

  if (scaleIdx == 8 || strlen(solBuf) > 30) {
    BSP_LCD_SetFont(&Font12);
  } else if (strlen(solBuf) > 22) {
    BSP_LCD_SetFont(&Font16);
  } else {
    BSP_LCD_SetFont(&Font20);
  }
  BSP_LCD_DisplayStringAt(10, 128, (uint8_t*)solBuf, LEFT_MODE);

  BSP_LCD_SetTextColor(LCD_COLOR_DARKGRAY);
  BSP_LCD_DrawHLine(0, 174, 399);
}

void drawChordSection() {
  printAcc();
}

void printAcc() {
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillRect(0, 175, 399, 96);

  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
  BSP_LCD_SetFont(&Font16);

  char cName[16] = "";
  if (chordIdx < NUM_CHORDS) {
    strncpy_P(cName, chordNames[chordIdx], 15);
  }
  
  char chordTitle[40];
  sprintf(chordTitle, "Accordo: %s", cName);
  BSP_LCD_DisplayStringAt(10, 185, (uint8_t*)chordTitle, LEFT_MODE);

  // Calcolo delle note dell'accordo basato su intervalli semitonali effettivi (indipendenti dalla lunghezza della scala)
  char chordNotes[64] = "";
  int cn = 0;
  while (cn < 8) {
    int8_t semitoneOffset = pgm_read_byte(&chordIntervals[chordIdx][cn]);
    if (semitoneOffset == 99) break;
    
    uint8_t noteIdx = (rootNote + semitoneOffset) % 12;
    strcat(chordNotes, scoreb[noteIdx].c_str());
    cn++;
    if (pgm_read_byte(&chordIntervals[chordIdx][cn]) != 99) {
      strcat(chordNotes, " ");
    }
  }

  if (strlen(chordNotes) > 20) {
    BSP_LCD_SetFont(&Font16);
  } else {
    BSP_LCD_SetFont(&Font20);
  }
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt(10, 218, (uint8_t*)chordNotes, LEFT_MODE);
}

void updateScreenSaverBounce() {
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);

  bounceX += speedX;
  bounceY += speedY;

  if (bounceX < 10 || bounceX > 260) speedX = -speedX;
  if (bounceY < 10 || bounceY > 210) speedY = -speedY;

  BSP_LCD_SetFont(&Font16);
  
  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
  BSP_LCD_DisplayStringAt(bounceX, bounceY, (uint8_t*)"STANDBY (60s)", LEFT_MODE);

  BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
  BSP_LCD_DisplayStringAt(bounceX, bounceY + 22, (uint8_t*)"(c) ScordaRecords", LEFT_MODE);

  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_DisplayStringAt(bounceX, bounceY + 44, (uint8_t*)"maxscorda@gmail.com", LEFT_MODE);

  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt(bounceX, bounceY + 66, (uint8_t*)"Touch screen to reactivate", LEFT_MODE);
}
