#pragma once

#include "Figure.h"

class World;

class Target : public Figure{
public:
	Target(std::vector<Triangle>& triangles, World* world, Vector position, double velocity, int growthLimit, bool isGrowing);
	void tick();

	void collide() override;

private:
	World* _world;
	int _grow;
	int _growLimit;
	bool _isGrowing;
};