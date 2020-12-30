#include "NewCamera.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"

#include <iostream>

Eye::Eye() : _position{ {-500,0,0} }, _pitch{ 0 }, _yaw{ 0 }, _roll{ 0 }, _view{ 4,4 }, 
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
	_view = TranslateMatrix{ _position * -1 };
	_view.randomLineRotate(_position, )
}