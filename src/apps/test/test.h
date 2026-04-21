#ifndef TEST_H
#define TEST_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_TEST[] PROGMEM = "* Test hardware";

typedef struct {
  uint32_t lastUpdate;
  uint32_t lastFrame;
  uint8_t fps;
} PACKED TestData;

class TestApp: public App {
  private:
    TestData *appData;

  public:
    const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern TestApp testApp;

#endif // TEST_H

