#include "menu.h"

// Object init
MenuApp menuApp;

#define MENU_SEL_OFFSET  (this->appData->selectOffset)
#define MENU_SCR_OFFSET  (this->appData->scrollOffset)
#define MENU_END_ITEM    (this->appData->endItem)

// Functions
void MenuApp::onStart() {
  this->title = TITLE_MENU;
  this->appData = (MenuData*)globalMemory;
  memset(this->appData, 0, sizeof(MenuData));
  MENU_END_ITEM = getEndItem();
}

void MenuApp::onExit() {
  sysmem.nextAppId = MENU_SEL_OFFSET;
  // launchApp(MENU_SEL_OFFSET);
}

void MenuApp::update() {
  if (CHECK_EVENT_BTN(UP)) {

    sysmem.needRedraw = 1;

    if (MENU_SEL_OFFSET > 0) MENU_SEL_OFFSET--;
    else if (MENU_SEL_OFFSET == 0) {
      MENU_SEL_OFFSET = MENU_END_ITEM;
      MENU_SCR_OFFSET = (MENU_END_ITEM + 1) - MAX_ITEMS;
    }
    if (MENU_SEL_OFFSET < MENU_SCR_OFFSET) MENU_SCR_OFFSET--;

    if (MENU_SEL_OFFSET > MENU_END_ITEM) MENU_SEL_OFFSET = 0;
    if (MENU_SEL_OFFSET < MAX_ITEMS) MENU_SCR_OFFSET = 0;

  } else if (CHECK_EVENT_BTN(DOWN)) {

    sysmem.needRedraw = 1;

    if (MENU_SEL_OFFSET < MENU_END_ITEM) MENU_SEL_OFFSET++;
    else if (MENU_SEL_OFFSET == MENU_END_ITEM) {
      MENU_SEL_OFFSET = 0;
      MENU_SCR_OFFSET = 0;
    }
    if (MENU_SEL_OFFSET - MENU_SCR_OFFSET >= MAX_ITEMS) MENU_SCR_OFFSET++;

  }

  if (CHECK_EVENT_BTN(RIGHT)) {
    sysmem.needExit = 1;
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

      if (app < MENU_SCR_OFFSET || app >= MENU_SCR_OFFSET + MAX_ITEMS) continue;

      display.setDrawColor(app == MENU_SEL_OFFSET);
      display.drawBox(0, ((app - MENU_SCR_OFFSET) << 3) + 3,
          SCREEN_WIDTH, FONT_HEIGHT + 1);

      display.setDrawColor(app != MENU_SEL_OFFSET);
      display.setCursor(2, 2 + ((app + 1 - MENU_SCR_OFFSET) << 3));

      display.print(strPtr);
    }

    page++;

  } while (display.nextPage());
}

