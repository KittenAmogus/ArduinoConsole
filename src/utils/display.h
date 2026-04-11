#ifndef DISPLAY_H
#define DISPLAY_H

// Config
#include "config.h"

#ifdef WOKWI_MODE
#define DISPLAY_TYPE    U8G2_SSD1306_128X64_NONAME_2_HW_I2C
#else
// Your display type
#define DISPLAY_TYPE    U8G2_ST7565_ERC12864_2_4W_HW_SPI
#endif

// Display size
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// U8G2
#include <U8g2lib.h>
#include <SPI.h>

extern DISPLAY_TYPE u8g2;

#endif // DISPLAY_H

