#pragma once

#include "gamestate.h"
#include"CLibary.h"
#include"RecLibary.h"
#include"raylib.h"
#include<iostream>
class startstate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	float mousex = 0;
	float mousey = 0;
public:
	startstate()
	{
		readyForNext = false;
		nextState = START;
	}

	virtual void tick(float deltaTime)
	{
		mousex = GetMouseX();
		mousey = GetMouseY();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, start)) {
			nextState = GAME;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, story)) {
			nextState = STORY;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, leavingGame)) {
			nextState = EXIT;
		}
	}

	virtual void draw() {
		Font fontTtf = LoadFont("resources/test.ttf");
		const char msgTtfT[22] = "F.E.A.R IS YOUR ENEMY";
		const char msgTtfStart[11] = "START GAME";
		const char msgTtfStory[6] = "Story";
		const char msgTtfExit[21] = "LEAVE THIS NIGHTMARE";
		DrawTextEx(fontTtf, msgTtfT, { 245,0}, 40, 2, LIME);
		DrawTextEx(fontTtf, msgTtfStart, { 285, 155}, 40, 2, WHITE);
		DrawTextEx(fontTtf, msgTtfStory, { 285, 250 }, 40, 2, WHITE);
		DrawTextEx(fontTtf, msgTtfExit, { 285, 350 }, 40, 2, WHITE);
		DrawRectangleLinesEx(start, 5, DARKGRAY);
		DrawRectangleLinesEx(start, 1, RED);
		DrawRectangleLinesEx(story, 5, DARKGRAY);
		DrawRectangleLinesEx(story, 1.25, WHITE);
		DrawRectangleLinesEx(leavingGame, 5, DARKGRAY);
		DrawRectangleLinesEx(leavingGame, 1, BLUE);
	}
	virtual GameStates next()
	{
		return nextState;
	}
};