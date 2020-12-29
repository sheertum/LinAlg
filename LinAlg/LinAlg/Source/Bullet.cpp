#include "Bullet.h"

Bullet::Bullet(const std::vector<Triangle>& triangles, double velocity, Matrix axis, Vector center) : Figure{ triangles, velocity }
{
	_center = center;
	_axis = axis;
}
