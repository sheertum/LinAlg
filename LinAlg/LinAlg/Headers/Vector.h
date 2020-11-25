#pragma once

#include <vector>

class Matrix;

class Vector
{
public:
    // Vector(int coordinate, ...);
    explicit Vector(std::vector<double>);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);

    Matrix operator*(const Matrix&);

    double& operator[](int);
    const double& operator[](int) const;
    const int getDimension() const;
    void print();

    std::vector<double> coordinates;
private:
    int _dimensions;
    bool hasCorrectDimension(const Vector&);
};