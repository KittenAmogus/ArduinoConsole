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



