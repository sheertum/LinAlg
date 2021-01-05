#include "Figure.h"
#include <iostream>
#include "UnitaryMatrix.h"
Figure::Figure(std::vector<Triangle>& triangles, double velocity) : _velocityFactor{ velocity }, _axis{ 3,3 }, _center{ Vector{{0,0,0}} }, _boundingSphere{ _center }
{
	std::vector<double> dataPoints{};
	int columnIndex = 0;

	for(auto triangle : triangles){
		auto vectors = triangle.getVectors();
		for(auto vector:vectors){
			if(!containtsVector(vector, dataPoints)){
				for (int i = 0; i < 3; i++) {
					dataPoints.push_back(vector[i]);
				}
				columnIndex++;
			}
		}
		_triangles.push_back(triangle);
	}

	calculateCenter(dataPoints, columnIndex);
	calulateAxis();
	_boundingSphere.calculateRadius(dataPoints);
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

std::vector<Triangle>& Figure::getTriangles()
{
	return _triangles;
}

void Figure::roll(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), getZAxis(), angle);
	}
	_axis.randomLineRotate(getCenter(), getZAxis(), angle);
}

void Figure::pitch(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), getXAxis(), angle);
	}
	_axis.randomLineRotate(getCenter(), getXAxis(), angle);
}

void Figure::yaw(double angle){
	for(auto& triangle : _triangles){
		triangle.randomLineRotate(getCenter(), getYAxis(), angle);
	}
	_axis.randomLineRotate(getCenter(), getYAxis(), angle);
}

void Figure::move(){
	Vector velocity = calculateSpeed();
	for(auto& triangle : _triangles){
		triangle.translate(velocity);
	}
	auto newCenterMatrix = _center.toMatrix();
	newCenterMatrix.translate(velocity);
	for (size_t i = 0; i < _center.getDimension(); i++)
	{
		_center[i] = newCenterMatrix(0,i);
	}
	_boundingSphere.setCenter(_center);
	_axis.translate(velocity);
}

void Figure::accelerate(double acceleration){
	if(_velocityFactor == 0){
		_velocityFactor += 0.01;
	}
	
	_velocityFactor = _velocityFactor *acceleration;
	
	if (_velocityFactor < 0.01) {
		_velocityFactor = 0;
	}
	std::cout << _velocityFactor << std::endl;
}

Vector Figure::calculateSpeed(){
	return (getZAxis()-_center)*_velocityFactor;
}

void Figure::grow(double factor){
	for(auto& triangle : _triangles){
		triangle.translate(_center * -1);
		triangle.scale(factor);
		_boundingSphere.scaleRadius(factor);
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

void Figure::calulateAxis(){
	_axis = UnitaryMatrix{ 3 };
	_axis.translate(_center);
}

Vector Figure::getXAxis(){
	return Vector{{_axis(0,0), _axis(0,1), _axis(0,2)}};
}

Vector Figure::getYAxis(){
	return Vector{{_axis(1,0), _axis(1,1), _axis(1,2)}};
}

Vector Figure::getZAxis(){
	return Vector{{_axis(2,0), _axis(2,1), _axis(2,2)}};
}

Vector Figure::getBigXAxis()
{
	Vector bigX = getXAxis()- getCenter();
	bigX = bigX * 100;
	bigX = bigX  + getCenter();
	return bigX;
}

Vector Figure::getBigYAxis()
{
	Vector bigY = getYAxis() - getCenter();
	bigY = bigY * 100;
	bigY = bigY + getCenter();
	return bigY;
}

Vector Figure::getBigZAxis()
{
	Vector bigZ = getZAxis() - getCenter();
	bigZ = bigZ * 100;
	bigZ = bigZ + getCenter();
	return bigZ;
}

Vector Figure::getSphereRadius() {
	return _center + Vector{ {_boundingSphere.getRadius(),0,0} };
}

BoundingSphere& Figure::getBoundingSphere(){
	return _boundingSphere;
}

void Figure::collide()
{
}
