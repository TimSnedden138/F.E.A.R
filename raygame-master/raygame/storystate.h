
#pragma once

#include "gamestate.h"
#include"CLibary.h"
#include"RecLibary.h"

class storystate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	float mousex = 0;
	float mousey = 0;
public:
	storystate()
	{
		readyForNext = false;
		nextState = STORY;
	}

	virtual void tick(float deltaTime)
	{
		mousex = GetMouseX();
		mousey = GetMouseY();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, LeavePause)) {
			nextState = START;
		}
	}

	virtual void draw()
	{
		DrawRectangleLinesEx(LeavePause, 3, WHITE);
		DrawText("Leave", 0, 630, 25, WHITE);
		DrawRectangleLinesEx(topScreenSt, 3, BLUE);
		DrawText("Story", 315, 0, 28, WHITE);
		DrawText("This is a game where time is not on your side. Because they are these people\nWho don't like your kind in their town.", 10, 150, 20, WHITE);
		DrawText("And they gave you a challenge to you Yes you player It's simple\nYou complete the challenge they won't kill you\nSurvive till the sun shows it face that's it", 10, 210, 20, WHITE);
		DrawText("Do you Accept their challenge their are things to help as a bit of courtesy for those \nwho aren't afraid of fear or death", 10, 290, 20, RED);
	}

	virtual GameStates next()
	{
		return nextState;

	}
};