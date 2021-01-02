#pragma once

#include "World.h"
#include "CollisionEvent.h"

class CollisionHandler {
public:
	CollisionHandler(World& world);
	bool checkAABBCollisions(Figure&, Figure&);
	void checkForCollisions();
	void collideFigures(std::vector<CollisionEvent>&);

private: 
	World& _world;
};