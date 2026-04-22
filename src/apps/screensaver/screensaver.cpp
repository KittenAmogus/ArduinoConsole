#include "screensaver.h"

#define SS_OFFSET (this->appData->offset)

ScreensaverApp screensaverApp;

void ScreensaverApp::onStart() {
	this->appData = (ScreensaverData*)globalMemory;
	memset(this->appData, 0, sizeof(ScreensaverData));
}

void ScreensaverApp::onExit() {}

void ScreensaverApp::update() {
	for (uint8_t page=0; page<4; page++) {
		if ((page == 0) || page == 2) SS_OFFSET[page]++;
		else SS_OFFSET[page]--;
		SS_OFFSET[page] &= 127;
	}
	sysmem.needRedraw = 1;
}

void ScreensaverApp::draw() {
	display.firstPage();
	uint8_t page = 0;
	do {
		display.setDrawColor(1);
		display.drawBox(SS_OFFSET[page], (page << 4), 4, 16);
		page++;
	} while (display.nextPage());
}

