#pragma once

#include <vector>

class Shape {
public:
	Shape(const std::vector<int>&);
	std::vector<int> _indices;
};