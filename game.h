#pragma once
class CGame
{
public:
	const char8_t *GetGameTitle() { return mGameTitle; }
	static CGame	*CreateInstance();
	static CGame	*GetInstance() { return sInstance; };
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1920;
	static const uint32_t mScreenHeight = 1080;
	static const uint32_t mBitsPerPixel = 32;
private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	CGame() {};
};
