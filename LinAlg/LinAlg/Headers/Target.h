#pragma once

#include "Figure.h"

class Target : public Figure{
public:
	Target(const std::vector<Triangle>& triangles, double velocity, int growthLimit, bool isGrowing);
	void tick();
private:
	int _grow;
	int _growLimit;
	bool _isGrowing;
};