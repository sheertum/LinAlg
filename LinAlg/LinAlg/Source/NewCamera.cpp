#include "NewCamera.h"
#include "UnitaryMatrix.h"

#include <iostream>

Eye::Eye() : _position{{0,0,0}}, _direction{{0,0,1}}, _view{4,4}, _yaw{0}
{
	update();
}

Matrix Eye::pointAt(const Vector& position, const Vector& target, const Vector& up)
{
	Vector newForward = target - position;
	newForward.normalise();
	//newForward.pushBack(1);

	double i = (up * newForward);
	Vector a = newForward * (up*newForward);
	Vector newUp = up - a;
	newUp.normalise();

	Vector newRight = newUp.crossProduct(newForward);

	Matrix pointAt(4, 4);

	pointAt(0, 0) = newRight[0];
	pointAt(1, 0) = newRight[1];
	pointAt(2, 0) = newRight[2];

	pointAt(0, 1) = newUp[0];
	pointAt(1, 1) = newUp[1];
	pointAt(2, 1) = newUp[2];

	pointAt(0, 2) = target[0];
	pointAt(1, 2) = target[1];
	pointAt(2, 2) = target[2];

	UnitaryMatrix eye(4);
	eye(0, 2) = -target[0];
	eye(1, 2) = -target[1];
	eye(2, 2) = -target[2];

	pointAt = pointAt * eye;

	return pointAt;
}

std::array<Vector, 2> Eye::getPerspective(const Vector& v1, const Vector& v2)
{
	std::array<Vector, 2> result = { v1, v2 };
	result[0].pushBack(1);
	result[1].pushBack(1);

	result[0] = (_view * result[0]).toVector();
	result[1] = (_view * result[1]).toVector();

	return result;
}

void Eye::update() {
	//_direction = Vector{ {0,0,-1} };
	_direction.normalise();
	_direction.print();
	std::cout << "\n";
	Vector up{ {0,1,0} };
	Vector target{ {0,0,1} };//_position + _direction;
	
	Matrix temp = target.toMatrix();
	temp.yRotate(_yaw);
	_direction = temp.toVector();

	target = _position + _direction;

	_view = pointAt(_position, target, up);
	_view.simpleInverse();
}