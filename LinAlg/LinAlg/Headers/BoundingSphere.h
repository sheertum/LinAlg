#pragma once
#include "Vector.h"
class BoundingSphere {
public:
	BoundingSphere();
	BoundingSphere(Vector& center, std::vector<double>& data);
	Vector getCenter() const;
	double getRadius() const;

private:
	Vector& _center;
	double _radius;
};