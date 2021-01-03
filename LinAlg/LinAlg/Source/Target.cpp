#include "Target.h"

Target::Target(std::vector<Triangle>& triangles, World* world, Vector position, double velocity, int growthLimit, bool isGrowing) : Figure{ triangles, velocity }, _growLimit { growthLimit }, _isGrowing{ isGrowing }, _grow{ 0 }, _world{world}{
	for(auto& triangle : _triangles){
		triangle.translate(position);
	}
}

void Target::tick()
{
	if (_grow > _growLimit) {
		_isGrowing = false;
	}
	else if (_grow < 0){
		_isGrowing = true;
	}

	if (_isGrowing) {
		grow(1.1);
		_grow++;
	}
	else {
		shrink(1.1);
		_grow--;
	}
}
