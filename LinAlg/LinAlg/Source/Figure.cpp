#include "Figure.h"
Figure::Figure(const std::vector<Triangle>& triangles) : _velocity{{0,0,0}}
{
	std::vector<double> dataPoints{};
	int columnIndex = 0;

	for(auto triangle : triangles){
		auto vectors = triangle.getVectors();
		for(auto vector:vectors){
			if(!containtsVector(vector, dataPoints)){
				for (int i = 0; i < vector.coordinates.size(); i++) {
					dataPoints.push_back(vector[i]);
				}
				columnIndex++;
			}
		}
		_triangles.push_back(triangle);
	}

	calculateCenter(dataPoints, columnIndex);
}

Figure::Figure(const std::vector<Triangle>& triangles, Vector velocity) : _velocity{velocity}
{
	std::vector<double> dataPoints{};
	int columnIndex = 0;

	for(auto triangle : triangles){
		auto vectors = triangle.getVectors();
		for(auto vector:vectors){
			if(!containtsVector(vector, dataPoints)){
				for (int i = 0; i < vector.coordinates.size(); i++) {
					dataPoints.push_back(vector[i]);
				}
				columnIndex++;
			}
		}
		_triangles.push_back(triangle);
	}

	calculateCenter(dataPoints, columnIndex);
}

bool Figure::containtsVector(Vector vector, std::vector<double> collection){
	auto vecCoordinates = vector.coordinates;

	for(auto i = 0; i < collection.size(); i=i+3 ){
		if(vecCoordinates[0] == collection[i] && vecCoordinates[1] == collection[i+1] && vecCoordinates[2] == collection[i+2]){
			return true;
		}
	}
	return false;
}

const std::vector<Triangle>& Figure::getTriangles() const
{
	return _triangles;
}

void Figure::roll(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), _zAxis, angle);
	}
	_xAxis.toMatrix().randomLineRotate(getCenter(), _zAxis, angle);
	_yAxis.toMatrix().randomLineRotate(getCenter(), _zAxis, angle);
}

void Figure::pitch(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), _xAxis, angle);
	}
	_zAxis.toMatrix().randomLineRotate(getCenter(), _xAxis, angle);
	_yAxis.toMatrix().randomLineRotate(getCenter(), _xAxis, angle);
}

void Figure::yaw(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), _yAxis, angle);
	}
	_xAxis.toMatrix().randomLineRotate(getCenter(), _yAxis, angle);
	_zAxis.toMatrix().randomLineRotate(getCenter(), _yAxis, angle);
}

void Figure::move(){
	for(auto& triangle : _triangles){
		triangle.translate(_velocity);
	}
	auto newVectorMatrix = _center.toMatrix();
	newVectorMatrix.translate(_velocity);
	_center.coordinates = newVectorMatrix.getData();
}

void Figure::accelerate(double acceleration){
	_velocity = _velocity*acceleration;
}

void Figure::deccelerate(double acceleration){
	accelerate(1/acceleration);
}

void Figure::grow(double factor){
	for(auto& triangle : _triangles){
		triangle.translate(_center * -1);
		triangle.scale(factor);
		triangle.translate(_center);
	}
}

void Figure::shrink(double factor){
	grow(1/factor);
}

Vector Figure::getCenter(){
	return _center;
}

void Figure::calculateCenter(std::vector<double> collection, int columnCount)
{
	int coordinateCounter = 0;
	for (size_t i = 0; i < columnCount; i++, coordinateCounter++)
	{
		for (size_t j = 0; j < 3; j++) {
			_center[j] += (collection[j + (i * 3)]);
		}
	}

	for (size_t i = 0; i < _center.getDimension(); i++)
	{
		_center[i] = _center[i] / coordinateCounter;
	}
}