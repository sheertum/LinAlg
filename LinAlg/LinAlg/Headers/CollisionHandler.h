#pragma once

#include "World.h"
#include "CollisionEvent.h"

class CollisionHandler {
public:
	CollisionHandler(std::shared_ptr<World> world);
	bool checkAABBCollisions(std::shared_ptr<Figure>& figA, std::shared_ptr<Figure>& figB);
	void checkForCollisions();
	void collideFigures(std::vector<CollisionEvent>&);

private: 
	std::shared_ptr<World> _world;
};