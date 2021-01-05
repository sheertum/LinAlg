#include "YRotateMatrix.h"
#include <cmath>

YRotateMatrix::YRotateMatrix(double alpha, int rows) : UnitaryMatrix{ rows } {
    if(rows < 3){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(0, 0) = std::cos(alpha);
    this->operator()(0, 2) = -1* std::sin(alpha);
    this->operator()(2, 0) = std::sin(alpha);
    this->operator()(2, 2) = std::cos(alpha);
}