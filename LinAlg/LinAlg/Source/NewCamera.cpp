#include "NewCamera.h"
#include "UnitaryMatrix.h"

#include <iostream>

Eye::Eye() : _eye{{0,0,0,1}}, _lookAt{{0,0,0,1}}, _view{4,4}, _yaw{0}
{
	update();
}

Matrix Eye::pointAt(const Vector& position, const Vector& direction, const Vector& up)
{


	//return result;
	return Matrix{3,3};
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
	Vector direction{ _eye - _lookAt };
	direction.normalise();

	Vector up{ {0,1,0,1} };

	Vector right{ up.crossProduct(direction) };
	right.normalise();

	up = direction.crossProduct(right);
	up.normalise();

	UnitaryMatrix toOrigin{4};
	toOrigin(3, 0, _eye * -1);
}