#include "Target.h"

Target::Target(const std::vector<Triangle>& triangles, double velocity, int growthLimit, bool isGrowing) : Figure{ triangles, velocity }, _growLimit { growthLimit }, _isGrowing{ isGrowing }, _grow{ 0 }{}

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
