#include "Bullet.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"
#include "World.h"

#include <iostream>
#include <cmath>

Bullet::Bullet(std::vector<Triangle>& triangles, World* world, Vector startPosition, Matrix axis, double velocityFactor) : Figure{ triangles, velocityFactor/3 }, _world{world}
{
	Vector zAxis{{axis(2,0),axis(2,1),axis(2,2)}};
	Vector xAxis{{axis(0,0),axis(0,1),axis(0,2)}};
	allignWithOriginator(zAxis, xAxis);
	setAtOriginatorPosition(startPosition);
}

void Bullet::allignWithOriginator(const Vector& zAxis, const Vector& xAxis){
	double pi = 3.14159265359;
	Vector originalDirection{ {0,0,-1} };
	Vector rotationAxis{ {0,0,0} };
	
	Vector angleCopy = zAxis;
	Vector angleZcopy = originalDirection;

	angleCopy.normalise();
	angleZcopy.normalise();
	double angle = acos(angleCopy * angleZcopy);

	rotationAxis = originalDirection.crossProduct(zAxis);
	
	if (rotationAxis[0] == 0 && rotationAxis[1] == 0 && rotationAxis[2] == 0 || angle == 0) {
		return;
	}
	_axis.randomLineRotate(Vector{ { 0,0,0 } }, rotationAxis, angle);
	_axis.randomLineRotate(Vector{ { 0,0,0 } }, rotationAxis, pi);
	
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

void Bullet::tick()
{
	if ((float(clock() - beginTime) / CLOCKS_PER_SEC) > lifeTime)
	{
		remove();
	}
}

void Bullet::remove()
{
	auto& figures = _world->getFigures();
	auto& bullets = _world->getBullets();

	int i = 0;
	for (const auto& bullet : bullets) {
		if (bullet.get() == this)
		{
			_world->removeBullet(i);
			break;
		}
		i++;
	}

	i = 0;
	for (const auto& figure : figures) {
		if (figure.get() == this)
		{
			_world->removeFigure(i);
			break;
		}
		i++;
	}
}

void Bullet::collide()
{
	remove();
}
