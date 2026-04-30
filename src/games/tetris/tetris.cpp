#include "tetris.h"

TetrisApp tetrisApp;

// private
void TetrisApp::rotateFigure(uint8_t rotateId) {}

void TetrisApp::loadFigure(uint8_t figureId) {}

void bakeFigure() {}

uint8_t isCollidingWorld() {}

uint8_t isCollidingWalls() {}


// public
void TetrisApp::onStart() {
	this->appData = (TetrisData*)globalMemory;
	memset(this->appData, 0, sizeof(TetrisData));

	// Idk, debug?
	for (uint8_t x=0; x<3; x++)
		TetrisHelper::setBlock(x, x << 1, 1);
}

void TetrisApp::onExit() {}

void TetrisApp::update() {

}

void TetrisApp::draw() {
	uint8_t page = 0;
	display.firstPage();
	do {
		for (uint8_t y = 0; y < 3; y++) {
			uint8_t yp = ((y << 1) << 1) + (y << 1);
			for (uint8_t x = 0; x < TETRIS_WIDTH; x++) {
				uint8_t xp = ((x << 1) << 1) + (x << 1);

				uint8_t state = TetrisHelper::getBlock(x, y);
				
				// Draw box
				if (state) {
					display.setDrawColor(1);
					display.drawBox(xp, yp, 6, 6);

					display.setDrawColor(0);
					display.drawBox(xp + 1, yp + 1, 4, 4);

					display.setDrawColor(1);
					display.drawBox(xp + 2, yp + 2, 2, 2);
				}
			}
		}
		page++;
	} while (display.nextPage());
}

