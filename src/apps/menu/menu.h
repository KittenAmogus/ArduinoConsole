#ifndef MENU_H
#define MENU_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_MENU[] PROGMEM = "* Main menu";

const uint8_t MAX_ITEMS = ((SCREEN_HEIGHT-4) / FONT_HEIGHT) - 1;

typedef struct {
  uint8_t scrollOffset;
  uint8_t selectOffset;
  uint8_t endItem;
} PACKED MenuData;

class MenuApp : public App {
  private:
    MenuData *appData;

  public:
    const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern MenuApp menuApp;

#endif // MENU_H

