#include "YRotateMatrix.h"

YRotateMatrix::YRotateMatrix(double alpha, int rows) : UnitaryMatrix{ rows } {
    if(rows < 3){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(0, 0) = cos(alpha * 3.14159265 / 180.0);
    this->operator()(0, 2) = -sin(alpha * 3.14159265 / 180.0);
    this->operator()(2, 0) = sin(alpha * 3.14159265 / 180.0);
    this->operator()(2, 2) = cos(alpha * 3.14159265 / 180.0);
}