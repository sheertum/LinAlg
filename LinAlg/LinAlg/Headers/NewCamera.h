#pragma once

#include "Vector.h"
#include "Matrix.h"
#include <array>

class Eye {
public:
	Eye();
	Matrix pointAt(const Vector& position, const Vector& target, const Vector& up);
	void update();

	std::array<Vector, 2> getPerspective(const Vector& v1, const Vector& v2);

	Vector _position;
	Vector _direction;
	double _viewAngle;
	Matrix _view;
};