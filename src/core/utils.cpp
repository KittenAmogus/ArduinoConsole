#include "utils.h"
#include "core/app_list.h"


uint8_t launchApp(uint8_t appId) {
  if (appId >= APPS_COUNT) return 0;
 
  // Load
  AppRegistry *appRegPtr = (AppRegistry*)&(ALL_APPS[appId]);
  App *appPtr = (App*)pgm_read_word(&(appRegPtr->instance));
  sysmem.runningApp = appPtr;

  // Print
  Serial.print("RUN ");
  Serial.println(getAppName(appId));

  // Start app
  sysmem.runningApp->onStart();
  sysmem.nextAppId = 0xFF;

  sysmem.buttons.event.mask = 0;  // Reset events

  sysmem.needRedraw = 1;

  return 1;
}

const __FlashStringHelper* getAppName(uint8_t appId) {
  if (appId >= APPS_COUNT) return 0;

  const char* namePtr = (const char*)pgm_read_word(&(ALL_APPS[appId].name));

  return (const __FlashStringHelper*)namePtr;
}

uint8_t getEndItem() {
  return APPS_COUNT - 1;
}

extern char *__brkval;
extern char __bss_end;

// System info
int getFreeRAM() {
  char top;
  if (__brkval == 0)  return (&top - &__bss_end);
  else                return (&top - __brkval);
}

uint16_t xorShift16() {
  static uint16_t y = RANDOM_SEED;
  y ^= y << 13;
  y ^= y >> 9;
  y ^= y << 7;
  return y;
}


