#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Shape.h"

#include <map>

class Figure : public Matrix {
public:
	Figure(const std::vector<Vector>& vectors);

	void scaleFromOrigin(double, double, double);

	Vector getVector(int index) const;
	int size() const;

	void updateCenter();
	void calculateCenter();

	void moveToOrigin();
	void moveBack();

	void createShape(std::vector<int> indices);
	const std::vector<Shape>& getShapes() const;

	//void rotate(const Matrix&);

private:
	std::vector<double> _center;
	std::vector<Shape> _shapes;
};
