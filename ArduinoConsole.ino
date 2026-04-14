#include "app/app.h"
#include "system/menu/menu.h"

#ifdef WOKWI_MODE
DISPLAY_TYPE u8g2(U8G2_R0, /*RES*/ 8);
#else
DISPLAY_TYPE u8g2(U8G2_R0, /*CS*/ 10, /*DC*/ 9, /*RES*/ 8);
#endif

#define FONT u8g2_font_profont12_tf

Buttons buttons = {0};
SharedMemory sharedMemory;
GlobalMemory globalMemory;

int main(void) {
  init();

  Serial.begin( 9600 );

  // INPUT_PULLUP for buttons
  DDRD &= ~0xFC;
  PORTD |= 0xFC;

  // Init display
  u8g2.begin();
  u8g2.setFont(FONT);

  memset(&globalMemory, 0, sizeof(globalMemory));

  // Update cycle
  for (;;) {
    startMenu();
  }

  return 0;
}

