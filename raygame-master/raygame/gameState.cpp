#include "Gamestate.h"
#include"optionstate.h"
#include"storystate.h"
#include"exitstate.h"
#include"pausestate.h"
#include"Playstate.h"
#include"splashstate.h"
#include"startstate.h"
#include <cassert>
void setupGameState(gamestate *&ptr, GameStates newState)
{
	switch (newState)
	{
	case GameStates::NONE:  ptr = new gamestate();  break;
	case GameStates::OPTIONS: ptr = new optionstate(); break;
	case GameStates::STORY:  ptr = new storystate();  break;
	case GameStates::SPLASH:   ptr = new splashstate();   break;
	case GameStates::EXIT: ptr = new exitstate(); break;
	case GameStates::PAUSE:   ptr = new pausestate();   break;
	case GameStates::GAME:   ptr = new Playstate();   break;
	case GameStates::START:   ptr = new startstate();   break;
	default: assert(false && "Invalid state specified.");
	}
}
