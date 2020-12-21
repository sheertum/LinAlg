#pragma once

#include <vector>

#include "Limit.h"

class Matrix;

class Vector
{
public:
    // Vector(int coordinate, ...);
    explicit Vector(std::vector<double>);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);

    Matrix operator*(const Matrix&);
    double operator*(const Vector);
    Vector operator*(const double);
    double getLength();
    Vector crossProduct(const Vector& target);

    double& operator[](int);
    const double& operator[](int) const;
    const int getDimension() const;
    void print();

    void normalise();

    void pushBack(double);

    double length() const;

    Matrix toMatrix() const;

public:
    std::vector<double> coordinates;

private:
    bool hasCorrectDimension(const Vector&);
};