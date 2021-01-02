#pragma once

#include "Figure.h"
#include <memory>

class World;

class Ship : public Figure
{
public:
	Ship(const std::vector<Triangle>&, World*);
	void shoot();
	Vector getAim();
private:
	World* _world;
	Vector _gunMuzzle;
	Vector _aim;
};

