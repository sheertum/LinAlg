#pragma once

#include "Vector.h"
#include "Matrix.h"
#include <array>

class Eye : public Matrix {
public:
	Eye();
	Matrix pointAt(const Vector& position, const Vector& target, const Vector& up);
	void update();

	Vector getPerspective(const Vector& v1, const Vector& offset);
	//std::array<Vector, 2> getPerspective(const Vector& v1, const Vector& v2);

	Vector _position;
	Vector _lookat;
	int i = 0;
	double angle = 0;
private:
	void rotate(Vector& toRotate, const Vector& axes, double angle);
};