#include "hal_conf_extra.h"
#include <stm32f7xx_hal.h>
#include <stm32746g_discovery.h>
#include <stm32746g_discovery_sdram.h>
#include <stm32746g_discovery_lcd.h>
#include <stm32746g_discovery_audio.h>
#include <stm32746g_discovery_ts.h>
#include <LTDC_F746_Discovery.h>
#include <string.h>
#include <math.h>

#include "config.h"

uint8_t rootNote = 0;
uint8_t scaleIdx = 0;
uint8_t chordIdx = 1;
boolean mute = false;

uint32_t lastActivityTime = 0;
bool isScreenReversed = false;

int16_t bounceX = 30;
int16_t bounceY = 80;
int8_t speedX = 2;
int8_t speedY = 1;
uint32_t lastBounceTick = 0;

TS_StateTypeDef TS_State;

void initDisplay();
void LeggiPulsantiTouch();
void drawUI();
void updateScreenSaverBounce();

void setup() {
  HAL_Init();
  initDisplay();
  BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  lastActivityTime = millis();
  drawUI();
}

void loop() {
  LeggiPulsantiTouch();

  if (!isScreenReversed && (millis() - lastActivityTime > INACTIVITY_TIMEOUT)) {
    isScreenReversed = true;
    BSP_LCD_Clear(LCD_COLOR_BLACK);
  }

  if (isScreenReversed && (millis() - lastBounceTick > 40)) {
    lastBounceTick = millis();
    updateScreenSaverBounce();
  }
}
