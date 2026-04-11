#include "src/types.h"
#include "src/config.h"
#include "src/utils/input.h"
#include "src/utils/display.h"
#include "src/system/menu/menu.h"

#ifdef WOKWI_MODE
DISPLAY_TYPE u8g2(U8G2_R0, /*RES*/ 8);
#else
DISPLAY_TYPE u8g2(U8G2_R0, /*CS*/ 10, /*DC*/ 9, /*RES*/ 8);
#endif

#define FONT u8g2_font_profont12_tf

Buttons buttons = {0};

int main(void) {
  init();

  Serial.begin( 9600 );

  // INPUT_PULLUP for buttons
  DDRD &= ~0xFC;
  PORTD |= 0xFC;

  // Init display
  u8g2.begin();
  u8g2.setFont(FONT);

  // Update cycle
  for (;;) {
    startMenu();
  }

  return 0;
}

