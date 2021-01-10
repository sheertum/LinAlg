#include "ShipControls.hpp"

ShipControls::ShipControls(std::weak_ptr<Ship> ship) : _ship{ship}
{
	_controls[SDLK_LSHIFT] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->accelerate(2);
		}
	};

	_controls[SDLK_LCTRL] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->accelerate(0.5);
		}
	};

	_controls[SDLK_q] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->roll(-rollAngle);
		}
	};

	_controls[SDLK_e] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->roll(rollAngle);
		}
	};

	_controls[SDLK_w] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->pitch(rollAngle);
		}
	};

	_controls[SDLK_s] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->pitch(-rollAngle);
		}
	};

	_controls[SDLK_a] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->yaw(-rollAngle);
		}
	};

	_controls[SDLK_d] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->yaw(rollAngle);
		}
	};

	_controls[SDLK_SPACE] = [this]() {
		if (const auto& ship = _ship.lock())
		{
			ship->shoot();
		}
	};

	for (const auto& it : _controls) {
		_input.addBinding(it.first, it.second);
	}
}

Input& ShipControls::getInput()
{
	return _input;
}

