#include "TranslateMatrix.h"

TranslateMatrix::TranslateMatrix(double x, double y) : UnitaryMatrix{3}{
    _data[getIndex(_rowCount-1, 0)] = x;
    _data[getIndex(_rowCount-1, 1)] = y;
}

TranslateMatrix::TranslateMatrix(double x, double y, double z) : UnitaryMatrix{4}{
    _data[getIndex(_rowCount-1, 0)] = x;
    _data[getIndex(_rowCount-1, 1)] = y;
    _data[getIndex(_rowCount-1, 2)] = z;
}