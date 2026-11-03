#include "config.h"

void drawSidebar() {
  BSP_LCD_SetTextColor(0xFF333333);
  BSP_LCD_FillRect(400, 0, 80, 272);
  BSP_LCD_SetFont(&Font12);

  struct Btn {
    uint16_t y;
    const char* label;
    uint32_t bg_color;
    uint32_t text_color;
  };

  Btn buttons[] = {
    { 0,   "Scala +", 0xFF00FFFF, 0xFF000000 },
    { 35,  "Scala -", 0xFF00FFFF, 0xFF000000 },
    { 70,  "Nota <",  0xFF00FF00, 0xFF000000 },
    { 105, "Nota >",  0xFF00FF00, 0xFF000000 },
    { 140, "Acc +",   0xFFFFFF00, 0xFF000000 },
    { 175, "Acc -",   0xFFFFFF00, 0xFF000000 },
    { 210, "PLAY",    0xFF0000FF, 0xFFFFFFFF },
    { 245, "MUTE",    0xFFFF0000, 0xFFFFFFFF }
  };

  for (int i = 0; i < 8; i++) {
    BSP_LCD_SetTextColor(buttons[i].bg_color);
    BSP_LCD_FillRect(401, buttons[i].y, 78, 30);
    
    BSP_LCD_SetBackColor(buttons[i].bg_color);
    BSP_LCD_SetTextColor(buttons[i].text_color);
    
    BSP_LCD_DisplayStringAt(405, buttons[i].y + 8, (uint8_t*)buttons[i].label, LEFT_MODE);
  }
}
