#include "game.h"

GameApp gameApp;

void GameApp::onStart() {
	this->appData = (GameData*)globalMemory;
	memset(this->appData, 0, sizeof(GameData));
}

void GameApp::onExit() {}

void GameApp::update() {}

void GameApp::draw() {}

