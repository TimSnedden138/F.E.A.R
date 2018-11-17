#pragma once

#include "gamestate.h"
#include "CLibary.h"
#include "RecLibary.h"
#include<iostream>

class exitstate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	float mousex = 0;
	float mousey = 0;

	bool timeToLeave = false;
public:
	exitstate()
	{
		nextState = EXIT;
	}

	virtual void tick(float deltaTime)
	{
		mousex = GetMouseX();
		mousey = GetMouseY();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, YES)) {
			nextState = START;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, NO)) {
			timeToLeave = true;
		}
	}

	virtual void draw()
	{
		DrawRectangleLinesEx(topScreenE, 3, INVISBLUE);
		DrawText("LEAVE THIS NIGHTMARE", 250, 0, 25, WHITE);
		DrawRectangleLinesEx(YES, 3, INVISBLUE);
		
		DrawText("YES", 250, 550, 35, WHITE);
		DrawRectangleLinesEx(NO, 3, INVISBLUE);
		DrawText("NO", 450, 550, 35, WHITE);
	}

	virtual GameStates next()
	{
		return nextState;
	}

	virtual bool shouldExit()
	{
		return timeToLeave;
	}
};