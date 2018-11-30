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
			if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON) && bulletAmountR != 2) {
				bulletR = true;
				BallpositionR.x = mousex;
				BallpositionR.y = mousey;
				bulletAmountR++;
				redbullet = false;
			}
			if (IsKeyPressed(KEY_R) && bulletAmountR == 2) {
				bulletAmountR = 0;
				bulletR = false;
			}
			if (bulletR == true && bulletAmountR != 2) {
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
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bulletAmountB != 6) {
				bulletB = true;
				BallpositionB.x = mousex;
				BallpositionB.y = mousey;
				bulletAmountB++;
				bluebullet = false;
			}
			if (IsKeyPressed(KEY_R) && bulletAmountB == 6) {
				bulletAmountB = 0;
				bulletB = false;
			}
			if (bulletB == true && bulletAmountB != 6) {
				if (BallpositionB.x != OffScreen.x) {
					BallpositionB.x += bulletSpeed * deltaTime;
					DrawPoly({ BallpositionB.x,BallpositionB.y }, 4, 5, 0, BLUE);
				}
			}
			distanceB = sqrt(pow(BallpositionB.x - enemypositionB.x, 2) + pow(BallpositionB.y - enemypositionB.y, 2));
			if (BallpositionB.y >= OffScreen.y && bulletAmountB == 6) {
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
		if (FEAR == 30){
			DrawText("YOU WIN", 300, 300, 80, RED);

		}
		if (Health == 0) {
			DrawText("YOU LOSE", 300, 300, 80, RED);
		}
		if (FEAR == -20) {
			DrawText("YOU LOSE", 300, 300, 80, RED);

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
			std::cout << BallpositionB.x << BallpositionB.y << std::endl;
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
			DrawCircle(enemypositionR.x, enemypositionR.y, 5, RED);
			DrawCircle(enemypositionG.x, enemypositionG.y, 5, GREEN);
			DrawCircle(770, 360, 5, GREEN);
			DrawCircle(enemypositionB.x, enemypositionB.y, 5, BLUE);
			DrawCircle(Playerposition.x, Playerposition.y, 5, WHITE);
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
			enemyRx = 780;
			enemyRy = 450;
			enemypositionR.x = 780;
			enemypositionR.y = 450;
			Health--;
			bulletR = false;
		}
		if (distanceR < 30)
		{
			enemyRx = 780;
			enemyRy = 450;
			enemypositionR.x = 780;
			enemypositionR.y = 450;
			FEAR++;
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
			enemyGx = 795;
			enemyGy = 500;
			enemypositionG.x = 795;
			enemypositionG.y = 500;
			Health--;
			bulletG = false;
		}
		if (distanceG < 30)
		{
			enemyGx = 795;
			enemyGy = 500;
			enemypositionG.x = 795;
			enemypositionG.y = 500;
			FEAR++;
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
		if (playerx == enemyBx && playery == enemyBy) {
			enemyBx = 720;
			enemyBy = 100;
			enemypositionB.x = 720;
			enemypositionB.y = 100;
			Health--;
			bulletB = false;
		}
		if (distanceB < 30)
		{
			enemyBx = enemypositionB.x;
			enemyBy = enemypositionB.y;
			enemypositionB.x = 725;
			enemypositionB.y = 100;
			FEAR++;
			bulletB = false;
		}
	}

};