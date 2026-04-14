#ifndef CONFIG_H
#define CONFIG_H

// ## Global ##
#define WOKWI_MODE // SSD1306 instead of <custom>
#define OLED_MODE  // Screen saver

// ## Display ##
#ifdef WOKWI_MODE // Wokwi display (SSD1306)
#define DISPLAY_TYPE    U8G2_SSD1306_128X64_NONAME_2_HW_I2C
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#else             // Custom display
#define DISPLAY_TYPE    U8G2_ST7565_ERC12864_2_4W_HW_SPI
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#endif

// ## Input ##
#define TRESHOLD_BUTTONS 50

#endif // CONFIG_H

