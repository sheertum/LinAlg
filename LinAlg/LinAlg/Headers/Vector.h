#pragma once

#include <vector>

class Vector
{
public:
    // Vector(float coordinate, ...);
    Vector(std::vector<float>);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    int dimensions;
    std::vector<float> coordinates;
private:
    bool hasCorrectDimension(const Vector&);
};