#ifndef GAME_H
#define GAME_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_GAME[] PROGMEM = "Game";

typedef struct {
	// FPS
	uint8_t fps;
	uint32_t lastFrame;

	// TPS
	uint32_t lastUpdate;
} PACKED GameData;


class GameApp: public App {
  private:
    GameData *appData;

  public:
		const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern GameApp gameApp;

#endif // GAME_H

