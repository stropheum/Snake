#pragma once
class StateManager
{
public:
	static StateManager* GetInstance();
	~StateManager() {};
	enum
	{
		START_SCREEN,
		GAME_RUNNING,
		PAUSED,
		GAME_OVER
	};
	int32_t		getState();
	void		setState(int32_t stateToSet);
	void		shutdown();
private:
	static StateManager *instance;
	StateManager();
	int32_t		mCurrentState;
};
