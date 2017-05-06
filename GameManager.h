#pragma once
class PlayerManager;
class GameManager
{
public:
	static GameManager* GetInstance();
	~GameManager();
	void reset();
private:
	static GameManager* instance;
	GameManager();
};

