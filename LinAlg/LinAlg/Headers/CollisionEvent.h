#pragma once
#include "Figure.h"
#include <memory>

class CollisionEvent {
public:
	CollisionEvent(std::shared_ptr<Figure>&, std::shared_ptr<Figure>&);
	std::shared_ptr<Figure>& figA;
	std::shared_ptr<Figure>& figB;
};