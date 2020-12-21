#pragma once
#include "Matrix.h"
#include "BoundingBox.h"

class Triangle : public Matrix
{
public:
	Triangle(Vector, Vector, Vector);
	Triangle(std::vector<double>);
private: 
	std::vector<Vector> convertToVectors(Matrix);
	BoundingBox _boundingBox;
};

