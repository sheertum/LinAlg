#include "Figure.h"

Figure::Figure(const std::vector<Vector>& vectors) : Matrix(vectors.size(), vectors[0].getDimension()), _center{}
{
	_center.resize(vectors[0].getDimension());
	int columnIndex = 0;
	for (const auto& vector : vectors)
	{
		int rowIndex = 0;
		for (int i : vector.coordinates) {
			this->operator()(columnIndex, rowIndex++) = i;
		}

		columnIndex++;
	}

	calculateCenter();
}

void Figure::scaleFromOrigin(double x, double y, double z)
{
	Matrix::scale(x, y, z);
}

Vector Figure::getVector(int index) const
{
	std::vector<double> v;
	v.resize(_rowCount);
	Vector vector{ v };

	for (size_t i = 0; i < _rowCount; i++)
	{
		vector[i] = this->operator()(index, i);
	}

	return vector;
}

int Figure::size() const
{
	return _columnCount;
}

void Figure::calculateCenter()
{
	int coordinateCounter = 0;
	for (size_t i = 0; i < _columnCount; i++, coordinateCounter++)
	{
		for (size_t j = 0; j < _rowCount; j++) {
			_center[j] += (this->operator()(i,j));
		}
	}

	for (auto& it : _center)
	{
		it = it / coordinateCounter;
	}
}

void Figure::moveToOrigin()
{
	Matrix::translate(_center[0] * -1, _center[1] * -1, _center[2] * -1);
}

void Figure::moveBack()
{
	Matrix::translate(_center[0], _center[1], _center[2]);
}

void Figure::createShape(std::vector<int> indices)
{
	_shapes.push_back({indices});
}

const std::vector<Shape>& Figure::getShapes() const
{
	return _shapes;
}
