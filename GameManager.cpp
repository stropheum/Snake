#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <vector>
#include "GameManager.h"
#include "StateManager.h"
#include "ScoreBoardManager.h"

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

/**
 * Singleton accessor method
 */
GameManager* GameManager::GetInstance()
{
	instance = !instance ? new GameManager() : instance;
	return instance;
}

/**
 * Resets the game back to start state
 */
void GameManager::reset()
{
	ScoreBoardManager::GetInstance()->reset();
	StateManager::GetInstance()->setState(StateManager::GAME_RUNNING);
}
