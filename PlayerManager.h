#pragma once
class PlayerManager
{
public:
	static PlayerManager* GetInstance();
	void init();
	void update(DWORD milliseconds);
	void render();
	void reset();
	void handleMovement(DWORD milliseconds);
	void updateTail();
	void increaseTail();
	uint32_t getTailSize();
	Coord2D getTailAt(uint32_t);
	~PlayerManager();
	void drawSquareAtPosition(Coord2D pos, char8_t redVal, char8_t blueVal);
	void handleCollisions();
	void handleScreenWrapping();
	bool8_t collidesWithTail(Coord2D object);
	bool8_t isMoving();
private:
	static PlayerManager* instance;
	PlayerManager();
	void updateDirection();
	void randomizeTailColors();
	Coord2D position;
	float gameSpeed;
	const uint32_t maxGameSpeed = 85.0f;
};

