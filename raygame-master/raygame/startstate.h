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
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, options)) {
			nextState = OPTIONS;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, start)) {
			nextState = GAME;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, story)) {
			nextState = STORY;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec({ mousex,mousey }, leavingGame)) {
			nextState = EXIT;
		}
		//if click on option box
		  // set nextState to option
	}

	virtual void draw() {
		DrawRectangleLinesEx(start, 5, DARKGRAY);
		DrawRectangleLinesEx(start, 1, RED);
		DrawText("START GAME", 285, 155, 40, WHITE);
		DrawRectangleLinesEx(options, 5, DARKGRAY);
		DrawRectangleLinesEx(options, 1, GREEN);
		DrawText("OPTIONS", 285, 255, 40, WHITE);
		DrawRectangleLinesEx(story, 5, DARKGRAY);
		DrawRectangleLinesEx(story, 1.25, WHITE);
		DrawText("Story", 285, 453, 30, WHITE);
		DrawRectangleLinesEx(leavingGame, 5, DARKGRAY);
		DrawRectangleLinesEx(leavingGame, 1, BLUE);
		DrawText("LEAVE THIS NIGHTMARE", 285, 355, 30, WHITE);
	}
	virtual GameStates next()
	{
		return nextState;
	}
};