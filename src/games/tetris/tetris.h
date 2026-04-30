#ifndef TETRIS_H
#define TETRIS_H

#include "api/api.h"
#include "core/core.h"

#define TETRIS_WIDTH	10
#define TETRIS_HEIGHT	20

#define TETRIS_OFFY	4
#define TETRIS_OFFX	2

const char TITLE_TETRIS[] PROGMEM = "Tetris (c)";	// (c) is for fun

typedef enum {
	TET_I,
	TET_O,
	TET_T
	TET_S,
	TET_Z,
	TET_J,
	TET_L,
} TetrisMask;

typedef enum {
	TET_NOCOL	= 0,
	TET_WALL,
	TET_MASK,
	TET_FLOOR
} TetrisCollide;

typedef struct {
	union {
		struct {
			uint16_t row3	: 4;
			uint16_t row2	: 4;
			uint16_t row1	: 4;
			uint16_t row0	: 4;
		};
		uint16_t mask;
	};
} PACKED TetrisFigure;

const uint16_t const tetrisMasks[] PROGMEM = {
	0x4444,	// TET_I
	0x0660,	// TET_O
	0x04E0,	// TET_T
	0x07E0,	// TET_S
	0x0E70,	// TET_Z
	0x0226,	// TET_J
	0x0446	// TET_L
};

typedef struct {
	uint16_t score;
	uint8_t gameSpeed;
	uint8_t offsetY;
	uint8_t offsetX;

	// uint8_t field[20];
	uint16_t field[TETRIS_HEIGHT];	// Just for testing, simplifying set/get

	TetrisFigure activeFigure;
	uint8_t rotate;

	// FPS
	uint8_t fps;
	uint32_t lastFrame;

	// TPS
	uint32_t lastUpdate;
} PACKED TetrisData;

class TetrisApp: public App {
  private:
    TetrisData *appData;

		void rotateFigure(uint8_t rotateId);
		void loadFigure(uint8_t figureId);
		void bakeFigure();

		uint8_t isCollidingWorld();
		uint8_t isCollidingWalls();

  public:
		const char *title;
	  void onStart() override;
	  void onExit() override;
	  void update() override;
	  void draw() override;
};
extern TetrisApp tetrisApp;

// Field helper
static class TetrisHelper {
	static uint8_t getBlock(uint8_t x, uint8_t y) {
		return (tetrisApp->appData->field[y] & (1 << (15 - x)));
	}

	static void setBlock(uint8_t x, uint8_t y, uint8_t state) {
		tetrisApp->appData->field[y] &= (state << (15 - x));
	}
};

#endif // TETRIS_H

