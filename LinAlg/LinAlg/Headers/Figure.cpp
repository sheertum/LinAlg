#include "Figure.h"

Figure::Figure(const std::vector<Vector>& vectors) : Matrix(vectors.size(), vectors[0].getDimension())
{
	int columnIndex = 0;
	for (const auto& vector : vectors)
	{
		int rowIndex = 0;
		for (int i : vector.coordinates) {
			this->operator()(columnIndex, rowIndex++) = i;
		}

		columnIndex++;
	}
}

Vector Figure::getVector(int index) const
{
	std::vector<int> v;
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
