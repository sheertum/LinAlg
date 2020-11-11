#include "Vector.h"

#include <stdarg.h> 
#include <iostream>

// Vector::Vector(float cordinateArgs, ...){
//     va_list coordinateList;
//     dimensions = 0;
//     va_start(coordinateList, cordinateArgs);
    
//     for(dimensions; dimensions < cordinateArgs; dimensions++)
//     {
//     }

//     coordinates = std::vector<float>(dimensions, 0.0f);

//     for(int i = 0; i < cordinateArgs; i++)
//     {
//         coordinates[i] = va_arg(coordinateList, float);
//     }

//     va_end(coordinateList);
//     std::cout << dimensions <<std::endl;
// }

Vector::Vector(std::vector<float> coordinateArgs){
    if(coordinateArgs.size() < 1)
    {
        throw("NoZeroDimensionVectorsAllowed");
    }

    dimensions = coordinateArgs.size();

    coordinates.reserve(dimensions);
    coordinates = coordinateArgs;
    
}

Vector Vector::operator+(const Vector& target)
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }

}
Vector Vector::operator-(const Vector& target)
{
    if(!hasCorrectDimension(target))
    {
        throw("DimensionsAreIncompatible");
    }

}

bool Vector::hasCorrectDimension(const Vector& target)
{
    if(dimensions == target.dimensions)
    {
        return true;
    }

    return false;
}