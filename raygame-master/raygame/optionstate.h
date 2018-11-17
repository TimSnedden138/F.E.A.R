#pragma once

#include "gamestate.h"
#include "CLibary.h"
#include "RecLibary.h"

class optionstate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	float mousex = 0;
	float mousey = 0;

public:
	optionstate()
	{
		readyForNext = false;
		nextState = OPTIONS;
	}

	virtual void tick(float deltaTime)
	{
		mousex = GetMouseX();
		mousey = GetMouseY();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, LeavePause)) {
			nextState = START;
		}
	}

	virtual void draw() {
		DrawRectangleLinesEx(topScreenO, 3, INVISGREEN);
		DrawText("OPTIONS", 315, 0, 25, WHITE);
		DrawRectangleLinesEx(LeavePause, 3, INVISGREEN);
		DrawText("Leave", 0, 630, 25, WHITE);
	}
	virtual GameStates next()
	{
		return nextState;
	}
	
};