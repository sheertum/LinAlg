#pragma once

#include <vector>

#include "Matrix.h"

class Vector : public Matrix
{
public:
    // Vector(int coordinate, ...);
    explicit Vector(std::vector<int>);
    //Vector operator+(const Vector&);
    //Vector operator-(const Vector&);
    //int& operator[](int);
    //const int& operator[](int) const;
    //const int getDimension() const;
    //void print();

    //std::vector<int> coordinates;
private:
    //int _dimensions;
    bool hasCorrectDimension(const Vector&);
};