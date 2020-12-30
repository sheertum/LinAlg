#pragma once
#include "Vector.h"
class BoundingSphere {
public:
	BoundingSphere(Vector center, std::vector<double>& data);

private:
	Vector _center;
	double _radius;
};