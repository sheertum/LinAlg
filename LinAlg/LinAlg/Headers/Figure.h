#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Triangle.h"
#include "Shape.h"

#include <map>

class Figure {
public:
	Figure(const std::vector<Triangle>& triangles);
	Figure(const std::vector<Triangle>& triangles, Vector velocity);
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

private:
	// void addUniqueCoordinates(Vector, int&, );
	bool containtsVector(Vector vector, std::vector<double> collection);
	void calculateCenter(std::vector<double> collection, int columnCount);

	//void rotate(const Matrix&);

private:
	std::vector<Triangle> _triangles;
	std::vector<Shape> _shapes;

protected:
	Vector _center {{0,0,0}};
	Vector _xAxis {{1,0,0}};
	Vector _yAxis {{0,1,0}};
	Vector _zAxis {{0,0,1}};
	Vector _velocity;
};
