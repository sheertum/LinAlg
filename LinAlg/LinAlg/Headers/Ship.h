#pragma once

#include "Figure.h"
#include <memory>

class World;

class Ship : public Figure
{
public:
	Ship(std::vector<Triangle>&, World*);
	void shoot();
	Vector getAim();

private:
	World* _world;
	Vector _gunMuzzle;
	Vector _aim;
	std::vector<Triangle> _bulletTriangles;
};

