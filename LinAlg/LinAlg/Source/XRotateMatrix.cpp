#include "XRotateMatrix.h"

XRotateMatrix::XRotateMatrix(double alpha, int rows): UnitaryMatrix{rows+1}{
    if(rows < 3){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(1, 1) = cos(alpha * 3.14159265 / 180.0 );
    this->operator()(1, 2) = sin(alpha * 3.14159265 / 180.0 );
    this->operator()(2, 1) = -sin(alpha * 3.14159265 / 180.0 );
    this->operator()(2, 2) = cos(alpha * 3.14159265 / 180.0 );
}