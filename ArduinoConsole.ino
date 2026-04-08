#include "config.h"
#include "utils/display.h"

DISPLAY_TYPE u8g2(U8G2_R0, /*CS*/ 10, /*DC*/ 9, /*RES*/ 8);

int main(void) {
  init();

  // setup();
  u8g2.begin();

  for (;;) {
    // loop();
  }

  return 0;
}

