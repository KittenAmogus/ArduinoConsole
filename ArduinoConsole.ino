// System
#include "api/api.h"
#include "core/core.h"

// Apps
#include "core/app_list.h"
#include "menu/menu.h"


// Display initializing
#ifdef WOKWI_MODE
DISPLAY_TYPE display(U8G2_R0, 8);
#else
DISPLAY_TYPE display(U8G2_R0, 10, 9, 8);
#endif

SystemMemory sysmem;
uint8_t globalMemory[GLOBAL_RAM_SIZE];


int main(void) {
  // Timers for U8G2
  init();

  Serial.begin(9600);
  Serial.println("Begin");

  // Display setup
  display.begin();
  display.setBusClock(8000000); // 8 MHz
  display.setContrast(16);      // 0 - 60
  display.setFont(FONT);

  // pinMode(2-7) = INPUT_PULLUP
  DDRD &= ~0xFC;
  PORTD |= 0xFC;

  // Set boot time
  sysmem.bootTime = millis();

  // App = menu
  sysmem.runningApp = &menuApp;
  sysmem.needRedraw = 1;

  // Start app
  sysmem.runningApp->onStart();
  sysmem.nextAppId = 0xFF;

  for (;;) {

    sysmem.currentTime = millis();

    // Update input
    if (sysmem.currentTime - sysmem.buttons.lastUpdate_ms > 50) {
      updateButtons(&sysmem.buttons);
      sysmem.buttons.lastUpdate_ms = sysmem.currentTime;
    }

    // If app has no exit condition  TODO: ADD system button
    if (CHECK_EVENT_BTN(LEFT)) {
      sysmem.needExit = 1;
    }

    if (sysmem.needExit) {
      sysmem.needExit = 0;
      sysmem.runningApp->onExit();

      if (sysmem.nextAppId == 0xFF) {
        Serial.println("Relaunch menu");
        launchApp(MENU_ID);
      } else {
        Serial.print("Launch ");
        Serial.println(sysmem.nextAppId);
        launchApp(sysmem.nextAppId);
      }

    }

    // Update app
    sysmem.runningApp->update();
    if (sysmem.needRedraw) {
      sysmem.needRedraw = 0;
      sysmem.runningApp->draw();

      // Reset font
      display.setFont(FONT);
    }

  }
}

