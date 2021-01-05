#include "Vector.h"
#include "Matrix.h"
#include "TranslateMatrix.h"

#include <stdarg.h> 
#include <iostream>
#include <cmath>

Vector::Vector(std::vector<double> coordinateArgs){
    if(coordinateArgs.size() < 1)
    {
        throw("NoZeroDimensionVectorsAllowed");
    }

    if(coordinateArgs.size() < 2)
    {
        throw("NoSingleDimensionVectorsAllowed");
    }

    coordinates = coordinateArgs;
}

Vector Vector::operator+ (const Vector& target) const
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }
    Vector result{std::vector<double>(getDimension(), 0.0f)};
    for(int i = 0; i < getDimension(); i++)
    {
        result[i] = coordinates[i] + target[i];
    }

    return result;
}

Vector Vector::operator+(double value) const
{
    Vector result{ {coordinates} };
    for (auto& i : result.coordinates)
    {
        i += value;
    }

    return result;
}

double Vector::getLength() const {
    double result = std::pow(coordinates[0], 2) + std::pow(coordinates[1], 2);

    if(getDimension() == 3){
        result += std::pow(coordinates[2], 2);
    }

    return sqrt(result);
}

Vector Vector::crossProduct(const Vector& target) const{
    if(getDimension() < 3){
        throw("CrossProductIsOnlyPossibleInThreeDimensions");
    }

    Vector result {target.coordinates};
    std::fill(result.coordinates.begin(), result.coordinates.end(), 0);

    int j = 0;
    int k = 0;

    for(int i = 0; i < getDimension(); i++){
        j = i +1;
        k = i +2;
        if(j >= getDimension()){
            j = 0;
            k = j + 1;
        }

        if(k >= getDimension()){
            k = 0;
        }
        double alfa = coordinates[j] * target[k];
        double beta = coordinates[k] * target[j];
        result[i] = alfa - beta;
    }

    return result;
}

Vector Vector::operator-(const Vector& target) const
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }

    Vector result{std::vector<double>(getDimension(), 0.0f)};
    for(int i = 0; i < getDimension(); i++)
    {
        result[i] = coordinates[i] - target[i];
    }

    return result;
}

Vector Vector::operator-(double value) const
{
    return this->operator+(-value);
}

Matrix Vector::operator*(const Matrix& matrix) const
{
    Matrix vectorMatrix = this->toMatrix();
    return vectorMatrix * matrix;
}

Vector Vector::operator*(const double scalar) const
{
    std::vector<double> buffer;
    buffer.resize(coordinates.size());
    Vector result{ buffer };

    for (int i = 0; i < coordinates.size(); i++) {
        result[i] = coordinates[i]*scalar;
    }

    return result;
}

Vector Vector::operator%(double value) const
{
    Vector result{ this->coordinates };
    for (size_t i = 0; i < coordinates.size(); i++)
    {
        result[i] = std::fmod(result[i], value);
    }

    return result;
}

void Vector::translate(const Vector& vec)
{
    Matrix result = this->toMatrix();
    result.translate(vec);
    *this = result.toVector();
}

bool Vector::operator!=(const Vector& other) const
{
    return !(coordinates == other.coordinates);
}

double Vector::operator*(const Vector inproductVector) const
{
    double result= 0;
    for(int i = 0; i < this->getDimension(); i++){
        result += coordinates[i]*inproductVector[i];
    }
    return result;
}

const double& Vector::operator[](int target) const
{
    return coordinates[target];
}

double& Vector::operator[](int target)
{
     return coordinates[target];
}


const int Vector::getDimension() const
{
    return coordinates.size();
}

bool Vector::hasCorrectDimension(const Vector& target) const
{
    if(getDimension() == target.getDimension())
    {
        return true;
    }

    return false;
}

void Vector::print()
{
    std::cout << "[";
    for(auto coord : coordinates)
    {
        std::cout << " " <<coord ;
    }
    std::cout << " ]";
}

void Vector::normalise()
{
    double magnitude = length();

    for (auto& i : coordinates) {
        i /= magnitude;
    }
}

void Vector::pushBack(double data)
{
    coordinates.push_back(data);
}

double Vector::length() const
{
    double lengthSum = 0.0;

    for (size_t i = 0; i < coordinates.size(); i++)
    {
        lengthSum += coordinates[i] * coordinates[i];
    }

    return std::sqrt(lengthSum);
}

Matrix Vector::toMatrix() const
{
    Matrix result{ 1, getDimension() };

    for (size_t i = 0; i < getDimension(); i++)
    {
        result(0, i) = coordinates[i];
    }

    return result;
}