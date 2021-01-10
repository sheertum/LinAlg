#pragma once
#include "Ship.h"
#include "SDL.h"
#include "Input.h"

#include <functional>
#include <memory>
#include <map>

class ShipControls
{
public:
	ShipControls(std::weak_ptr<Ship>);
	Input& getInput();

private:
	#define rollAngle 3.14159265359 / 20
	std::weak_ptr<Ship> _ship;
	std::map<SDL_KeyCode, std::function<void()>> _controls;
	Input _input;
};
