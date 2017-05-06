#pragma once
class BackgroundManager
{
public:
	static BackgroundManager* GetInstance();
	~BackgroundManager();
	void render();
private:
	BackgroundManager();
	static BackgroundManager* instance;
};

