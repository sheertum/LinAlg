#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Triangle.h"
#include "Shape.h"

#include <map>

class Figure : public Matrix {
public:
	Figure(const std::vector<Vector>& vectors);
	Figure(const std::vector<Triangle>& triangles);

	void scaleFromOrigin(double, double, double);

	Vector getVector(int index) const;
	int size() const;

	void updateCenter();
	void calculateCenter();

	void moveToOrigin();
	void moveBack();

	const std::vector<Triangle>& getTriangles() const;

private:
	void addUniqueCoordinates(Vector, int&);
	bool containtsVector(Vector vector);
	
	std::vector<Triangle> _triangles;
	std::vector<double> _center;
	std::vector<Shape> _shapes;
};
