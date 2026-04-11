#include "sysinfo.h"
#include "utils/pmem.h"
#include "utils/input.h"
#include "utils/memory.h"
#include "utils/display.h"


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

static void handleInput() {
  // TODO: Add scrolling
  if (buttons.event.END) {
    buttons.event.END = 0;
    globalMemory.needExit = 1;
  }
}

void startSysinfo() {
  memset(&sharedMemory, 0, sizeof(sharedMemory));
  globalMemory.needRedraw = 1;
  globalMemory.needExit = 0;
  u8g2.clearBuffer();

  for (;;) {

    // Input
    globalMemory.curTime = millis();
    if (globalMemory.curTime - buttons.lastUpdate_ms > BUTTONS_TRESHOLD) {
      buttons.lastUpdate_ms = globalMemory.curTime;
      updateButtons();
      handleInput();
    }

    // Draw
    if (globalMemory.needRedraw) draw();

    if (globalMemory.needExit) break;
  }

  return;
}

