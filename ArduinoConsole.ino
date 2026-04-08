#include "config.h"
#include "utils/display.h"

#ifdef WOKWI_MODE
DISPLAY_TYPE u8g2(U8G2_R0, /*RES*/ 8);
#else
DISPLAY_TYPE u8g2(U8G2_R0, /*CS*/ 10, /*DC*/ 9, /*RES*/ 8);
#endif

int main(void) {
  init();

  // setup();
  u8g2.begin();
  
  // Test
  u8g2.firstPage();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  do {
    u8g2.drawStr(0, 24, "Hello, World!");
  } while (u8g2.nextPage());

  for (;;) {
    // loop();
  }

  return 0;
}

