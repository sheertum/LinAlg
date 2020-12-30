#include "Camera.h"
#include "UnitaryMatrix.h"

#include <vector>

Camera::Camera(Vector position, Vector lookAt, double angle, double fov, Limit clippingPlane) : _position{position}, _lookAt{lookAt} {
	_axis = UnitaryMatrix{position.getDimension()};
	_axis.translate(position);
}

void Camera::roll(double angle){
	_axis.randomLineRotate(_position, getZAxis(), angle);
	//Bewerrk projectionmatrix
	// loop door hele wereld om die tegenovergesteld te bewerken
}

void Camera::pitch(double angle){
	_axis.randomLineRotate(_position, getYAxis(), angle);
}

void Camera::yaw(double angle){
	_axis.randomLineRotate(_position, getXAxis(), angle);
}

void Camera::moveUp(double distance){
	
}

void Camera::moveRight(double distance){

}

void Camera::moveBack(double distance){

}

Vector Camera::getXAxis(){
	return Vector{{_axis(0,0), _axis(0,1), _axis(0,2)}};
}

Vector Camera::getYAxis(){
	return Vector{{_axis(1,0), _axis(1,1), _axis(1,2)}};
}

Vector Camera::getZAxis(){
	return Vector{{_axis(2,0), _axis(2,1), _axis(2,2)}};
}
