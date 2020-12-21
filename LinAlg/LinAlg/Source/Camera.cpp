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
	update();
}

void Camera::update()
{
	Vector direction = _position - _lookAt;
	Vector up{ {0,1,0,1} };
	Vector right = up.crossProduct(direction);
	up = direction.crossProduct(right);

	right.normalise();
	up.normalise();
	direction.normalise();

	updateTranslation(right, up, direction);
}

void Camera::rotate(double x, double y, double z)
{
	Matrix temp = _lookAt.toMatrix();

	temp.translate(-_position[0], -_position[1], -_position[2]);
	
	temp.xRotate(x);
	temp.yRotate(y);
	temp.zRotate(z);

	temp.translate(_position[0], _position[1], _position[2]);

	_lookAt = temp.toVector();
}

std::vector<Vector> Camera::toCameraPerspective(const Vector& vector1, const Vector& vector2) const
{
	Vector result1{ vector1 };
	result1.pushBack(1.0);

	Vector result2{ vector2 };
	result2.pushBack(1.0);

	result1 = (_translation * result1).toVector();
	result2 = (_translation * result2).toVector();

	return std::vector<Vector>{result1, result2};
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











