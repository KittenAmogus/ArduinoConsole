#include "test.h"

TestApp testApp;

void TestApp::onStart() {

}

void TestApp::onExit() {

}

void TestApp::update() {

  sysmem.needRedraw = 1;
}

void TestApp::draw() {
  uint32_t frameStart = millis();
  uint32_t delta = frameStart - this->appData->lastFrame;
  this->appData->lastFrame = frameStart;

  if (frameStart - this->appData->lastUpdate > 256) {
    if (delta > 0) this->appData->fps = 1000 / delta;
    this->appData->lastUpdate = frameStart;
  }

  display.firstPage();
  uint8_t page = 0;
  do {
    if (page == 0) {
      display.setFont(u8g2_font_u8glib_4_tr); // Smallest readable font
      display.setDrawColor(1);
      display.setCursor(SCREEN_WIDTH - 28 - 2, 5 + 2); // Top right - offset - len("FPS 000")
      display.print(F("FPS "));
      display.print(this->appData->fps);
    }

    // Update buttons
    else if (page == 1) {
      // No system, it cannot be checked
      for (uint8_t btn=0; btn<6; btn++) {
        display.setDrawColor(sysmem.buttons.is.mask & (1 << btn));
        display.drawBox(btn << 4, 16, 16, 16);  // Y = 16, X = 16 * btn
      }
    }

    page++;
  } while (display.nextPage());
  this->appData->lastFrame = sysmem.currentTime;
}

