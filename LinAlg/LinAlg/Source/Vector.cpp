#include "Vector.h"

#include <stdarg.h> 
#include <iostream>

// Vector::Vector(int cordinateArgs, ...){
//     va_list coordinateList;
//     dimensions = 0;
//     va_start(coordinateList, cordinateArgs);
    
//     for(dimensions; dimensions < cordinateArgs; dimensions++)
//     {
//     }

//     coordinates = std::vector<int>(dimensions, 0.0f);

//     for(int i = 0; i < cordinateArgs; i++)
//     {
//         coordinates[i] = va_arg(coordinateList, int);
//     }

//     va_end(coordinateList);
//     std::cout << dimensions <<std::endl;
// }

Vector::Vector(std::vector<int> coordinateArgs){
    if(coordinateArgs.size() < 1)
    {
        throw("NoZeroDimensionVectorsAllowed");
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
    Vector result{std::vector<int>(_dimensions, 0.0f)};
    for(int i = 0; i < _dimensions; i++)
    {
        result[i] = coordinates[i] + target[i];
    }

    return result;
}

Vector Vector::operator-(const Vector& target)
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }

    Vector result{std::vector<int>(_dimensions, 0.0f)};
    for(int i = 0; i < _dimensions; i++)
    {
        result[i] = coordinates[i] - target[i];
    }

    return result;
}

const int& Vector::operator[](int target) const
{
    return coordinates[target];
}

int& Vector::operator[](int target)
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