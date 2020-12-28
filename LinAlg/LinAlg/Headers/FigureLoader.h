#pragma once

#include "Figure.h"
#include <string>

class FigureLoader
{
public:
	static Figure load(const char*);

private:
	static void handleVertex(const std::string&, std::vector<Vector>&);
	static void handleTriangle(const std::string&, const std::vector<Vector>&, std::vector<Triangle>&);
};
