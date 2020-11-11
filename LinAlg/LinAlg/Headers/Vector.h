#pragma once

class Vector
{
public:
    Vector(float coordinate, ...);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
private:
    int _dimensions;
    float _coordinate[];
};