#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(Vector center, std::vector<double>& data) : _center{center} {
    _radius = 0;
    for (size_t i = 0; i <= data.size(); i++)
	{
        Vector temp{{}};
		for (size_t j = 0; j < 3; j++) {
			temp[j] = (data[j + (i * 3)]);
		}
        temp = temp-center;

	}
}
