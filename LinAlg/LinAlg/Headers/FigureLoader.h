#pragma once

#include "Figure.h"
#include <string>

class FigureLoader
{
public:
	static Figure load(const char*, int maxCoordinate, int minCoordinate = 0, double scale = 1.0);

private:
	static Vector handleVertex(const std::string&);
	static void handleTriangle(const std::string&, const std::vector<Vector>&, std::vector<Triangle>&);
};
