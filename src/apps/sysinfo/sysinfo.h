#ifndef SYSINFO_H
#define SYSINFO_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_SYSINFO[] PROGMEM = "* Sysinfo";

typedef struct {
  uint8_t scrollOffset;
  uint32_t lastUpdate;
} PACKED SysinfoData;

class SysinfoApp : public App {
  private:
    SysinfoData *appData;

  public:
    const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern SysinfoApp sysinfoApp;


#endif // SYSINFO_H


