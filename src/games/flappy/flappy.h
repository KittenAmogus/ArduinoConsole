#ifndef FLAPPY_H
#define FLAPPY_H

#include "api/api.h"
#include "core/core.h"

const char TITLE_FLAPPY[] PROGMEM = "Flappy Bird";

#define FLAPPY_TPS_DELTA  (1000 / 20)

#define FLAPPY_X  (SCREEN_WIDTH >> 2)
#define FLAPPY_SPEED  2
#define FLAPPY_GAP    24
#define FLAPPY_PIPE_COUNT 4

#define FLAPPY_PIPE_WIDTH 12
#define FLAPPY_BIRD_SIZE  6

#define FLAPPY_GRAVITY  (128)
#define FLAPPY_JUMP     (777)

typedef struct {
  uint16_t xOffset: 8;
  uint16_t yOffset: 6;
  uint16_t claimed: 1;

  uint16_t _unused: 1;
} PACKED FlappyPipe;

typedef struct {
  union {
    struct {
      uint16_t fp:  8;
      int16_t dc:   8;
    };
    int16_t raw;
  };
} PACKED FlappyFixed;

typedef struct {
  uint16_t score;
  uint8_t lastPipeY;
  uint8_t gameOver;
  uint32_t lastUpdate;

  uint32_t lastFrame;
  uint8_t fps;

  FlappyFixed velY;
  FlappyFixed posY;

  FlappyPipe pipes[FLAPPY_PIPE_COUNT];
} PACKED FlappyData;

class FlappyApp : public App {
  private:
    FlappyData *appData;

  public:
    const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern FlappyApp flappyApp;

#endif // FLAPPY_H

