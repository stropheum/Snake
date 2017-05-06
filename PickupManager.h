#pragma once
class PickupManager
{
public:
	~PickupManager();
	static PickupManager* GetInstance();
	void render();
	void renderCoin();
	void renderCherry();
	Coord2D getCoinPosition();
	Coord2D getCherryPosition();
	void respawnCoin();
	void respawnCherry();
private:
	PickupManager();
	static PickupManager* instance;
	Coord2D coin;
	Coord2D cherry;
};

