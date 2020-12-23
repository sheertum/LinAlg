#pragma once

#include <vector>

#include "Limit.h"

class Matrix;

class Vector
{
public:
    // Vector(int coordinate, ...);
    explicit Vector(std::vector<double>);
    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;

    Matrix operator*(const Matrix&) const;
    double operator*(const Vector) const;
    Vector operator*(const double) const;

    Vector operator%(double) const;

    bool operator!=(const Vector&) const;

    double getLength() const;
    Vector crossProduct(const Vector& target) const;

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
    bool hasCorrectDimension(const Vector&) const;
};