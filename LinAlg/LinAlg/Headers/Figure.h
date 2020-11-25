#pragma once

#include "Matrix.h"
#include "Vector.h"

class Figure : public Matrix {
public:
	Figure(const std::vector<Vector>& vectors);

	Vector getVector(int index) const;
	int size() const;

private:
	std::vector<double> _center;
};
