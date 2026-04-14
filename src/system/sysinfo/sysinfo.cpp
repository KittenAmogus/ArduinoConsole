#include "sysinfo.h"


static void draw() {
  globalMemory.needRedraw = 0;


  u8g2.firstPage();
  do {
    // Software version
    u8g2.setDrawColor(1);
    u8g2.setCursor(4, 12);
    u8g2.print(GET_STR_U8G2_FLASH(SOFTWARE_VERSION));

  } while (u8g2.nextPage());
}

static uint8_t handleInput() {
  // TODO: Add scrolling
  if (buttons.event.END) {
    buttons.event.END = 0;
    globalMemory.needExit = 1;
    return 1;
  }
  return 0;
}

void startSysinfo() {
  memset(&sharedMemory, 0, sizeof(sharedMemory));
  globalMemory.needRedraw = 1;
  globalMemory.needExit = 0;
  u8g2.clearBuffer();

  while (!globalMemory.needExit) {
    if (updateInput()) {
      if (handleInput()) break;
    }

    // Draw
    if (globalMemory.needRedraw) draw();
  }

  return;
}

