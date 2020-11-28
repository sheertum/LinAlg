#include "Vector.h"
#include "Matrix.h"

#include <stdarg.h> 
#include <iostream>

Vector::Vector(std::vector<double> coordinateArgs){
    if(coordinateArgs.size() < 1)
    {
        throw("NoZeroDimensionVectorsAllowed");
    }

    if(coordinateArgs.size() < 2)
    {
        throw("NoSingleDimensionVectorsAllowed");
    }

    _dimensions = coordinateArgs.size();

    coordinates.reserve(_dimensions);
    coordinates = coordinateArgs;
    
}

Vector Vector::operator+ (const Vector& target)
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }
    Vector result{std::vector<double>(_dimensions, 0.0f)};
    for(int i = 0; i < _dimensions; i++)
    {
        result[i] = coordinates[i] + target[i];
    }

    return result;
}

double Vector::getLength(){
    double result = std::pow(coordinates[0], 2) + std::pow(coordinates[1], 2);

    if(getDimension() == 3){
        result += std::pow(coordinates[2], 2);
    }

    return sqrt(result);
}

Vector Vector::crossProduct(const Vector& target){
    if(_dimensions < 3){
        throw("CrossProductIsOnlyPossibleInThreeDimensions");
    }

    Vector result {{0,0,0}};
    int j = 0;
    int k = 0;

    for(int i = 0; i < _dimensions; i++){
        j = i +1;
        k = i +2;
        if(j >= _dimensions){
            j = 0;
            k = j + 1;
        }

        if(k >= _dimensions){
            k = 0;
        }

        result[i] = coordinates[j]*target[k] - coordinates[k]*target[j];
    }

    return result;
}

Vector Vector::operator-(const Vector& target)
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }

    Vector result{std::vector<double>(_dimensions, 0.0f)};
    for(int i = 0; i < _dimensions; i++)
    {
        result[i] = coordinates[i] - target[i];
    }

    return result;
}

Matrix Vector::operator*(const Matrix& matrix)
{

    return matrix;
}

Vector Vector::operator*(const double scalar)
{
    Vector result{std::vector<double>()};
    for(auto& coordinate : coordinates){
        coordinate = coordinate*scalar;
    }
}

double Vector::operator*(Vector inproductVector)
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
    return _dimensions;
}

bool Vector::hasCorrectDimension(const Vector& target)
{
    if(_dimensions == target.getDimension())
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