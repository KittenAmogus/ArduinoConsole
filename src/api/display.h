#ifndef DISPLAY_H
#define DISPLAY_H


#include "core/config.h"

// Libs
#include <U8g2lib.h>
#include <SPI.h>

// Display type and size
#ifdef WOKWI_MODE // Wokwi display (SSD1306)
#define DISPLAY_TYPE  U8G2_SSD1306_128X64_NONAME_2_HW_I2C
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#else             // Custom display
#define DISPLAY_TYPE  U8G2_ST7565_ERC12864_2_4W_HW_SPI
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#endif

extern DISPLAY_TYPE display;


#endif // DISPLAY_H

