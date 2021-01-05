#pragma once
#include "Figure.h"

class World;

class Bullet : public Figure {
public:
	Bullet(std::vector<Triangle>& triangles, World* world, Vector startPosition, Matrix axis, double velocityFactor);
	void allignWithOriginator(Vector zAxis);
	void setAtOriginatorPosition(Vector position);

	void collide() override;

private:
	World* _world;
};