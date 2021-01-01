#include "NewCamera.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"

#include <iostream>

Eye::Eye() : Matrix{ 3,3 }, _position { {0, 0, 0} }, _lookat{ {0.1,0.1,-10.1} }
{
	_data = UnitaryMatrix{ 3,3 }.getData();
}

Matrix Eye::pointAt(const Vector& position, const Vector& direction, const Vector& up)
{
	return Matrix(1,1);
}

//std::array<Vector, 2> Eye::getPerspective(const Vector& v1, const Vector& v2)
//{
//	std::array<Vector, 2> result = { v1, v2 };
//	result[0].pushBack(1);
//	result[1].pushBack(1);
//
//	result[0] = (_view * result[0]).toVector();
//	result[1] = (_view * result[1]).toVector();
//
//	return result;
//}

void Eye::update() {
	//_view = TranslateMatrix{ _position * -1 };

	//Vector xAxis{ _axis.getVector(0) };

	//_view.randomLineRotate(_position, xAxis, xAxis.getAngle(Vector{ {1,0,0} }));
}

Vector Eye::getPerspective(const Vector& v1, const Vector& offset)
{

	Vector vector{ v1 };
	vector.pushBack(1);

	Vector position{ _position };
	position.pushBack(1);

	Vector lookat{ _lookat };
	Matrix temp{ lookat.toMatrix() };
	temp.xRotate(angle);
	lookat = temp.toVector();
	lookat.pushBack(1);

	Vector direction = position - lookat;
	direction.normalise();

	Vector up{ {0,1,0,1} };

	Vector right = up.crossProduct(direction);
	right.normalise();

	up = direction.crossProduct(right);
	up.normalise();

	Matrix m{ UnitaryMatrix{4} };
	m(0, 0, right, false);
	m(0, 1, up, false);
	m(0, 2, direction, false);

	Matrix toOrigin{ UnitaryMatrix{4} };
	toOrigin(3, 0, (position * -1), true);
	m = m * toOrigin;

	vector = (m * vector).toVector();
	//vector.translate(_position);

	//Vector direction = _position - _lookat;
	//direction.normalise();
	////direction.pushBack(1);

	//Vector up{ {0,1,0} };

	//Vector right = up.crossProduct(direction);
	//right.normalise();

	//direction.translate(_position);
	//up.translate(_position);
	//right.translate(_position);

	////Matrix temp{ vector.toMatrix() };
	//Matrix rotate{ getRandomLineRotateMatrix(right, angle) };
	//vector.pushBack(1);
	//vector = (rotate * vector).toVector();
	////temp.randomLineRotate(_position, right, angle);

	return vector;
}

void Eye::rotate(Vector& toRotate, const Vector& axes, double angle)
{
	if (angle != 0 && angle != 360)
	{
		Matrix temp = toRotate.toMatrix();
		temp.originLineRotate(axes, angle);
		toRotate = temp.toVector();
	}
}
