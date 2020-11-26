#pragma once

#include <unordered_map>
#include <functional>

#include "SDL_events.h"

class Input {
public:
	
	void addBinding(SDL_Keycode, std::function<void()>);

	void handleEvents();

	void pollEvents();

private:
	std::unordered_map< SDL_Keycode, std::function<void()>> _bindings;
	std::unordered_map<SDL_Keycode, bool> _events;
};