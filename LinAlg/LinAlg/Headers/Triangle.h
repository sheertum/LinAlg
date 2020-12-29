#pragma once
#include "Matrix.h"
#include "BoundingBox.h"

class Triangle : public Matrix
{
public:
	Triangle(Vector, Vector, Vector, const Vector& normal = Vector{ {1,1,1} });
	Triangle(std::vector<double>, const Vector& normal = Vector{ {1,1,1} });
	std::vector<Vector> getVectors() const;

	double getWidth() const;
	double getHeight() const;
	double getLength() const;

	double getMaxZ() const;

	Vector getNormal() const;

private: 
	std::vector<Vector> convertToVectors(Matrix);
	BoundingBox _boundingBox;
	Vector _normal;
	double _width;
	double _height;
	double _length;
};

