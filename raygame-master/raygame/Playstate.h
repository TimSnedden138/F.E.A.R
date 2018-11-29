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
	float playerx = 250;
	float playery = 250;
	float enemyRx = 750;
	float enemyRy = 450;
	float enemyGx = 775;
	float enemyGy = 360;
	float enemyBx = 725;
	float enemyBy = 50;
	bool bulletR = false;
	bool redbullet = false;
	bool greenbullet = false;
	bool bluebullet = false;
	bool bulletG = false;
	bool bulletB = false;
	float rot = 0;
	float time = 60;
	int bulletSpeed = 300;
	int bulletAmountR = 0;
	int Health = 175;
	int bulletAmountG = 0;
	int bulletAmountB= 0;
	Texture2D background = LoadTexture("Resources/Background.png");


public:
	Playstate()
	{
		readyForNext = false;
		nextState = GAME;
	}

	virtual void tick(float deltaTime)
	{
		time = time - GetFrameTime();
		if (time > 0) {
			DrawTextureEx(background, { 0,0 }, 0, 2.25, WHITE);
			rot = rand() % 360;
			DrawText(std::to_string(bulletAmountR).c_str(), 100, 630, 20, RED);
			DrawText(std::to_string(bulletAmountG).c_str(), 50, 630, 20, GREEN);
			DrawText(std::to_string(bulletAmountB).c_str(), 150, 630, 20, BLUE);
			DrawText(std::to_string(Health).c_str(), 95, 40, 20, LIGHTBLUE);
			DrawText(std::to_string(time).c_str(), 85,80, 20, RED);
			DrawText("Health: ", 25, 40,20, LIGHTBLUE);
			DrawText("TIME: ", 25, 80, 20, RED);
			std::cout << "EnemyR: "<< enemyRx << "," << enemyRy << std::endl;
			std::cout <<"Player: "<< playerx << "," << playery << std::endl;
			mousex = GetMouseX();
			mousey = GetMouseY();
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
			if (BallpositionB.y >= OffScreen.y && bulletAmountB == 6) {
				bulletB = false;
			}
			//GREEN BULLET
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && bulletAmountG != 15) {
				bulletG = true;
				BallpositionG.x = mousex;
				BallpositionG.y = mousey;
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
			if (BallpositionG.y >= OffScreen.y && bulletAmountG == 15) {
				bulletG = false;
			}
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
			if (playerx == enemyRx && playery == enemyRy){
				Health--;
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
			if (enemypositionG.y < Playerposition.y) {
				enemypositionG.y++;
				enemyGy++;
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
			//DRAWING FOR THE GAME
			DrawCircle(enemypositionR.x, enemypositionR.y, 5, RED);
			DrawCircle(enemypositionG.x, enemypositionG.y, 5, GREEN);
			DrawCircle(enemypositionB.x, enemypositionB.y, 5, BLUE);
			DrawCircle(Playerposition.x, Playerposition.y, 5, WHITE);
		}
		if (time <= 0) {
			DrawText("YOU WIN", 300, 300, 80, RED);
		}
	}

	virtual void draw()
	{
		//Game Screen
		if (time <= 0) {
			DrawRectangleLinesEx(topScreenW, 3, GREEN);
			DrawText("WIN STATE", 315, 0, 25, WHITE);
		}
	}

	virtual GameStates next()
	{
		return nextState;
	}
};