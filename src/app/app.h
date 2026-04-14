#ifndef APP_H
#define APP_H

// Just include "app/app.h" to include everything you need for writing app

// Utils
#include "utils/pmem.h"
#include "utils/memory.h"

// Custom
#include "types.h"
#include "input.h"
#include "config.h"
#include "display.h"

// Arduino
#include <SPI.h>
#include <U8g2lib.h>
#include <Arduino.h>

// ## Functions ##

uint8_t updateInput() {
  globalMemory.curTime = millis();
  if (globalMemory.curTime - buttons.lastUpdate_ms > TRESHOLD_BUTTONS) {
    buttons.lastUpdate_ms = globalMemory.curTime;
    updateButtons();
    return 1;
  } else {
    return 0;
  }
}

// ## App class

class App {
public:
  const char title[] PROGMEM;

  virtual void start()    = 0;
  virtual void update()   = 0;
  virtual void draw()     = 0;
};

class App1 : public App {
public:
  void start() override {};
};
Aoo *curApp = (void*)0;

union AppContainer {
  App1 app1;

  AppContainer()  {};
  ~AppContainer() {};
};

#endif // APP_H

