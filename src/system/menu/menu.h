#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

// Menu values
typedef enum {
  MENU_SNAKE = 0,
  MENU_FLAPPY,
  MENU_TETRIS,

  MENU_SYSINFO,
  MENU_SLEEP,
  MENU_SIZE     // Not an app but app count
} MenuState;

extern uint8_t menuState;

// Menu strings
const char STR_MENU_SNAKE[]     PROGMEM = "Snake";
const char STR_MENU_FLAPPY[]    PROGMEM = "FLappy bird";
const char STR_MENU_TETRIS[]    PROGMEM = "Tetris";

const char STR_MENU_SYSINFO[]   PROGMEM = "* System info";
const char STR_MENU_SLEEP[]     PROGMEM = "* Sleep mode";

// Menu string array
const char* const menuStrings[] PROGMEM = {
  STR_MENU_SNAKE,
  STR_MENU_FLAPPY,
  STR_MENU_TETRIS,

  STR_MENU_SYSINFO,
  STR_MENU_SLEEP
};

uint8_t startMenu();

#endif // MENU_H

