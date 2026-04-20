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


uint8_t launchApp(uint8_t appId) {
  if (appId >= APPS_COUNT) return 0;
  // sysmem.runningApp = ...
  return 1;
}

const __FlashStringHelper* getAppName(uint8_t appId) {
  if (appId >= APPS_COUNT) return 0;

  // Читаем адрес строки напрямую из таблицы ALL_APPS, которая во Flash
  // Смещение +2 или использование структуры поможет найти name
  const char* namePtr = (const char*)pgm_read_word(&(ALL_APPS[appId].name));

  return (const __FlashStringHelper*)namePtr;
}

uint8_t getEndItem() {
  return APPS_COUNT;
}

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

  // App = menu
  sysmem.runningApp = &menuApp;
  sysmem.needRedraw = 1;

  // Start app
  sysmem.runningApp->onStart();

  uint32_t cur;

  for (;;) {

    cur = millis();

    // Update input
    if (cur - sysmem.buttons.lastUpdate_ms > 50) {
      updateButtons(&sysmem.buttons);
      sysmem.buttons.lastUpdate_ms = cur;
    }

    // Update app
    sysmem.runningApp->update();
    if (sysmem.needRedraw) {
      sysmem.needRedraw = 0;
      sysmem.runningApp->draw();
    }
  }
}

