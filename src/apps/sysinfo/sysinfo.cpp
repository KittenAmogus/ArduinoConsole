#include "sysinfo.h"

SysinfoApp sysinfoApp;

#define SYSINFO_SCR_OFFSET  (this->appData->scrollOffset)
#define SYSINFO_LAST_UPDATE (this->appData->lastUpdate)

void SysinfoApp::onStart() {
  this->appData = (SysinfoData*)(globalMemory);
  memset(this->appData, 0, sizeof(SysinfoData));
  SYSINFO_LAST_UPDATE = millis();
}

void SysinfoApp::onExit() {
  
}

void SysinfoApp::update() {
  sysmem.needRedraw |= (sysmem.currentTime - SYSINFO_LAST_UPDATE > 512);

  if (CHECK_EVENT_BTN(END) || CHECK_EVENT_BTN(SEL)) {
    sysmem.needRedraw |= 1;
    sysmem.needExit = 1;
  }
}

void SysinfoApp::draw() {
  SYSINFO_LAST_UPDATE = millis();

  display.firstPage();
  uint8_t page = 0;
  do {

    display.setDrawColor(1);
    // display.setCursor(FONT_WIDTH * 7, FONT_HEIGHT);
    display.setCursor(2, FONT_HEIGHT + 2);
    display.print("Uptime (sec):     ");
    display.print((sysmem.currentTime - sysmem.bootTime) / 1000);

    display.setDrawColor(1);
    display.setCursor(2, (FONT_HEIGHT + 2) << 1);
    display.print("Free RAM (bytes): ");
    display.print(getFreeRAM());

    page++;

  } while (display.nextPage());
}

