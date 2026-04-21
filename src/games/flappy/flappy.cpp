#include "flappy.h"

FlappyApp flappyApp;

#define FLAPPY_POSY (this->appData->posY)
#define FLAPPY_VELY (this->appData->velY)
#define FLAPPY_PIPES (this->appData->pipes)
#define FLAPPY_LAST_UPDATE (this->appData->lastUpdate)

static void resetPipe(uint8_t *lastY, FlappyPipe *pipe) {
  pipe->xOffset = (SCREEN_WIDTH); //  + FLAPPY_PIPE_WIDTH);
  // pipe->yOffset = 16;  // TODO: Random
  
  uint16_t randomVal = xorShift16();

  int8_t delta = (randomVal & 31) - 16;
  int16_t nextY = (int16_t(*lastY) + delta);
  pipe->yOffset = CLAMP(nextY, 8, (SCREEN_HEIGHT - 8 - FLAPPY_GAP));
  *lastY = pipe->yOffset;

  pipe->claimed = 0;
}

void FlappyApp::onStart() {
  this->appData = (FlappyData*)&globalMemory;
  memset(this->appData, 0, sizeof(FlappyData));
  FLAPPY_POSY.dc = (SCREEN_HEIGHT >> 1);

  this->appData->lastPipeY = (SCREEN_HEIGHT >> 1);

  for (uint8_t pipe=0; pipe<FLAPPY_PIPE_COUNT; pipe++) {
    FlappyPipe *pipePtr = &(FLAPPY_PIPES[pipe]);
    resetPipe(&this->appData->lastPipeY, pipePtr);
    pipePtr->xOffset = SCREEN_WIDTH + ((pipe * (SCREEN_WIDTH / FLAPPY_PIPE_COUNT)));
  }

  this->appData->score = -4;
}

void FlappyApp::onExit() {
  display.firstPage();
  do {
    display.setDrawColor(1);
    display.setCursor(16 + 2, FONT_HEIGHT + 2 + 16);
    display.print("Game Over");
 
    // Score
    display.setCursor(16 + 2, ((FONT_HEIGHT + 2) << 1) + 16);
    display.print("SCORE ");
    display.print(this->appData->score);
  } while (display.nextPage());

  // Wait key press for (uint8_t i=0; i<255; i++) {
  for (uint8_t i=0; i<255; i++) {
    updateButtons(&sysmem.buttons);

    if (sysmem.buttons.event.mask > 0) break;

    _delay_ms(24);
  }
}

void FlappyApp::update() {

  // Jump on every buttons (exit on SYS)
  if (sysmem.buttons.event.mask > 0) {
    sysmem.buttons.event.mask = 0;
    FLAPPY_VELY.raw = -(FLAPPY_JUMP);
  }

  // Update physics
  if (sysmem.currentTime - FLAPPY_LAST_UPDATE > FLAPPY_TPS_DELTA) {
    sysmem.needRedraw = 1;
    FLAPPY_LAST_UPDATE = sysmem.currentTime;

    FLAPPY_POSY.raw += (FLAPPY_VELY.raw);
    FLAPPY_VELY.raw += FLAPPY_GRAVITY;

    // Check collisions with world
    if (FLAPPY_POSY.dc < 0 || FLAPPY_POSY.dc > SCREEN_HEIGHT - FLAPPY_BIRD_SIZE) {
      FLAPPY_POSY.dc = 0;
      sysmem.needRedraw = 1;
      sysmem.needExit = 1;  // Game over
    }

    // Update pipes
    for (uint8_t pipe=0; pipe<FLAPPY_PIPE_COUNT; pipe++) {
      FlappyPipe *pipePtr = &(FLAPPY_PIPES[pipe]);
      if (pipePtr->xOffset <= FLAPPY_SPEED)
        resetPipe(&this->appData->lastPipeY, pipePtr);
      pipePtr->xOffset -= FLAPPY_SPEED;

      // in Pipe
      uint8_t collide = (
          (FLAPPY_X + FLAPPY_BIRD_SIZE > pipePtr->xOffset) &&
          (FLAPPY_X < pipePtr->xOffset + FLAPPY_PIPE_WIDTH));
 
      collide &= (
          // hitTop
            (FLAPPY_POSY.dc < pipePtr->yOffset) ||
          // hitBottom
            (FLAPPY_POSY.dc + FLAPPY_BIRD_SIZE > pipePtr->yOffset + FLAPPY_GAP));

      if (collide) {
        this->appData->gameOver = 1;
        break;
      } else {
        this->appData->score += !(pipePtr->claimed);
        pipePtr->claimed |= 1;
      }
    }

    sysmem.needExit |= this->appData->gameOver;
  }
}

void FlappyApp::draw() {
  uint32_t delta = sysmem.currentTime - this->appData->lastFrame;
  this->appData->fps = 1000 / delta;
  this->appData->lastFrame = sysmem.currentTime;

  display.firstPage();
  do {

    for (uint8_t pipe=0; pipe<FLAPPY_PIPE_COUNT; pipe++) {
      FlappyPipe *pipePtr = &(FLAPPY_PIPES[pipe]);

      // Base
      display.setDrawColor(1);
      display.drawBox(pipePtr->xOffset, 0, FLAPPY_PIPE_WIDTH, SCREEN_HEIGHT);

      // Gap
      display.setDrawColor(0);
      display.drawBox(pipePtr->xOffset, pipePtr->yOffset, FLAPPY_PIPE_WIDTH, FLAPPY_GAP);
      
      // Score
      display.setDrawColor(1);
      display.setFont(u8g2_font_5x7_mf);
      display.setCursor(2, 7 + 2);
      display.print(this->appData->score);

      // FPS
      display.setCursor(SCREEN_WIDTH - 2 - (5 << 1) - 5, 7 + 2);
      display.print(this->appData->fps);
    }

    display.setDrawColor(1);
    display.drawBox(FLAPPY_X, FLAPPY_POSY.dc, FLAPPY_BIRD_SIZE, FLAPPY_BIRD_SIZE);

  } while (display.nextPage());
}

