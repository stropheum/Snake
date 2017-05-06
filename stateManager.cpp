#define STATE_MANAGER_CPP
#include <stdarg.h>												// Header File For Variable Argument Routines
#include "baseTypes.h"
#include "stateManager.h"

StateManager* StateManager::instance = NULL;

StateManager::StateManager() : mCurrentState(START_SCREEN)
{
	
}

StateManager* StateManager::GetInstance()
{
	instance = !instance ? new StateManager() : instance;
	return instance;
}

int32_t StateManager::getState()
{
	return mCurrentState;
}

void StateManager::setState(int32_t state)
{
	mCurrentState = state;
}

void StateManager::shutdown()
{
	// Handle any end of life stuff
}