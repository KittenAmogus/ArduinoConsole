#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_SCREENSAVER[] PROGMEM = "* Screensaver";

typedef struct {
	uint8_t offset[4];
} PACKED ScreensaverData;


class ScreensaverApp: public App {
  private:
    ScreensaverData *appData;

  public:
		const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern ScreensaverApp screensaverApp;

#endif // SCREENSAVER_H

