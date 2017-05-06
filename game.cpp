#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <string>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "PickupManager.h"
#include "BackgroundManager.h"
#include "ScoreBoardManager.h"

// Declarations
const char8_t CGame::mGameTitle[] = "Framework1";
CGame* CGame::sInstance = NULL;
BOOL Initialize(GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	InputManager::GetInstance()->init();
	StateManager::GetInstance()->setState(StateManager::GAME_RUNNING);
	PlayerManager::GetInstance()->init();
	ScoreBoardManager::GetInstance()->init();
}

void CGame::UpdateFrame(DWORD milliseconds)
{
	keyProcess();
	switch (StateManager::GetInstance()->getState())
	{
		case StateManager::GAME_RUNNING:
			PlayerManager::GetInstance()->update(milliseconds);
			ScoreBoardManager::GetInstance()->update(milliseconds);
			break;
		case StateManager::GAME_OVER:
			PlayerManager::GetInstance()->update(milliseconds);
			break;
		default: break;
	}
}

void CGame::DrawScene(void)
{
	startOpenGLDrawing();
	switch(StateManager::GetInstance()->getState())
	{
		case StateManager::START_SCREEN:
			break;
		case StateManager::GAME_RUNNING:
			BackgroundManager::GetInstance()->render();
			PlayerManager::GetInstance()->render();
			PickupManager::GetInstance()->render();
			ScoreBoardManager::GetInstance()->render();
			break;
		case StateManager::GAME_OVER:
			BackgroundManager::GetInstance()->render();
			PlayerManager::GetInstance()->render();
			ScoreBoardManager::GetInstance()->render();
			break;
		case StateManager::PAUSED:
			break;
		default: break;
	}
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}

void CGame::shutdown()
{
	StateManager::GetInstance()->shutdown();
}

void CGame::DestroyGame(void)
{
}
