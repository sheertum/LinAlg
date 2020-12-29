#include "ScalarMatrix.h"

ScalarMatrix::ScalarMatrix(double x, double y) : UnitaryMatrix{2}{
    _data[getIndex(0, 0)] = x;
    _data[getIndex(1, 1)] = y;
}

ScalarMatrix::ScalarMatrix(double x, double y, double z) : UnitaryMatrix{3}{
    _data[getIndex(0, 0)] = x;
    _data[getIndex(1, 1)] = y;
    _data[getIndex(2, 2)] = z;
}