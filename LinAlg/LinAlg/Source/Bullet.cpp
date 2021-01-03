#include "Bullet.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"

#include <cmath>

Bullet::Bullet(std::vector<Triangle>& triangles, World* world, Vector startPosition, Matrix axis, double velocityFactor) : Figure{ triangles, velocityFactor }, _world{world}
{
	//TODO: figue loader gebruiken om de triangles in te laden die bij het juiste figuur horen
	Vector direction{{axis(2,0),axis(2,1),axis(2,2)}};
	allignWithOriginator(direction);
	setAtOriginatorPosition(startPosition);
	
}

void Bullet::allignWithOriginator(Vector direction){

	double pi = 3.14159265359;
	Vector originalDirection{ {0,0,-1} };
	Vector rotationAxis{ {0,0,0} };


	double angle = std::fmod(direction * originalDirection, 2 * pi);
	if (abs(angle) > pi) {
		rotationAxis = originalDirection.crossProduct(direction);
	}
	else {
		rotationAxis = direction.crossProduct(originalDirection);
	}
	
	if (rotationAxis[0] == 0 && rotationAxis[1] == 0 && rotationAxis[2] == 0) {
		return;
	}
	_axis.randomLineRotate(Vector{ { 0,0,0 } }, rotationAxis, angle);


	for(auto& triangle : _triangles){
		triangle.randomLineRotate(Vector{{ 0,0,0 }}, rotationAxis, angle);
	}
}

void Bullet::setAtOriginatorPosition(Vector position){
	_axis.translate(position);
	_center = _center + position;
	for(auto& triangle : _triangles){
		triangle.translate(position);
	}
}
