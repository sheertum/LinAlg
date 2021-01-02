#pragma once
#include "Figure.h"
#include <memory>

class CollisionEvent {
public:
	CollisionEvent(std::unique_ptr<Figure>&, std::unique_ptr<Figure>&);
	std::unique_ptr<Figure>& figA;
	std::unique_ptr<Figure>& figB;
};