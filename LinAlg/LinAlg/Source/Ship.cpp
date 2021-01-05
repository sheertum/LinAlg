#include "Ship.h"
#include "World.h"
#include "UnitaryMatrix.h"

Ship::Ship(std::vector<Triangle>& triangles, World* world) : 
	Figure( triangles, 0.0 ),
_gunMuzzle{ {0,0,0} }, 
_aim{ {{0,0,0}} }, 
_world{ world },
_bulletTriangles{}
{
	Vector vA{ {-100,-100,-100} };
    Vector vB{ {100,100,0} };
    Vector vC{ {100,0,100} };
    Triangle triangle1{ vA, vB, vC };

	_bulletTriangles.push_back(triangle1);
}

void Ship::shoot(){
	Matrix originAxis = _axis;
	originAxis.translate(_center*-1);
	
	_world->addBullet(_bulletTriangles, getCenter(), originAxis, 0.1);
}

Vector Ship::getAim(){
	return getZAxis()*1000;
}