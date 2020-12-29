#include "ZRotateMatrix.h"

ZRotateMatrix::ZRotateMatrix(double alpha, int rows) : UnitaryMatrix{rows}{
    if(rows < 2){
        throw "ImpossibleDimension for rotation";
    }

    this->operator()(0, 0) = cos(alpha * 3.14159265 / 180.0 );
    this->operator()(0, 1) = sin(alpha * 3.14159265 / 180.0 );
    this->operator()(1, 0) = -sin(alpha * 3.14159265 / 180.0 );
    this->operator()(1, 1) = cos(alpha * 3.14159265 / 180.0 );
}