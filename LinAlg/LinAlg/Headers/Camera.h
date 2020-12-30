#pragma once

#include "Vector.h"
#include "Figure.h"
#include "Limit.h"

class Camera {
public:
	Camera(Vector position, Vector lookAt, double angle, double fov, Limit clippingPlane);
	void roll(double angle);
	void pitch(double angle);
	void yaw(double angle);
	void moveUp(double distance);
	void moveRight(double distance);
	void moveBack(double distance);

private:
	Vector getXAxis();
	Vector getYAxis();
	Vector getZAxis();

public:
	double _fov;
	Vector _position;
	Vector _lookAt;
	Matrix _axis;
	Limit _clippingPlane;
};