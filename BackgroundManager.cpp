#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <vector>
#include "gamedefs.h"
#include "BackgroundManager.h"
#include "ShapeDraw.h"


BackgroundManager* BackgroundManager::instance = NULL;

BackgroundManager::BackgroundManager()
{
}

BackgroundManager::~BackgroundManager()
{
}

/**
 * Singleton accessor method
 */
BackgroundManager* BackgroundManager::GetInstance()
{
	instance = !instance ? new BackgroundManager() : instance;
	return instance;
}

/**
 * Renders the bounding box of the playable area
 */
void BackgroundManager::render()
{
	char r, g, b;
	r = 0x00;
	g = b = 0x00;
	uint32_t max = 3 * SCALE;
	uint32_t topBoundary = (HEIGHT) * SCALE - max;
	uint32_t bottomBoundary = max;
	uint32_t leftBoundary = max;
	uint32_t rightBoundary = (WIDTH) * SCALE - max;

	for (uint32_t i = 0; i < max; i++)
	{
		// Bottom Bar
		DrawLine(leftBoundary - (max - i), i, rightBoundary + (max - i), i, r, g + 2 * i, b + 2 * i);
		// Top Bar
		DrawLine(leftBoundary - (max - i), HEIGHT * SCALE - i, rightBoundary + (max - i), HEIGHT * SCALE - i, r, g + 2 * i, b + 2 * i);
	}

	for (uint32_t i = 0; i < max; i++)
	{
		// Left Bar
		DrawLine(i, bottomBoundary - (max - i), i, topBoundary + (max - i), r, g + 2 * i, b + 2 * i);
		// Right Bar
		DrawLine(rightBoundary + i + 1, bottomBoundary - 1 - i, rightBoundary + i + 1, topBoundary + 1 + i, 
			r, g + 2 * (max - 1 - i), b + 2 * (max - 1 - i));
	}
}