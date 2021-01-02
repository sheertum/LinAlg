#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "ProjectionMatrix.h"
#include <array>

class Eye : public Matrix {
public:
	Eye();
	Matrix pointAt(const Vector& position, const Vector& target, const Vector& up);
	void update();

	Matrix view(const Vector& eye, double pitch, double yaw);
	Matrix lookAt(const Vector& eye, const Vector& target, const Vector& up);

	Vector getPerspective(const Vector& v1, const Vector& offset, const ProjectionMatrix& perspective);
	//std::array<Vector, 2> getPerspective(const Vector& v1, const Vector& v2);

	void newRotate(Vector&, double xAngle);

	Vector _position;
	Vector _lookat;
	int i = 0;
	double angle = 0;
private:
	void rotate(Vector& toRotate, const Vector& axes, double angle);
};