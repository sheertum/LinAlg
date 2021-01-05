#include "XRotateMatrix.h"
#include <cmath>

XRotateMatrix::XRotateMatrix(double alpha, int rows): UnitaryMatrix{rows}{
    if(rows < 3){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(1, 1) = std::cos(alpha);
    this->operator()(1, 2) = std::sin(alpha);
    this->operator()(2, 1) = -1*std::sin(alpha);
    this->operator()(2, 2) = std::cos(alpha);
}