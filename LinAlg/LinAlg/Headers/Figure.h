#pragma once

#include "Matrix.h"
#include "Vector.h"

class Figure : public Matrix {
public:
	Figure(const std::vector<Vector>& vectors);

	void scaleFromOrigin(double, double, double);

	Vector getVector(int index) const;
	int size() const;

	void updateCenter();
	void calculateCenter();

private:
	std::vector<double> _center;
};
