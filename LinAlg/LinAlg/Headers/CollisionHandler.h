#pragma once

#include "World.h"
#include "CollisionEvent.h"

class CollisionHandler {
public:
	CollisionHandler(World& world);
	bool checkAABBCollisions(std::unique_ptr<Figure>& figA, std::unique_ptr<Figure>& figB);
	void checkForCollisions();
	void collideFigures(std::vector<CollisionEvent>&);

private: 
	World& _world;
};