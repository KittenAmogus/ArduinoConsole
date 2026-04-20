#ifndef APP_LIST_H
#define APP_LIST_H

// Apps
#include "menu/menu.h"
// #include "<name>/<name.h>"

// Debug strings
const char TITLE_MENU1[] PROGMEM = "TITLE 1";
const char TITLE_MENU2[] PROGMEM = "TITLE 2";
const char TITLE_MENU3[] PROGMEM = "TITLE 3";
const char TITLE_MENU4[] PROGMEM = "TITLE 4";
const char TITLE_MENU5[] PROGMEM = "TITLE 5";
const char TITLE_MENU6[] PROGMEM = "TITLE 6";
const char TITLE_MENU7[] PROGMEM = "TITLE 7";
const char TITLE_MENU8[] PROGMEM = "TITLE 8";
const char TITLE_MENU9[] PROGMEM = "TITLE 9";

extern MenuApp menuApp;
// extern <Name>App <name>App;

struct AppRegistry {
  App* instance;
  const char* name;
};

const AppRegistry ALL_APPS[] PROGMEM = {
  {&menuApp, TITLE_MENU},
  
  // Debug strings
  {&menuApp, TITLE_MENU1},
  {&menuApp, TITLE_MENU2},
  {&menuApp, TITLE_MENU3},
  {&menuApp, TITLE_MENU5},
  {&menuApp, TITLE_MENU6},
  {&menuApp, TITLE_MENU7},
  {&menuApp, TITLE_MENU8},
  {&menuApp, TITLE_MENU9},
  // {&<name>App, TITLE_<NAME>},
};
#define APPS_COUNT (sizeof(ALL_APPS) / sizeof(AppRegistry))

#endif // APP_LIST_H

