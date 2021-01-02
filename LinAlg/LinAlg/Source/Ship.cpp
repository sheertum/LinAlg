#include "Ship.h"

Ship::Ship(const std::vector<Triangle>& triangles, World* world) : Figure(triangles, 0), _gunMuzzle{ {0,0,0} }, _aim{ {{0,0,0}} }, _world{ world } {
	_gunMuzzle = getZAxis();
    _aim = getZAxis()*1000;
}

void Ship::shoot(){

}

Vector Ship::getAim(){
	return _aim;
}
