#pragma once
#include "Vector.h"
class BoundingSphere {
public:
	BoundingSphere(Vector& center);
	void calculateRadius(const std::vector<double>&);
	Vector& getCenter() const;
	void setCenter(Vector&);
	double getRadius() const;
	void scaleRadius(double factor);

private:
	Vector& _center;
	double _radius;
};