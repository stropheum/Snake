#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
class InputManager
{
public:
	static InputManager	*GetInstance();
	void					init() {};
	//checkout gameframework.cpp
	Coord2D*					getCurrentMousePosition() { return nullptr; };
	//keyboard interface?
	bool8_t hasInput();
	bool8_t upPressed();
	bool8_t	downPressed();
	bool8_t leftPressed();
	bool8_t rightPressed();
	bool8_t selectPressed();

private:
	InputManager() {};

	static InputManager *instance;

};
#endif