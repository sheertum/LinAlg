#include "Camera.h"
#include "UnitaryMatrix.h"

#include <vector>

Camera::Camera(const Vector& position, const Vector& lookAt, const Limit& xLimit, const Limit& yLimit, const Limit& zLimit) : _xLimit{xLimit}, _yLimit{ yLimit }, _zLimit{ zLimit }, _position{ position }, _lookAt{ lookAt }, _translation{4,4}
{
	update(position, lookAt);
	_translation(3, 3) = 1;
}

Camera::Camera(const Vector& position, const Vector& lookAt, const Limit& limit) : Camera{position, lookAt, limit, limit, limit}
{
}

void Camera::setXlimits(const Limit& limit)
{
	_xLimit = limit;
}

void Camera::setYlimits(const Limit& limit)
{
	_yLimit = limit;
}

void Camera::setZlimits(const Limit& limit)
{
	_zLimit = limit;
}

void Camera::setLimits(const Limit& limit)
{
	setXlimits(limit);
	setYlimits(limit);
	setZlimits(limit);
}

void Camera::update(const Vector& position, const Vector& lookAt)
{
	_position = position;
	_lookAt = lookAt;

	Vector direction = _position - _lookAt;
	Vector up{ {0,1,0,1} };
	Vector right = up.crossProduct(direction);
	up = direction.crossProduct(right);

	right.normalise({ _xLimit, _yLimit, _zLimit, _zLimit });
	up.normalise({ _xLimit, _yLimit, _zLimit, _zLimit });
	direction.normalise({ _xLimit, _yLimit, _zLimit, _zLimit });

	updateTranslation(right, up, direction);
}

std::vector<Vector> Camera::toCameraPerspective(const Vector& vector1, const Vector& vector2) const
{
	std::vector<Vector> results(2);

	Matrix result1{ 1, vector1.getDimension() };
	Matrix result2{ 1, vector2.getDimension() };


	return result;
}

void Camera::updateTranslation(const Vector& right, const Vector& up, const Vector& direction)
{
	_translation(0, 0) = right[0];
	_translation(1, 0) = right[1];
	_translation(2, 0) = right[2];
				 
	_translation(0, 1) = up[0];
	_translation(1, 1) = up[1];
	_translation(2, 1) = up[2];
				 
	_translation(0, 2) = direction[0];
	_translation(1, 2) = direction[1];
	_translation(2, 2) = direction[2];

	_translation(3, 3) = 1;

	Matrix eye{ UnitaryMatrix{ 4 } };
	eye(3, 0) = -_position[0];
	eye(3, 1) = -_position[1];
	eye(3, 2) = -_position[2];

	_translation = _translation * eye;

	_translation.draw();
}











