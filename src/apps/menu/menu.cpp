#include "menu.h"

// Object init
MenuApp menuApp;

#define SEL_OFFSET  (this->appData->selectOffset)
#define SCR_OFFSET  (this->appData->scrollOffset)
#define END_ITEM    (this->appData->endItem)

// Functions
void MenuApp::onStart() {
  this->title = TITLE_MENU;
  this->appData = (MenuData*)globalMemory;
  memset(this->appData, 0, sizeof(MenuData));
  END_ITEM = getEndItem();
}

void MenuApp::onExit() {
  launchApp(SEL_OFFSET);
}

void MenuApp::update() {
  if (CHECK_EVENT_BTN(LEFT)) {

    sysmem.needRedraw = 1;

    if (SEL_OFFSET > 0) SEL_OFFSET--;
    else if (SEL_OFFSET == 0) {
      SEL_OFFSET = END_ITEM - 1;
      SCR_OFFSET = (END_ITEM) - MAX_ITEMS;
    }
    if (SEL_OFFSET < SCR_OFFSET) SCR_OFFSET--;

  } else if (CHECK_EVENT_BTN(RIGHT)) {

    sysmem.needRedraw = 1;

    if (SEL_OFFSET < END_ITEM - 1) SEL_OFFSET++;
    else if (SEL_OFFSET == END_ITEM - 1) {
      SEL_OFFSET = 0;
      SCR_OFFSET = 0;
    }
    if (SEL_OFFSET - SCR_OFFSET >= MAX_ITEMS) SCR_OFFSET++;

  }
}

void MenuApp::draw() {
  display.firstPage();

  uint8_t page = 0;
  do {

    for (uint8_t app=0; app<0xFE; app++) {
      const __FlashStringHelper *strPtr = getAppName(
          app
      );

      if (strPtr == 0) break;

      if (app < SCR_OFFSET || app >= SCR_OFFSET + MAX_ITEMS) continue;

      display.setDrawColor(app == SEL_OFFSET);
      display.drawBox(0, ((app - SCR_OFFSET) << 3) + 3,
          SCREEN_WIDTH, FONT_HEIGHT + 1);

      display.setDrawColor(app != SEL_OFFSET);
      display.setCursor(2, 2 + ((app + 1 - SCR_OFFSET) << 3));

      display.print(strPtr);
    }

    page++;

  } while (display.nextPage());
}

