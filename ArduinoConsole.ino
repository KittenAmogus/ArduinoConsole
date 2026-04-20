// System
#include "api/api.h"
#include "core/core.h"

// Display initializing
#ifdef WOKWI_MODE
DISPLAY_TYPE display(U8G2_R0, 8);
#else
DISPLAY_TYPE display(U8G2_R0, 10, 9, 8);
#endif

#define FONT (u8g2_font_u8glib_4_tr)


int main(void) {
  // Timers for U8G2
  init();

  // Display setup
  display.begin();
  display.setBusClock(8000000); // 8 MHz
  display.setContrast(16);      // 0 - 60
  display.setFont(FONT);

  // pinMode(2-7) = INPUT_PULLUP
  DDRD &= ~0xFC;
  PORTD |= 0xFC;

  // FPS timers
  uint32_t cur, lastMs, lastUpdate;
  uint8_t fps;

  Buttons btns;

  // Loop
  for (;;) {
	  cur = millis();
	
    // Update FPS
	  if (cur - lastUpdate > 256) {
	    lastUpdate = cur;
	    fps = (uint8_t)(1000 / (cur - lastMs));
	  }
	
    // Draw
	  display.firstPage();
    uint8_t page = 0; // Redraw only element which IS on page
	  do {

      // FPS is on top,
      // we do not need to redraw it every page
      if (page == 0) {
			  display.setDrawColor(1);
			  display.setCursor(128-12, 5);
			  display.print(fps);
      }

      // Buttons can be in 2nd page
      if (page < 2) {
        // Buttons
        updateButtons(&btns);
        for (uint8_t btn=0; btn<6; btn++) {
          display.setDrawColor(btns.is.mask & (1 << btn));
          display.drawBox((btn << 4) + (btn << 1) + 2, 2, 16, 16);
        }
      }

      page++;
    } while (display.nextPage());
    lastMs = cur;
  }
}

