#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <vector>
#include "baseTypes.h"
#include "gamedefs.h"
#include "PlayerManager.h"
#include "ShapeDraw.h"
#include "InputManager.h"
#include "PickupManager.h"
#include "StateManager.h"
#include "ScoreBoardManager.h"
#include "GameManager.h"


PlayerManager* PlayerManager::instance = nullptr;
std::vector<Coord2D> tail(MAX_LENGTH);
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direction;
uint32_t playerTailSize;
std::vector<char8_t> tailColorRed(MAX_LENGTH);
std::vector<char8_t> tailColorBlue(MAX_LENGTH);

PlayerManager::PlayerManager() : gameSpeed(maxGameSpeed)
{
	tail.resize(MAX_LENGTH);
	for (auto i = 0; i < tail.size(); i++)
	{
		tail[i].x = -1;
		tail[i].y = -1;
	}
	tailColorRed.resize(MAX_LENGTH);
	tailColorBlue.resize(MAX_LENGTH);
	playerTailSize = 0;
	reset();
}

PlayerManager::~PlayerManager()
{
	if (instance) delete instance;
}

PlayerManager* PlayerManager::GetInstance()
{
	instance = !instance ? new PlayerManager() : instance;
	return instance;
}

/**
 * Initializes class members
 */
void PlayerManager::init()
{
	randomizeTailColors();
}

/**
 * Update the player state
 * @Param milliseconds: the number of milliseconds since last update call
 */
void PlayerManager::update(DWORD milliseconds)
{	
	switch (StateManager::GetInstance()->getState())
	{
		case StateManager::GAME_RUNNING:
			handleMovement(milliseconds);
			break;
		case StateManager::GAME_OVER:
			if (InputManager::GetInstance()->selectPressed())
			{
				GameManager::GetInstance()->reset();
				reset();
			}
			break;
		default: break;
	}
}

/**
 * Renders the player to the screen
 */
void PlayerManager::render()
{
	drawSquareAtPosition(position, 0x00, 0x00);
	for (uint32_t i = 0; i < playerTailSize; i++)
	{
		drawSquareAtPosition(tail[i], tailColorRed[i], tailColorBlue[i]);
	}
}

/**
 * Resets the player to the center of the screen with no tail
 */
void PlayerManager::reset()
{
	direction = STOP;

	gameSpeed = maxGameSpeed;
	position.x = WIDTH / 2;
	position.y = HEIGHT / 2;

	playerTailSize = 0;
	for (uint32_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		tail[i].x = -1;
		tail[i].y = -1;
	}

	PlaySound("Respawn.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void PlayerManager::handleMovement(DWORD milliseconds)
{
	static auto deltaTime = 0.0f;
	deltaTime += static_cast<float_t>(milliseconds);
	updateDirection();
	if (deltaTime >= gameSpeed)
	{
		deltaTime = 0.0f;
		updateTail();

		switch (direction)
		{
		case UP:
			position.y++;
			break;
		case DOWN:
			position.y--;
			break;
		case LEFT:
			position.x--;
			break;
		case RIGHT:
			position.x++;
			break;
		default: break;
		}

		handleScreenWrapping();
	}

	handleCollisions();
}

/**
 * Updates the position of all tail elements
 */
void PlayerManager::updateTail()
{
	Coord2D lastCoord = tail[0];
	Coord2D last2Coord;
	tail[0].x = position.x;
	tail[0].y = position.y;

	for (uint32_t i = 1; i < playerTailSize; i++)
	{
		last2Coord = tail[i];
		tail[i] = lastCoord;
		lastCoord = last2Coord;
	}
}

/**
 * Adds one element to the player's tail
 */
void PlayerManager::increaseTail()
{
	playerTailSize += 10;
	gameSpeed -= 0.1f;
	if (gameSpeed <= 65.0f)
	{
		gameSpeed = 65.0f;
	}
}

uint32_t PlayerManager::getTailSize()
{
	return playerTailSize;
}

/**
 * Returns the coordinates of a specific tail segment
 */
Coord2D PlayerManager::getTailAt(uint32_t index)
{
	return tail[index];
}

void PlayerManager::drawSquareAtPosition(Coord2D pos, char8_t redVal, char8_t blueVal)
{
	uint32_t renderX = pos.x * SCALE;
	uint32_t renderY = pos.y * SCALE;
	for (uint32_t i = 1; i < SCALE - 1; i++)
	{
		DrawLine(renderX + i + 1, renderY + 1, renderX + i + 1, renderY + SCALE - 1, 0x00, 0xFF, blueVal);
	}
}

void PlayerManager::updateDirection()
{
	if (InputManager::GetInstance()->upPressed() && direction != DOWN &&
		!(tail[0].x == position.x && tail[0].y == position.y + 1))
	{
		direction = UP;
	}
	else if (InputManager::GetInstance()->downPressed() && direction != UP &&
		!(tail[0].x == position.x && tail[0].y == position.y - 1))
	{
		direction = DOWN;
	}
	else if (InputManager::GetInstance()->leftPressed() && direction != RIGHT &&
		!(tail[0].x == position.x - 1 && tail[0].y == position.y))
	{
		direction = LEFT;
	}
	else if (InputManager::GetInstance()->rightPressed() && direction != LEFT &&
		!(tail[0].x == position.x + 1 && tail[0].y == position.y))
	{
		direction = RIGHT;
	}
}

void PlayerManager::handleCollisions()
{
	PickupManager* pickupManager = PickupManager::GetInstance();
	Coord2D coin = pickupManager->getCoinPosition();
	Coord2D cherry = pickupManager->getCherryPosition();

	if (position.x == coin.x && position.y == coin.y)
	{
		increaseTail();
		tail[playerTailSize - 1].x = -1;
		tail[playerTailSize - 1].y = -1;
		pickupManager->respawnCoin();
		ScoreBoardManager::GetInstance()->addScore(ScoreBoardManager::COIN_VALUE);
		PlaySound("Powerup.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	if (position.x == cherry.x && position.y == cherry.y)
	{
		increaseTail();
		tail[playerTailSize - 1].x = -1;
		tail[playerTailSize - 1].y = -1;
		pickupManager->respawnCherry();
		ScoreBoardManager::GetInstance()->addScore(ScoreBoardManager::CHERRY_VALUE);
		PlaySound("Powerup.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	if (collidesWithTail(position) || position.x < 3 || position.x >= (WIDTH - 3) || position.y < 3 || position.y >= (HEIGHT - 3))
	{
		StateManager::GetInstance()->setState(StateManager::GAME_OVER);
		PlaySound("Explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}

void PlayerManager::handleScreenWrapping()
{
	if (position.x >= WIDTH)
	{
		position.x = 0;
	}
	else if (position.x < 0)
	{
		position.x = WIDTH - 1;
	}

	if (position.y >= HEIGHT)
	{
		position.y = 0;
	}
	else if (position.y < 0)
	{
		position.y = HEIGHT - 1;
	}
}

bool8_t PlayerManager::collidesWithTail(Coord2D object)
{
	bool result = false;
	for (int i = 0; i < playerTailSize; i++)
	{
		if (object.x == tail[i].x && object.y == tail[i].y)
		{
			result = true;
		}
	}
	return result;
}

void PlayerManager::randomizeTailColors()
{
	for (int i = 0; i < tailColorRed.size(); i++)
	{
		tailColorRed[i] = (i * 25) % 255;
		tailColorBlue[i] = (i * 25) % 255;
	}
}

bool8_t PlayerManager::isMoving()
{
	return direction != STOP;
}
