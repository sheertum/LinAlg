#include "Figure.h"

Figure::Figure(const std::vector<Vector>& vectors) : Matrix(vectors.size(), vectors[0].getDimension()), _center{0,0,0}
{
	int columnIndex = 0;
	int coordinateCounter = 1;
	for (const auto& vector : vectors)
	{
		int rowIndex = 0;
		for (int i : vector.coordinates) {
			this->operator()(columnIndex, rowIndex++) = i;
		}

		_center[0] = (vector.coordinates[0] + _center[0]) / coordinateCounter;
		_center[1] = (vector.coordinates[1] + _center[1]) / coordinateCounter;
		_center[2] = 0; //TODO

		coordinateCounter++;

		columnIndex++;
	}
}

void Figure::scaleFromOrigin(double x, double y, double z)
{
	Matrix::translate(_center[0] * -1, _center[1] * -1, _center[2] * -1);
	Matrix::scale(x, y, z);
	Matrix::translate(_center[0], _center[1], _center[2]);
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
