#pragma once
#include <vector>
class ScoreBoardManager
{
public:
	static ScoreBoardManager* GetInstance();
	~ScoreBoardManager();
	void init();
	void update(DWORD milliseconds);
	void render();
	void addScore(uint32_t points);
	void reset();

	static const uint32_t CHERRY_VALUE = 50;
	static const uint32_t COIN_VALUE   = 100;
private:
	ScoreBoardManager();
	static void drawString(char *s, float x, float y);
	void displayHighScores();

	static ScoreBoardManager* instance;
	uint32_t score;
	uint32_t displayedScore;
	std::vector<char*>    highScoreNames;
	std::vector<uint32_t> highScores;
	char* buffer;
};

