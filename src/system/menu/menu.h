#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

// Menu values
typedef enum {
  MENU_SYSINFO,
  MENU_SLEEP,
  MENU_SIZE     // Not an app but app count
} MenuState;// System things
const char STR_MENU_SYSINFO[]   PROGMEM = "* System info";
const char STR_MENU_SLEEP[]     PROGMEM = "* Sleep mode";

// Menu string array
const char* const menuStrings[] PROGMEM = {
  STR_MENU_SYSINFO,
  STR_MENU_SLEEP
};

uint8_t startMenu();

#endif // MENU_H

