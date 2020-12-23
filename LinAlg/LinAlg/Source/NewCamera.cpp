#include "NewCamera.h"
#include "UnitaryMatrix.h"

#include <iostream>

Eye::Eye() : _position{{0,0,0}}, _direction{{0,0,1}}, _view{4,4}, _yaw{0}
{
	update();
}

Matrix Eye::pointAt(const Vector& position, const Vector& direction, const Vector& up)
{
	Vector camRight = direction.crossProduct(up);
	camRight.normalise();

	Vector camUp = camRight.crossProduct(direction);

	Matrix R(4, 4);
	Matrix translation(4, 4);

	for (size_t i = 0; i < 3; i++)
	{
		R(0, i) = camRight[i];
		R(1, i) = camUp[i];
		R(2, i) = -direction[i];
	}

	Matrix result(4, 4);
	result(0, 0, camRight);
	result(1, 0, camUp);
	result(2, 0, direction * -1);
	result(3, 0, position);
	result.simpleInverse();

	return result;
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
	Vector usedDirection = _direction % 3.14159265;
	usedDirection.normalise();
	usedDirection.print();

	std::cout << "\n";
	Vector up{ {0,1,0} };
	Vector target{ {0,0,1} };//_position + _direction;
	
	Matrix temp = target.toMatrix();
	//temp.yRotate(_yaw);
	//_direction = temp.toVector();

	target = _position + _direction;

	_view = pointAt(_position, usedDirection, up);
	_view.simpleInverse();
}