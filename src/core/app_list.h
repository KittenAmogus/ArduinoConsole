#ifndef APP_LIST_H
#define APP_LIST_H

// Apps
#include "menu/menu.h"
#include "sysinfo/sysinfo.h"
// #include "<name>/<name.h>"

extern MenuApp menuApp;
extern SysinfoApp sysinfoApp;
// extern <Name>App <name>App;

struct AppRegistry {
  App* instance;
  const char* name;
};

const AppRegistry ALL_APPS[] PROGMEM = {
  {&sysinfoApp, TITLE_SYSINFO},

  {&menuApp, TITLE_MENU},
  {&menuApp, TITLE_MENU},
  // {&<name>App, TITLE_<NAME>},
};
#define APPS_COUNT (sizeof(ALL_APPS) / sizeof(AppRegistry))

#define MENU_ID 1   // Menupp id in ALL_APPS

#endif // APP_LIST_H

