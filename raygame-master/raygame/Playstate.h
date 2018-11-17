#pragma once

#include "gamestate.h"
#include"RecLibary.h"
#include"CLibary.h"
#include"raylib.h"
#include<string>
class Playstate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	float mousex = 0;
	float mousey = 0;
	bool bullet = false;
	float rot = 0;
	Vector2 Playerposition{ 250,250 };
	Vector2 Ballposition{ 250,250 };
	Vector2 Destination{ 800,650 };
	int bulletSpeed = 300;
	float bulletAmount = 0;


public:
	Playstate()
	{
		readyForNext = false;
		nextState = GAME;
	}

	virtual void tick(float deltaTime)
	{
		rot = rand() % 360;
		DrawText(std::to_string(bulletAmount).c_str(), 50, 630, 10, WHITE);
		mousex = GetMouseX();
		mousey = GetMouseY();
		if (IsKeyDown(KEY_W)) {
			Playerposition.y--;
		}
		if (IsKeyDown(KEY_S)) {
			Playerposition.y++;
		}
		if (IsKeyDown(KEY_A)) {
			Playerposition.x--;
		}
		if (IsKeyDown(KEY_D)) {
			Playerposition.x++;
		}
		if (IsKeyPressed(KEY_SPACE)&& bulletAmount != 6) {
			bullet = true;
			Ballposition.x = mousex;
			Ballposition.y = mousey;
			bulletAmount++;
		}
		if (IsKeyPressed(KEY_R) && bulletAmount == 6) {
			bulletAmount = 0;
			bullet = false;
		}
		if (bullet == true && bulletAmount != 6) {
			if (Ballposition.x != Destination.x) {
				Ballposition.x += bulletSpeed * deltaTime;
				//DrawCircle(Ballposition.x, Ballposition.y, 5, WHITE);
				DrawPoly({ Ballposition.x,Ballposition.y }, 4, 5, 0, WHITE);
			}

		}
		if (Ballposition.y >= Destination.y && bulletAmount == 6) {
			bullet = false;
		}
	
		DrawCircle(Playerposition.x,Playerposition.y,5,DARKBLUE);
	}

	virtual void draw()
	{
		//Game Screen
			DrawRectangleLinesEx(topScreenG, 3, RED);
			DrawText("GAME STATE", 315, 0, 25, WHITE);
	}

	virtual GameStates next()
	{
		return nextState;
	}
};