#pragma once

#include <vector>
#include <array>

#include "Limit.h"

class Matrix;

class Vector
{
public:
    // Vector(int coordinate, ...);
    explicit Vector(std::vector<double>);
    Vector operator+(const Vector&) const;
    Vector operator+(double) const;
    Vector operator-(const Vector&) const;
    Vector operator-(double) const;

    Matrix operator*(const Matrix&) const;
    double operator*(const Vector&) const;
    Vector operator*(const double) const;

    Vector operator%(double) const;

    void translate (Vector vec);

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

    double getAngle(const Vector&, bool inRadians = true) const;
    std::array<double, 3> getAngles(const Vector&, bool inRadians = true) const;

public:
    std::vector<double> coordinates;

private:
    bool hasCorrectDimension(const Vector&) const;
};