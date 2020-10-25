#ifndef __OLED_SSD1306_H
#define __OLED_SSD1306_H

#include "main.h"
#include "i2c.h"

void OLED_Init(void);
void OLED_open(void);
void OLED_clear(void);
void OLED_close(void);
void OLED_Display_String(uint8_t Page_Add, uint8_t Column_Add, char *pString, uint8_t Lingth);

#endif
