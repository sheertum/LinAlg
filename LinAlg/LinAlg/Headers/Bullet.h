#pragma once
#include "Figure.h"

class Bullet : public Figure {
public:
	Bullet(const std::vector<Triangle>& triangles, double velocity, Matrix axis, Vector center);
};