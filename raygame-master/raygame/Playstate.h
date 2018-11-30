#pragma once
#include "gamestate.h"
#include"RecLibary.h"
#include"CLibary.h"
#include"raylib.h"
#include"Values.h"
#include<string>
#include<cmath>
class Playstate : public gamestate
{
	bool readyForNext;
	GameStates nextState;
	Texture2D background = LoadTexture("Resources/Background.png");
	Texture2D enenmyR = LoadTexture("Resources/enenmyR.png");
	Texture2D enenmyB = LoadTexture("Resources/enenmyB.png");
	Texture2D enenmyG = LoadTexture("Resources/enenmyG.png");
	Texture2D player = LoadTexture("Resources/player.png");

public:
	Playstate()
	{
		readyForNext = false;
		nextState = GAME;
		Health = 25;
	}

	virtual void tick(float deltaTime)
	{
		time = time - GetFrameTime();
		if (time > 0) {
			DrawTextureEx(background, { 0,0 }, 0, 2.25, WHITE);
			distanceG = sqrt(pow(BallpositionG.x - enemypositionG.x, 2) + pow(BallpositionG.y - enemypositionG.y, 2));
			distanceB = sqrt(pow(BallpositionB.x - enemypositionB.x, 2) + pow(BallpositionB.y - enemypositionB.y, 2));
			distanceR = sqrt(pow(BallpositionR.x - enemypositionR.x, 2) + pow(BallpositionR.y - enemypositionR.y, 2));
			mousex = GetMouseX();
			mousey = GetMouseY();
			move();
			AI();	
			//RED BULLET
			if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON) && bulletAmountR != 5) {
				bulletR = true;
				BallpositionR.x = mousex;
				BallpositionR.y = mousey;
				bulletAmountR++;
				redbullet = false;
			}
			if (IsKeyPressed(KEY_R) && bulletAmountR == 5) {
				bulletAmountR = 0;
				bulletR = false;
			}
			if (bulletR == true && bulletAmountR != 5) {
				if (BallpositionR.x != OffScreen.x) {
					BallpositionR.x += bulletSpeed * deltaTime;
					DrawPoly({ BallpositionR.x,BallpositionR.y }, 4, 5, 0, RED);
				}
			}
			distanceR = sqrt(pow(BallpositionR.x - enemypositionR.x, 2) + pow(BallpositionR.y - enemypositionR.y, 2));

			if (BallpositionR.y >= OffScreen.y && bulletAmountR == 2) {
				bulletR = false;
			}
			//BLUE BULLET
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bulletAmountB != 9) {
				bulletB = true;
				BallpositionB.x = mousex;
				BallpositionB.y = mousey;
				bulletAmountB++;
				bluebullet = false;
			}
			if (IsKeyPressed(KEY_R) && bulletAmountB == 9) {
				bulletAmountB = 0;
				bulletB = false;
			}
			if (bulletB == true && bulletAmountB != 9) {
				if (BallpositionB.x != OffScreen.x) {
					BallpositionB.x += bulletSpeed * deltaTime;
					DrawPoly({ BallpositionB.x,BallpositionB.y }, 4, 5, 0, BLUE);
				}
			}
			distanceB = sqrt(pow(BallpositionB.x - enemypositionB.x, 2) + pow(BallpositionB.y - enemypositionB.y, 2));
			if (BallpositionB.y >= OffScreen.y && bulletAmountB == 9) {
				bulletB = false;
			}

			//GREEN BULLET
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && bulletAmountG != 15) {
				bulletG = true;
				BallpositionG.x = mousex;
				BallpositionG.y = mousey;
				colliderGx = mousex + 8;
				colliderGy = mousey;
				bulletAmountG++;
				greenbullet = false;

			}
			if (IsKeyPressed(KEY_R) && bulletAmountG == 15) {
				bulletAmountG = 0;
				bulletG = false;
			}
			if (bulletG == true && bulletAmountG != 15) {
				if (BallpositionG.x != OffScreen.x) {
					BallpositionG.x += bulletSpeed * deltaTime;
					DrawPoly({ BallpositionG.x,BallpositionG.y }, 4, 5, 0, GREEN);
				}
			}
			distanceG = sqrt(pow(BallpositionG.x - enemypositionG.x, 2) + pow(BallpositionG.y - enemypositionG.y, 2));

			if (BallpositionG.y >= OffScreen.y && bulletAmountG == 15) {
				bulletG = false;
				BallpositionG.x = mousex;
				BallpositionG.y = mousey;
				
			}

		}
		if (time <= 0) {
			DrawText("YOU WIN", 300, 300, 80, RED);
		}
		if (FEAR == 40){
			DrawText("YOU WIN", 300, 300, 80, RED);

		}
		if (Health == 0) {
			DrawText("YOU LOSE", 300, 300, 80, RED);
		}
		if (FEAR == -20) {
			DrawText("YOU LOSE", 300, 300, 80, RED);

		}
		if (FEAR >= 15) {
			HideCursor();
			DrawText("X: ", 25, 610, 20, WHITE);
			DrawText("Y: ", 160, 610, 20, WHITE);
			DrawText(std::to_string(mousex).c_str(), 45, 610, 20, LIME);
			DrawText(std::to_string(mousey).c_str(), 180, 610, 20, LIME);
		}
	}

	virtual void draw()
	{
		//Game Screen
		if (time <= 0) {
			DrawRectangleLinesEx(topScreenW, 3, GREEN);
			DrawText("WIN STATE", 315, 0, 25, WHITE);
		}
		if (time > 0) {
			rot = rand() % 360;
			DrawText(std::to_string(bulletAmountR).c_str(), 100, 630, 20, RED);
			DrawText(std::to_string(bulletAmountG).c_str(), 50, 630, 20, GREEN);
			DrawText(std::to_string(bulletAmountB).c_str(), 150, 630, 20, BLUE);
			DrawText(std::to_string(Health).c_str(), 95, 40, 20, LIGHTBLUE);
			DrawText(std::to_string(time).c_str(), 85, 80, 20, RED);
			DrawText(std::to_string(FEAR).c_str(), 85, 120, 20, RED);
			DrawText("Health: ", 25, 40, 20, LIGHTBLUE);
			DrawText("TIME: ", 25, 80, 20, RED);
			DrawText("FEAR: ", 25, 120, 20, RED);
			DrawTextureEx(enenmyR, { enemypositionR.x,enemypositionR.y },0, .15, LIGHTRED);
			DrawTextureEx(enenmyB, { enemypositionB.x,enemypositionB.y }, 0, .15, LIGHTBLUE);
			DrawTextureEx(enenmyG, { enemypositionG.x,enemypositionG.y }, 0, .15, LIGHTGREEN);
			DrawTextureEx(player, {Playerposition.x - 10, Playerposition.y}, 0, 1.5, WHITE);

		}
	}

	virtual GameStates next()
	{
		return nextState;
	}
	virtual void move() {
		if (IsKeyDown(KEY_W)) {
			Playerposition.y--;
			playery--;
		}
		if (IsKeyDown(KEY_S)) {
			Playerposition.y++;
			playery++;
		}
		if (IsKeyDown(KEY_A)) {
			Playerposition.x--;
			playerx--;
		}
		if (IsKeyDown(KEY_D)) {
			Playerposition.x++;
			playerx++;
		}
	}
	virtual void AI() {
		//RED AI
		if (enemypositionR.x > Playerposition.x) {
			enemypositionR.x--;
			enemyRx--;
		}
		else if (enemypositionR.x < Playerposition.x) {
			enemypositionR.x++;
			enemyRx++;
		}
		if (enemypositionR.y > Playerposition.y) {
			enemypositionR.y--;
			enemyRy--;
		}
		else if (enemypositionR.y < Playerposition.y) {
			enemypositionR.y++;
			enemyRy++;
		}
		if (playerx == enemyRx && playery == enemyRy) {
			enemyRx = rand() % 790;
			enemyRy = 450;
			enemypositionR.x = enemyRx;
			enemypositionR.y = enemyRy;
			Health--;
			FEAR--;
			bulletR = false;
		}
		if (distanceR < 20)
		{
			enemyRx = rand() % 790;
			enemyRy = 450;
			enemypositionR.x = enemyRx;
			enemypositionR.y = enemyRy;
			FEAR++;
			Health++;
			bulletR = false;
		}
		//GREEN AI
		if (enemypositionG.x > Playerposition.x) {
			enemypositionG.x--;
			enemyGx--;
		}
		else if (enemypositionG.x < Playerposition.x) {
			enemypositionG.x++;
			enemyGx++;
		}
		if (enemypositionG.y > Playerposition.y) {
			enemypositionG.y--;
			enemyGy--;
		}
		if (playerx == enemypositionG.x && playery == enemypositionG.y) {
			enemyGx = rand() % 790;
			enemyGy = 450;
			enemypositionG.x = enemyGx;
			enemypositionG.y = enemyGy;
			Health--;
			FEAR--;
			bulletG = false;
		}
		if (distanceG < 20)
		{
			enemyGx = rand() % 790;
			enemyGy = 450;
			enemypositionG.x = enemyGx;
			enemypositionG.y = enemyGy;
			FEAR++;
			Health++;
			bulletG = false;
		}
		//BLUE AI
		else if (enemypositionB.y < Playerposition.y) {
			enemypositionG.y++;
		}
		if (enemypositionB.x > Playerposition.x) {
			enemypositionB.x--;
			enemyBx--;
		}
		else if (enemypositionB.x < Playerposition.x) {
			enemypositionB.x++;
			enemyBx++;
		}
		if (enemypositionB.y > Playerposition.y) {
			enemypositionB.y--;
			enemyGy--;
		}
		else if (enemypositionB.y < Playerposition.y) {
			enemypositionB.y++;
			enemyBy++;
		}
		if (playerx == enemypositionB.x && playery == enemypositionB.y) {
			enemyBx = rand() % 790;
			enemyBy = 450;
			enemypositionB.x = enemyBx;
			enemypositionB.y = enemyBy;
			Health--;
			FEAR--;
			bulletB = false;
		}
		if (distanceB < 20)
		{
			enemyBx = rand() % 790;
			enemyBy = 450;
			enemypositionB.x = enemyBx;
			enemypositionB.y = enemyBy;
			FEAR++;
			Health++;
			bulletB = false;
		}
	}

};