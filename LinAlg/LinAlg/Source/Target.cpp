#include "Target.h"
#include "World.h"

Target::Target(std::vector<Triangle>& triangles, World* world, Vector position, double velocity, int growthLimit, bool isGrowing) : Figure{ triangles, velocity }, _growLimit { growthLimit }, _isGrowing{ isGrowing }, _grow{ 0 }, _world{world}{
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

void Target::collide()
{
	remove();
}

void Target::remove()
{
	auto& figures = _world->getFigures();
	auto& targets = _world->getTargets();

	int i = 0;
	for (const auto& target : targets) {
		if (target.get() == this)
		{
			_world->removeTarget(i);
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
