#pragma once
#include "Vector.h"
class BoundingSphere {
public:
	BoundingSphere(Vector& center);
	void calculateRadius(const std::vector<double>&);
	Vector getCenter() const;
	double getRadius() const;

private:
	Vector& _center;
	double _radius;
};