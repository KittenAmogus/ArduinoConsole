#ifndef CONFIG_H
#define CONFIG_H

// #define WOKWI_MODE // SSD1306 instead of <custom>
// #define OLED_MODE  // Screen saver

#ifdef WOKWI_MODE
#define DISPLAY_TYPE    U8G2_SSD1306_128X64_NONAME_2_HW_I2C
#define DISPLAY_INIT()  U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
#else
// Your display type
#define DISPLAY_TYPE    U8G2_ST7565_ERC12864_2_4W_HW_SPI
#define DISPLAY_INIT()  U8G2_ST7565_ERC12864_2_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
#endif

// Display size
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

#endif // CONFIG_H

