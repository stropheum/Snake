#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <vector>
#include <stdlib.h>
#include "basetypes.h"
#include "glut.h"
#include "PlayerManager.h"
#include "ScoreBoardManager.h"
#include "SixteenSegmentManager.h"
#include "StateManager.h"


ScoreBoardManager* ScoreBoardManager::instance = NULL;

ScoreBoardManager::ScoreBoardManager() : score(0), displayedScore(0), buffer(nullptr)
{
	highScoreNames.resize(100);
	highScores.resize(100);
}

ScoreBoardManager::~ScoreBoardManager()
{
}

ScoreBoardManager* ScoreBoardManager::GetInstance()
{
	instance = !instance ? new ScoreBoardManager() : instance;
	return instance;
}

void ScoreBoardManager::init()
{
}

void ScoreBoardManager::update(DWORD milliseconds)
{
	static DWORD deltaTime = 0;
	deltaTime += milliseconds;
	if (deltaTime >= 1000)
	{
		if (PlayerManager::GetInstance()->isMoving())
		{
			score++;
		}
		deltaTime = 0;
	}
}

void ScoreBoardManager::render()
{
	if (displayedScore < score)
	{
		displayedScore++;
	}
	char8_t word[500];
	sprintf_s(word, "%06d", displayedScore);
	char8_t scoreText[500] = "score ";
	SixteenSegmentManager::GetInstance()->displayString(scoreText, 1920 / 2 - 312, 1080 - 110);
	SixteenSegmentManager::GetInstance()->displayString(word, 1920/2 - 12, 1080 - 110);

	char myWord[100] = "dale diaz snake game";
	SixteenSegmentManager::GetInstance()->displayString(myWord, 450, 25);

	if (StateManager::GetInstance()->getState() == StateManager::GAME_OVER)
	{
		SixteenSegmentManager::GetInstance()->displayString("game over", 712, 600);
		SixteenSegmentManager::GetInstance()->displayString("press space to continue", 400, 400);
	}
}

void ScoreBoardManager::drawString(char* text, float x, float y) {
	glPushMatrix();
	glColor4ub(0xff, 0xff, 0xff, 0xff);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(x, y, 0);

	for (auto character = text; *character; character++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *character);
	}
	glPopMatrix();
}

void ScoreBoardManager::displayHighScores()
{
	
}

void ScoreBoardManager::addScore(uint32_t points)
{
	score += points;
}

void ScoreBoardManager::reset()
{
	score = 0;
	displayedScore = 0;
}