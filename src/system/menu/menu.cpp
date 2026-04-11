#include "menu.h"
#include "utils/pmem.h"
#include "utils/input.h"
#include "utils/memory.h"
#include "utils/display.h"

// Apps
#include "system/sysinfo/sysinfo.h"

static int8_t offset = 0;

// #define GET_STR(idx) ((const char*)pgm_read_word(&menuStrings[idx]))

static void startApp() {
  switch (sharedMemory.menu.selected) {
    case (MENU_SYSINFO):
      startSysinfo();
      break;
    default:
      return;
  }
}

static void draw() {
  globalMemory.needRedraw = 0;

  u8g2.firstPage();
  uint8_t i = 0;

  do {
    uint8_t posY = (i << 4);

    // Box
    u8g2.setDrawColor(i == sharedMemory.menu.selected - offset);
    u8g2.drawBox(0, posY, 128, 16);

    if (i + offset >= MENU_SIZE) continue;

    // Text
    u8g2.setDrawColor(i != sharedMemory.menu.selected - offset);
    u8g2.setCursor(4, posY + 12);
    u8g2.print(GET_STR_U8G2_ARRAY(menuStrings[i + offset]));
 
    i++;
  } while (u8g2.nextPage());
}

static uint8_t handleInput() {
  // Select
  if (buttons.event.SEL) {
    buttons.event.SEL = 0;
    startApp();

  // Next
  } else if (buttons.event.DOWN) {
    globalMemory.needRedraw = 1;
    buttons.event.DOWN = 0;
    if (++sharedMemory.menu.selected >= MENU_SIZE) sharedMemory.menu.selected = 0;
  }

  // Previous
  else if (buttons.event.UP) {
    globalMemory.needRedraw = 1;
    buttons.event.UP = 0;
    if (sharedMemory.menu.selected > 0) sharedMemory.menu.selected--;
    else sharedMemory.menu.selected = MENU_SIZE - 1;
  }

  // Moving cursor
  if (sharedMemory.menu.selected < offset) {
    offset = sharedMemory.menu.selected;
  }
  else if (sharedMemory.menu.selected >= offset + 4) {
    offset = sharedMemory.menu.selected - 3; 
  }
 
  return 0;
}

uint8_t startMenu() {
  memset(&sharedMemory, 0, sizeof (sharedMemory));

  globalMemory.needRedraw = 1;
  sharedMemory.menu.selected = 0;

  while (1) {
    globalMemory.curTime = millis();
    if (globalMemory.curTime - buttons.lastUpdate_ms > 50) {
      updateButtons();
      buttons.lastUpdate_ms = globalMemory.curTime;

      handleInput();
    }

    if (globalMemory.needRedraw) draw();
  }

  return 0;
}

