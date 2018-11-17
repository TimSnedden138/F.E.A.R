#pragma once

#include "raylib.h"

enum GameStates
{
	NONE,
	START,
	PAUSE,
	EXIT,
	SPLASH,
	GAME,
	OPTIONS,
	STORY,


};

class gamestate
{
public:
	virtual void tick(float deltaTime) {};
	virtual void draw() {};
	virtual GameStates next() { return NONE; };
	virtual bool shouldExit() { return false; }
};

void setupGameState(gamestate *&ptr, GameStates newState);
