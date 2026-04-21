#ifndef SNAKE_H
#define SNAKE_H

#include "api/api.h"
#include "core/core.h"

#define SNAKE_SIZE    8
#define SNAKE_LENGTH  128
#define SNAKE_WIDTH   (SCREEN_WIDTH / SNAKE_SIZE)
#define SNAKE_HEIGHT  (SCREEN_HEIGHT / SNAKE_SIZE)

#define SNAKE_SPEED   3 // delay = (1024 >> SPEED)

const char TITLE_SNAKE[] PROGMEM = "Snake";

typedef struct {
  int8_t x  : 2;
  int8_t y  : 2;
  int8_t _unused  : 4;
} PACKED SnakeDirection;

typedef struct {
  uint8_t x : 4;
  uint8_t y : 3;
  uint8_t _unused: 1;
} PACKED SnakePos;

typedef struct {

  SnakePos snake[SNAKE_LENGTH];
  SnakePos apple;

  uint8_t appleTimer;
  uint8_t appleWhite;

  uint32_t lastUpdate;

  SnakeDirection curDirection;
  SnakeDirection nextDirection;

  uint8_t headIdx;
  uint8_t tailIdx;

} PACKED SnakeData;


class SnakeApp: public App {
  private:
    SnakeData *appData;

    uint8_t isCollide(uint8_t idx, uint8_t toApple);
    uint8_t addPart(uint8_t grow);

  public:
    const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern SnakeApp snakeApp;

#endif // SNAKE_H

