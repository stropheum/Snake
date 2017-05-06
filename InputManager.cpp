#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include "InputManager.h"
#include "openGLFramework.h"

InputManager* InputManager::instance = NULL;

InputManager *InputManager::GetInstance()
{
	instance = !instance ? new InputManager() : instance;
	return instance;
}

/**
 * Returns true if user is pressing any key
 */
bool8_t InputManager::hasInput()
{
	bool8_t result = false;
	for (uint32_t i = 0; i < 255; i++)
	{
		if (g_keys->keyDown[i])
		{
			result = true;
		}
	}

	return result;
}

bool8_t InputManager::upPressed()
{
	return (g_keys->keyDown['W'] || g_keys->keyDown['w'] || g_keys->keyDown[38]);
}

bool8_t InputManager::downPressed()
{
	return (g_keys->keyDown['S'] || g_keys->keyDown['s'] || g_keys->keyDown[40]);
}

bool8_t InputManager::leftPressed()
{
	return (g_keys->keyDown['A'] || g_keys->keyDown['a'] || g_keys->keyDown[37]);
}

bool8_t InputManager::rightPressed()
{
	return (g_keys->keyDown['D'] || g_keys->keyDown['d'] || g_keys->keyDown[39]);
}

bool8_t InputManager::selectPressed()
{
	return (g_keys->keyDown[' ']);
}




