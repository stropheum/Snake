#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <vector>
#include "baseTypes.h"
#include "gamedefs.h"
#include "PickupManager.h"
#include "ShapeDraw.h"
#include "random.h"
#include "PlayerManager.h"


PickupManager* PickupManager::instance = nullptr;

PickupManager::PickupManager()
{
	respawnCoin();
	respawnCherry();
}

PickupManager::~PickupManager()
{

}

/**
 * Singleton accessor method
 */
PickupManager* PickupManager::GetInstance()
{
	instance = !instance ? new PickupManager() : instance;
	return instance;
}

void PickupManager::render()
{
	renderCoin();
	renderCherry();
}

void PickupManager::renderCoin()
{
	uint32_t renderX = coin.x * SCALE;
	uint32_t renderY = coin.y * SCALE;
	for (uint32_t i = 0; i < SCALE; i++)
	{
		DrawLine(renderX + i, renderY, renderX + i, renderY + SCALE, 0xFF, 0xFF, 0x00);
	}
}

void PickupManager::renderCherry()
{
	uint32_t renderX = cherry.x * SCALE;
	uint32_t renderY = cherry.y * SCALE;
	for (uint32_t i = 0; i < SCALE; i ++)
	{
		DrawLine(renderX + i, renderY, renderX + i, renderY + SCALE, 0xFF, 0x00, 0x00);
	}
}

Coord2D PickupManager::getCoinPosition()
{
	return coin;
}

Coord2D PickupManager::getCherryPosition()
{
	return cherry;
}

void PickupManager::respawnCoin()
{
	do
	{
		coin.x = getRangedRandom(static_cast<int>(WALL_SIZE), static_cast<int>(WIDTH - WALL_SIZE));
		coin.y = getRangedRandom(static_cast<int>(WALL_SIZE), static_cast<int>(HEIGHT - WALL_SIZE));
	} while (coin.x == cherry.x && coin.y == cherry.y || 
		PlayerManager::GetInstance()->collidesWithTail(coin));
}

void PickupManager::respawnCherry()
{
	do
	{
		cherry.x = getRangedRandom(static_cast<int>(WALL_SIZE), static_cast<int>(WIDTH - WALL_SIZE));
		cherry.y = getRangedRandom(static_cast<int>(WALL_SIZE), static_cast<int>(HEIGHT - WALL_SIZE));
	} while (cherry.x == coin.x && cherry.y == coin.y || 
		PlayerManager::GetInstance()->collidesWithTail(cherry));
}
