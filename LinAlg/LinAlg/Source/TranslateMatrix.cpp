#include "TranslateMatrix.h"

TranslateMatrix::TranslateMatrix(double x, double y) : UnitaryMatrix{3}{
    _data[getIndex(_columnCount-1, 0)] = x;
    _data[getIndex(_columnCount -1, 1)] = y;
}

TranslateMatrix::TranslateMatrix(double x, double y, double z) : UnitaryMatrix{4}{
    _data[getIndex(_columnCount -1, 0)] = x;
    _data[getIndex(_columnCount -1, 1)] = y;
    _data[getIndex(_columnCount -1, 2)] = z;
}

TranslateMatrix::TranslateMatrix(Vector vec) : UnitaryMatrix{vec.getDimension()}{
    _data[getIndex(_columnCount -1, 0)] = vec[0];
    _data[getIndex(_columnCount -1, 1)] = vec[1];
    _data[getIndex(_columnCount -1, 2)] = vec[2];
}