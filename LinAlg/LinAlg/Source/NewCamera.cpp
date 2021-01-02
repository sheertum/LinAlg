#include "NewCamera.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"

#include <iostream>

Eye::Eye() : Matrix{ 3,3 }, _position { {0, 0, 0} }, _lookat{ _position }
{
	_lookat[2] = -1;
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

Matrix Eye::view(const Vector& inEye, double pitch, double yaw)
{
	Vector eye{ inEye };
	eye.pushBack(0);

	float cosPitch = std::cos(pitch);
	float sinPitch = std::sin(pitch);
	float cosYaw = std::cos(yaw);
	float sinYaw = std::sin(yaw);

	Vector xAxis{ {cosYaw,				0,		 -sinYaw,				0} };
	Vector yAxis{ {sinYaw * sinPitch,	cosPitch, cosYaw * sinPitch,	0 } };
	Vector zAxis{ {sinYaw * cosPitch,  -sinPitch, cosPitch * cosYaw,	0} };
	
	Vector newEye{ {0,0,0,1} };
	newEye[0] = -(xAxis * eye);
	newEye[1] = -(yAxis * eye);
	newEye[2] = -(zAxis * eye);

	Matrix result(4, 4);
	result(0, 0, xAxis, false);
	result(0, 1, yAxis, false);
	result(0, 2, zAxis, false);
	result(0, 3, newEye, false);

	return result;
}

Matrix Eye::lookAt(const Vector& eye, const Vector& target, const Vector& up)
{
	Vector N = target;
	N.normalise();

	Vector U = up.crossProduct(target);
	U.normalise();

	Vector V = N.crossProduct(U);
 
	Matrix result{ 4, 4 };

	result(0, 0, U, false);
	result(0, 1, V, false);
	result(0, 2, N, false);
	result(3, 3) = 1;

	return result;
}

Vector Eye::getPerspective(const Vector& v1, const Vector& offset, const ProjectionMatrix& perspective)
{
	Vector vector{ v1 };
	//Vector position{ _position };

	//vector.pushBack(1);

	//Matrix translation{ TranslateMatrix{_position*-1} };
	//Matrix rotation = view(_position, 0, angle);//lookAt(Vector{ {0,0,0} }, _lookat, Vector{ {0,1,0} });
	//Matrix total = rotation * translation;

	//vector = (total * vector).toVector();

	newRotate(vector,angle);
	return vector;
}

void Eye::newRotate(Vector& vector, double xAngle)
{
	vector.translate(_position * -1);
	Matrix temp = vector.toMatrix();
	temp.xRotate(xAngle);

	vector = temp.toVector();
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
