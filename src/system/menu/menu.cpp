/*
#include "./menu.h"
#include "../../utils/pmem.h"
#include "../../utils/input.h"
#include "../../utils/display.h"
*/
#include "menu.h"
#include "utils/pmem.h"
#include "utils/input.h"
#include "utils/display.h"

uint8_t menuState = 0;
static int8_t offset = 0;

static uint8_t needRedraw;

#define GET_STR(idx) ((const char*)pgm_read_word(&menuStrings[idx]))

static void draw() {
  needRedraw = 0;

  u8g2.firstPage();
  uint8_t i = 0;

  do {
    uint8_t posY = (i << 4);

    // Box
    u8g2.setDrawColor(i == menuState - offset);
    u8g2.drawBox(0, posY, 128, 16);

    if (i + offset >= MENU_SIZE) continue;

    // Text
    u8g2.setDrawColor(i != menuState - offset);
    u8g2.setCursor(4, posY + 12);
    u8g2.print((const __FlashStringHelper*)GET_STR(i + offset));
 
    i++;
  } while (u8g2.nextPage());
}

static uint8_t handleInput() {
  if (buttons.event.SEL) {
    buttons.event.SEL = 0;
    Serial.println((const __FlashStringHelper*)GET_STR( menuState ));
  } else if (buttons.event.DOWN) {
    needRedraw = 1;
    buttons.event.DOWN = 0;
    if (++menuState >= MENU_SIZE) menuState = 0;
  } 
  else if (buttons.event.UP) {
    needRedraw = 1;
    buttons.event.UP = 0;
    if (menuState > 0) menuState--;
    else menuState = MENU_SIZE - 1;
  }

  if (menuState < offset) {
    offset = menuState;
  } 
  else if (menuState >= offset + 4) {
    offset = menuState - 3; 
  }
  
  return 0;
}

uint8_t startMenu() {
  needRedraw = 1;
  menuState = 0;

  uint32_t ctime;

  while (1) {
    ctime = millis();
    if (ctime - buttons.lastUpdate_ms > 50) {
      updateButtons();
      buttons.lastUpdate_ms = ctime;

      handleInput();
    }

    if (needRedraw) draw();
  }

  return 0;
}

