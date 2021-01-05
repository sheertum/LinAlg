#pragma once
#include "Matrix.h"
#include "Vector.h"

class ProjectionMatrix {
public:
	ProjectionMatrix(double width, double height, double fieldOfView, double zNear, double zFar);

	Vector operator*(const Vector&);
	bool correctMultiply();
private:
	Matrix _data;
	double _width;
	double _height;
	bool _correct;
};