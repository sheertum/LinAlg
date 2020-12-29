#pragma once
#include "Matrix.h"
#include "BoundingBox.h"

class Triangle : public Matrix
{
public:
	Triangle(Vector, Vector, Vector);
	Triangle(std::vector<double>);
	std::vector<Vector> getVectors() const;

	double getWidth() const;
	double getHeight() const;
	double getLength() const;

	double getMaxZ() const;

private: 
	std::vector<Vector> convertToVectors(Matrix);
	BoundingBox _boundingBox;
	double _width;
	double _height;
	double _length;
};

