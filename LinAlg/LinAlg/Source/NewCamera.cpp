#include "NewCamera.h"
#include "UnitaryMatrix.h"

#include <iostream>

Eye::Eye() : _position{{0,0,0,1}}, _lookAt{{0,0,0,-1}}, _view{4,4}, _yaw{0}
{
	_view(3, 3) = 1;
	update();
}

Matrix Eye::pointAt(const Vector& position, const Vector& direction, const Vector& up)
{
	return Matrix(1,1);
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
	Vector direction{ _position - _lookAt };
	direction.normalise();

	Vector up{ {0,1,0,1} };

	Vector right{ up.crossProduct(direction) };
	right.normalise();

	up = direction.crossProduct(right);
	up.normalise();

	UnitaryMatrix toOrigin{4};
	toOrigin(3, 0, _position * -1);
	toOrigin(3, 3) = 1;

	std::cout << "\n";
	toOrigin.draw();
	std::cout << "\n";
	std::cout << "\n";

	_view(0, 0, right, false);
	_view(0, 1, up, false);
	_view(0, 2, direction, false);
	_view.draw();

	_view = _view * toOrigin;
	std::cout << "\n";
	std::cout << "\n";
	_view.draw();
}