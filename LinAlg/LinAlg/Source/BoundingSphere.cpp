#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector& center) : _center{ center } {
	_radius = 0;
}

void BoundingSphere::calculateRadius(const std::vector<double>& data){
    Vector temp{_center};

    for (size_t i = 0; i < data.size()/3; i++)
	{
		for (size_t j = 0; j < 3; j++) {
			temp[j] = (data[j + (i * 3)]);
		}
        temp = temp-_center;

		if(temp.length() > _radius){
			_radius = temp.length();
		}
	}
}

Vector& BoundingSphere::getCenter() const
{
	return _center;
}

double BoundingSphere::getRadius() const
{
	return _radius;
}

void BoundingSphere::scaleRadius(double factor){
	_radius*= factor;
}

void BoundingSphere::setCenter(Vector& center){
	_center = center;
}