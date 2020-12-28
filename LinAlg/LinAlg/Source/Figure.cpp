#include "Figure.h"
Figure::Figure(const std::vector<Triangle>& triangles) : _center{}, _velocity{{0,0,0}}
{
	std::vector<double> dataPoints{};
	_center.resize(3);
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

Figure::Figure(const std::vector<Triangle>& triangles, Vector velocity) : _center{}, _velocity{velocity}
{
	std::vector<double> dataPoints{};
	_center.resize(3);
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

}

void Figure::pitch(double angle){

}

void Figure::yaw(double angle){

}

void Figure::move(){
	for(auto& triangle : _triangles){
		triangle.translate(_velocity[0], _velocity[1], _velocity[2]);
	}
}

void Figure::accelerate(double acceleration){
	_velocity = _velocity*acceleration;
}

void Figure::grow(double factor){

}

void Figure::shrink(double factor){

}

Vector Figure::getCenter(){
	return Vector{{_center[0], _center[1], _center[2]}};
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

	for (auto& it : _center)
	{
		it = it / coordinateCounter;
	}
}

void Figure::moveToOrigin()
{
	for(auto& triangle : _triangles){
		triangle.translate(_center[0] * -1, _center[1] * -1, _center[2] * -1);
	}
}

void Figure::moveBack()
{
	for(auto& triangle : _triangles){
		triangle.translate(_center[0], _center[1], _center[2]);
	}
}
