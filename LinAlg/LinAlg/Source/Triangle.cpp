#include "Triangle.h"
Triangle::Triangle(Vector a, Vector b, Vector c, const Vector& normal) : Matrix{ 3,3 }, _normal{ normal } {
	std::vector<Vector> points{ a,b,c };
	_normal = Vector{ {normal[0], normal[1], normal[2]} };

	int i = 0;
	for (auto point : points) {
		for (int j = 0; j < _rowCount; j++) {
			this->operator()(i, j) = point[j];
		}
		i++;
	}
}

Triangle::Triangle(std::vector<double> data, const Vector& normal) : Matrix{ 3, 3 }, _normal{normal} {
	if (data.size() != 9) {
		throw "OutOfBounds";
	}

	_normal = Vector{ {normal[0], normal[1], normal[2]} };

	Matrix matrix{3,3,data};
	std::vector<Vector> points = convertToVectors(matrix);
	Vector A = points[0];
	Vector B = points[1];
	Vector C = points[2];

	Vector center = (A+B+C)*(1.0/3.0);
	Vector AB = B - A;
	Vector AC = C - A;
	Vector normABC = AB.crossProduct(AC);

	if(normABC * center < 0){
		Vector temp = B;
		B = A;
		A = temp;
	}
}

std::vector<Vector> Triangle::getVectors() const{
	std::vector<Vector> result{};
	for (int i = 0; i < _columnCount; i++) {
		std::vector<double> newCoordinates{};
		for (int j = 0; j < _rowCount; j++) {
			newCoordinates.push_back(this->operator()(i, j));
		}
		result.push_back(Vector{ newCoordinates });
	}
	return result;
}

Vector Triangle::getNormal() const
{
	return _normal;
}

std::vector<Vector> Triangle::convertToVectors(Matrix input)
{
	std::vector<Vector> result{};
	for (int i = 0; i < 3; i++) {
		std::vector<double> newCoordinates{};
		for (int j = 0; j < 3; j++) {
			newCoordinates.push_back(input(j, i));
		}
		result.push_back(Vector{ newCoordinates });
	}
	return result;
}
