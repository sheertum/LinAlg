#pragma once

#include "World.h"

class CollisionHandler {
public:
	CollisionHandler(World& world);
	bool checkAABBCollisions(Figure&, Figure&);
	void checkForCollisions();
	void collideFigures();

private: 
	World& _world;
};