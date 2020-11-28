#include "Input.h"

void Input::addBinding(SDL_Keycode code, std::function<void()> function)
{
	_bindings[code] = function;
}

void Input::handleEvents()
{
	for (auto event : _events)
	{
		if (_bindings[event.first]) {
			_bindings[event.first]();
		}
	}

	_events.clear();
}

void Input::pollEvents()
{
	SDL_Event event;

	while( SDL_PollEvent( &event ) ){
		SDL_Keycode code = event.key.keysym.sym;
		if (event.type == SDL_KEYDOWN)
		{
			_events[code] = true;
		}
	}
}
