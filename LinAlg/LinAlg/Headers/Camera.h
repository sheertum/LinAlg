#pragma once

#include "Vector.h"
#include "Figure.h"
#include "Limit.h"

class Camera {
public:
	Camera(const Vector& position, const Vector& lookAt, const Limit& xLimit, const Limit& yLimit, const Limit& zLimit);
	Camera(const Vector& position, const Vector& lookAt, const Limit& limit);

	void setXlimits(const Limit& limit);
	void setYlimits(const Limit& limit);
	void setZlimits(const Limit& limit);
	void setLimits(const Limit& limit);

	void update(const Vector& position, const Vector& lookAt);
	void update();

	void rotate(double x, double y, double z);

	std::vector<Vector> toCameraPerspective(const Vector& vector1, const Vector& vector2) const;

	double angle;
private:
	void updateTranslation(const Vector& right, const Vector& up, const Vector& direction);

private:
	Limit _xLimit;
	Limit _yLimit;
	Limit _zLimit;

	Vector _position;
	Vector _lookAt;

	Matrix _translation;
};