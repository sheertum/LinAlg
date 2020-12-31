#include "BoundingSphere.h"

BoundingSphere::BoundingSphere() : _radius{ 0 }, _center{ Vector{ {0,0,0} } } {}

BoundingSphere::BoundingSphere(Vector& center, std::vector<double>& data) : _center{center} {
    _radius = 0;
    for (size_t i = 0; i <= data.size(); i+=3)
	{
        Vector temp{{}};
		for (size_t j = 0; j < 3; j++) {
			temp[j] = (data[j + (i * 3)]);
		}
        temp = temp-center;

		if(temp.length() > _radius){
			_radius = temp.length();
		}
	}
}

Vector BoundingSphere::getCenter() const
{
	return _center;
}

double BoundingSphere::getRadius() const
{
	return _radius;
}
