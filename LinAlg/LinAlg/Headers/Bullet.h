#pragma once
#include "Figure.h"
#include <ctime>

class World;

class Bullet : public Figure {
public:
	Bullet(std::vector<Triangle>& triangles, World* world, Vector startPosition, Matrix axis, double velocityFactor);
	void allignWithOriginator(Vector zAxis);
	void setAtOriginatorPosition(Vector position);

	void tick();

	void remove();

	void collide() override;

private:
	const clock_t beginTime{ std::clock() };
	const clock_t lifeTime{ 10 };

	World* _world;
};