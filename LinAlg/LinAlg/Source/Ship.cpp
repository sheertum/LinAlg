#include "Ship.h"
#include "World.h"
#include "UnitaryMatrix.h"

Ship::Ship(std::vector<Triangle>& triangles, World* world, std::vector<Triangle>& bullettriangles) :
	Figure( triangles, 0.0 ),
_gunMuzzle{ {0,0,0} }, 
_aim{ {{0,0,0}} }, 
_world{ world },
_bulletTriangles{ bullettriangles }
{
	Figure temp{ _bulletTriangles, 0 };
	_bulletRadius = temp.getBoundingSphere().getRadius();
}

void Ship::shoot(){
	Matrix originAxis = _axis;
	originAxis.translate(_center*-1);

	double total = getBoundingSphere().getRadius() + _bulletRadius;
	Vector direction = getZAxis();
	direction.translate(getCenter() * -1);
	direction.normalise();
	direction = direction * total;
	direction.translate(getCenter());

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(_bulletTriangles, _world, direction, originAxis, 100 + _velocityFactor);

	_world->addBullet(bullet);
}

Vector Ship::getAim(){
	return getZAxis()*1000;
}

void Ship::collide()
{
	remove();
}

void Ship::remove()
{
	auto& figures = _world->getFigures();

	int i = 0;
	for (const auto& figure : figures) {
		if (figure.get() == this)
		{
			_world->removeFigure(i);
			break;
		}
		i++;
	}
	_world->removeShip();
}
