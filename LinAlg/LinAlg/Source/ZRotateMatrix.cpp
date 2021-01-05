#include "ZRotateMatrix.h"
#include <cmath>

ZRotateMatrix::ZRotateMatrix(double alpha, int rows) : UnitaryMatrix{rows}{
    if(rows < 2){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(0, 0) = std::cos(alpha);
    this->operator()(0, 1) = std::sin(alpha);
    this->operator()(1, 0) = -1*std::sin(alpha);
    this->operator()(1, 1) = std::cos(alpha);
}