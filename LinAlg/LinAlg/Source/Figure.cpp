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

Figure::Figure(const std::vector<Triangle>& triangles) : Matrix(triangles.size()*3, 3), _center{}
{
	_center.resize(3);
	int columnIndex = 0;
	for(auto triangle : triangles){
		auto vectors = triangle.getVectors();
		for(auto vector:vectors){
			addUniqueCoordinates(vector, columnIndex);
		}
		_triangles.push_back(triangle);
	}

	calculateCenter();
}

void Figure::addUniqueCoordinates(Vector vector, int& vectorCounter){
	bool exists = false;

	int location = vectorCounter*3;
	auto vecCoordinates = vector.coordinates;

	if(!containtsVector(vector)){
		_data[location] = vecCoordinates[0];
		_data[location+1] = vecCoordinates[1];
		_data[location+2] = vecCoordinates[2];
		vectorCounter++;
	}
}

bool Figure::containtsVector(Vector vector){
	auto vecCoordinates = vector.coordinates;

	for(auto i = 0; i < _columnCount; i=i+3 ){
		if(vecCoordinates[0] == _data[i] && vecCoordinates[1] == _data[i+1] && vecCoordinates[2] == _data[i+2]){
			return true;
		}
	}
	return false;
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

const std::vector<Triangle>& Figure::getTriangles() const
{
	return _triangles;
}
