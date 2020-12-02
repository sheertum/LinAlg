#include "ProjectionMatrix.h"
#include <math.h>

ProjectionMatrix::ProjectionMatrix(double width, double height, double fieldOfView, double zNear, double zFar) : _data{4,4}
{
	double tanCalculation = (1 / tan(fieldOfView * 0.5 / 180 * 3.14159));
	_data(0, 0) = (height / width) * tanCalculation;
	_data(1, 1) = tanCalculation;
	_data(2, 2) = zFar / (zFar - zNear);
	_data(3, 2) = 1;
	_data(2, 3) = (-zFar*zNear)/(zFar-zNear);
	
}

Vector ProjectionMatrix::operator*(const Vector& vector) 
{
	Matrix temp{ 1,4 };
	temp(0, 0) = vector[0];
	temp(0, 1) = vector[1];
	temp(0, 2) = vector[2];
	temp(0, 3) = 1;

	Matrix tempResult = _data * temp;
	double w = tempResult(0, 3);

	if (w != 0.0)
	{
		Vector result{ {tempResult(0,0), tempResult(0,1), tempResult(0,2)} };
		result[0] /= w;
		result[1] /= w;
		result[2] /= w;
		return result;
	}

	return Vector{ {-DBL_MAX,-DBL_MAX,-DBL_MAX} };
}

