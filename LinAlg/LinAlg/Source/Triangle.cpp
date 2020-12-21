#include "Triangle.h"
Triangle::Triangle(Vector a, Vector b, Vector c) : Matrix{ 3,3 }, _boundingBox{}{
	std::vector<Vector> points{ a,b,c };
	int i = 0;
	for (auto point : points) {
		for (int j = 0; j < 3; j++) {
			_data[(i + j)] = point[j];
		}
		i = i + 3;
	}
	_boundingBox = BoundingBox{_data};
}

Triangle::Triangle(std::vector<double> data) : Matrix { 3, 3 }, _boundingBox{data} {
	if (data.size() != 9) {
		throw "OutOfBounds";
	}
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

std::vector<Vector> Triangle::convertToVectors(Matrix input)
{
	std::vector<Vector> result{};
	for (int i = 0; i < 3; i++) {
		std::vector<double> newCoordinates{};
		for (int j = 0; j < 3; j++) {
			newCoordinates.push_back(input(i, j));
		}
		result.push_back(Vector{ newCoordinates });
	}
	return result;
}
