
#pragma once

#include "gamestate.h"
#include"CLibary.h"
#include"RecLibary.h"

class pausestate : public gamestate
{
	bool readyForNext;

public:
	pausestate()
	{
		readyForNext = false;
	}

	virtual void tick(float deltaTime)
	{
		readyForNext = IsMouseButtonPressed(0) || readyForNext;
	}

	virtual void draw()
	{
		DrawText("PAUSE MENU", GetScreenWidth() / 3, 0, 25, WHITE);
		DrawRectangleLinesEx(LeavePause, 3, RED);
		DrawText("TO LEAVE YOUR STATE Click Me", 0, 635, 20, WHITE);
	}

	virtual GameStates next()
	{
		if (readyForNext) { return GameStates::GAME; }
		else { return GameStates::PAUSE; }
	}
};