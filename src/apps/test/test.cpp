#include "test.h"

TestApp testApp;

void TestApp::onStart() {

}

void TestApp::onExit() {

}

void TestApp::update() {
  // FPS
  uint32_t now = millis();
  uint32_t delta = now - this->appData->lastFrame;
  this->appData->lastFrame = now;

  if (now - this->appData->lastUpdate > 512) {
    if (delta > 0) this->appData->fps = 1000 / delta;
    this->appData->lastUpdate = now;
  }

  sysmem.needRedraw = 1;
}

void TestApp::draw() {
  display.firstPage();
  uint8_t page = 0;
  do {
    if (page == 0) {
      display.setFont(u8g2_font_u8glib_4_tr);
      display.setDrawColor(1);
      display.setCursor(SCREEN_WIDTH - 30, 7);
      display.print(F("FPS "));
      display.print(this->appData->fps);
    }

    for (uint8_t btn=0; btn<6; btn++) {
      if (sysmem.buttons.is.mask & (1 << btn)) {
        display.setDrawColor(1);
        display.drawBox(btn << 4, 16, 16, 16);
      }
    }

    page++;
  } while (display.nextPage());
}

