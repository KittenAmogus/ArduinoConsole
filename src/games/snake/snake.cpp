#include "snake.h"

SnakeApp snakeApp;

#define SNAKE_ARRAY (this->appData->snake)
#define SNAKE_LAST_UPDATE (this->appData->lastUpdate)

#define SNAKE_HEAD_IDX (this->appData->headIdx)
#define SNAKE_TAIL_IDX (this->appData->tailIdx)

#define SNAKE_CUR_DIRECTION   (this->appData->curDirection)
#define SNAKE_NEXT_DIRECTION  (this->appData->nextDirection)

#define SNAKE_APPLE (this->appData->apple)


uint8_t SnakeApp::isCollide(uint8_t idx, uint8_t toApple) {
  SnakePos headPos = SNAKE_ARRAY[idx];

  if (toApple)
    return (headPos.x == SNAKE_APPLE.x && headPos.y == SNAKE_APPLE.y);

  uint8_t i = SNAKE_TAIL_IDX;
  while (i != idx) {
    if (!toApple) if (SNAKE_ARRAY[i].x == headPos.x && SNAKE_ARRAY[i].y == headPos.y) return 1;
    else if (SNAKE_ARRAY[i].x == SNAKE_APPLE.x && SNAKE_ARRAY[i].y == SNAKE_APPLE.y) return 1;
    i = (i + 1) & 127;
  }
  return 0;
}

uint8_t SnakeApp::addPart(uint8_t grow) {
  SnakePos prevPos = SNAKE_ARRAY[SNAKE_HEAD_IDX];

  SNAKE_HEAD_IDX = (SNAKE_HEAD_IDX + 1) & 127;
  if (!grow) SNAKE_TAIL_IDX = (SNAKE_TAIL_IDX + 1) & 127;
  else {
    // Randomize apple
    SNAKE_APPLE.x = xorShift16();
    SNAKE_APPLE.y = xorShift16();
  }

  if (SNAKE_HEAD_IDX == SNAKE_TAIL_IDX) return 1;

  SNAKE_ARRAY[SNAKE_HEAD_IDX] = {
    (int8_t)prevPos.x + SNAKE_CUR_DIRECTION.x,
    (int8_t)prevPos.y + SNAKE_CUR_DIRECTION.y
  };

  prevPos = SNAKE_ARRAY[SNAKE_HEAD_IDX];
  return isCollide(SNAKE_HEAD_IDX, 0);
}

void SnakeApp::onStart() {
  this->appData = (SnakeData*)globalMemory;
  memset(this->appData, 0, sizeof(SnakeData));

  for (uint8_t i=0; i<3; i++) {
    SNAKE_ARRAY[SNAKE_HEAD_IDX++] = {(SNAKE_WIDTH >> 1) + i, SNAKE_HEIGHT >> 1};
  }
  SNAKE_HEAD_IDX--;

  SNAKE_CUR_DIRECTION = SNAKE_NEXT_DIRECTION = {1, 0};
}

void SnakeApp::onExit() {

}

void SnakeApp::update() {
  if (SNAKE_CUR_DIRECTION.y == 0) {
    if (CHECK_EVENT_BTN(DOWN)) {
      SNAKE_NEXT_DIRECTION = {0, 1};
    } else if (CHECK_EVENT_BTN(UP)) {
      SNAKE_NEXT_DIRECTION = {0, -1};
    }
  } else if (SNAKE_CUR_DIRECTION.x == 0) {
    if (CHECK_EVENT_BTN(RIGHT)) {
      SNAKE_NEXT_DIRECTION = {1, 0};
    } else if (CHECK_EVENT_BTN(LEFT)) {
      SNAKE_NEXT_DIRECTION = {-1, 0};
    }
  }

  // TPS
  if (sysmem.currentTime - SNAKE_LAST_UPDATE > (1024 >> SNAKE_SPEED)) {
    this->appData->appleWhite ^= 1;
    if (this->appData->appleTimer++ & 31 == 0) this->appData->appleWhite = !this->appData->appleWhite;

    SNAKE_CUR_DIRECTION = {
      .x = SNAKE_NEXT_DIRECTION.x,
      .y = SNAKE_NEXT_DIRECTION.y
    };

    sysmem.buttons.event.mask = 0;

    sysmem.needRedraw = 1;
    SNAKE_LAST_UPDATE = sysmem.currentTime;

    if (addPart(0)) {
      sysmem.needExit = 1;
      return;
    }

    if (isCollide(SNAKE_HEAD_IDX, 1)) {
      addPart(1);
    }
  }
}

void SnakeApp::draw() {
  display.firstPage();
  do {
    uint8_t idx = SNAKE_TAIL_IDX;

    for (;;) {
	    SnakePos pos = SNAKE_ARRAY[idx];
	
	    display.setDrawColor(1);
	    display.drawBox(pos.x << 3, pos.y << 3, SNAKE_SIZE, SNAKE_SIZE);
	
	    idx = (idx + 1) & 127;
	    if (idx == SNAKE_HEAD_IDX) break;
    }

    // Apple
    display.setDrawColor(1);
    display.drawBox(SNAKE_APPLE.x << 3, SNAKE_APPLE.y << 3, SNAKE_SIZE, SNAKE_SIZE);
    display.setDrawColor(this->appData->appleWhite);
    display.drawBox((SNAKE_APPLE.x << 3) + 1, (SNAKE_APPLE.y << 3) + 1, SNAKE_SIZE-2, SNAKE_SIZE-2);

  } while (display.nextPage());
}

