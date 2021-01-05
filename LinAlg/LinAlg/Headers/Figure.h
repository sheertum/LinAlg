#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Triangle.h"
#include "Shape.h"
#include "BoundingSphere.h"

#include <map>

class Figure {
public:
	explicit Figure(std::vector<Triangle>& triangles, double velocity);
	void roll(double angle);
	void pitch(double angle);
	void yaw(double angle);
	
	void move();
	void accelerate(double acceleration);
	void deccelerate(double acceleration);

	void grow(double factor);
	void shrink(double factor);
	const std::vector<Triangle>& getTriangles() const;

	Vector getCenter();
	Vector getXAxis();
	Vector getYAxis();
	Vector getZAxis();
	Vector getSphereRadius();

	BoundingSphere& getBoundingSphere();

	void collide();

protected:
	bool containtsVector(Vector vector, std::vector<double> collection);
	Vector calculateSpeed();
	void calulateAxis();
	void calculateCenter(std::vector<double> collection, int columnCount);

protected:
	std::vector<Triangle> _triangles;
	std::vector<Shape> _shapes;
	Vector _center;
	Matrix _axis;
	double _velocityFactor = 0;
	BoundingSphere _boundingSphere;
};
