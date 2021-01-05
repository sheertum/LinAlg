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

}

void Ship::shoot(){
	Matrix originAxis = _axis;
	originAxis.translate(_center*-1);
	
	_world->addBullet(_bulletTriangles, getCenter(), originAxis, 100);
}

Vector Ship::getAim(){
	return getZAxis()*1000;
}