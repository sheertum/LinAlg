#pragma once

#include "Figure.h"
#include <string>

class FigureLoader
{
public:
	static Figure load(const char*, int maxCoordinate, int minCoordinate = 0, double scale = 1.0);

private:
	static Vector handleVertex(const std::string&);
	static void handleTriangle(const std::string&, const std::vector<Vector>&, const std::vector<Vector>& normals, std::vector<Triangle>&, double min, double max, double scale, double maxCoordinate);
	static size_t findNth(const std::string& line, const std::string& lookFor, size_t nth);
	static size_t fileterIndex(const std::string& line, size_t last, size_t first = 0);
	static Vector scale(const Vector& target, double min, double max, double scale, double maxCoordinate);
};
