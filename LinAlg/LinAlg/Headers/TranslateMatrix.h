#pragma once

#include "UnitaryMatrix.h"

class TranslateMatrix : public UnitaryMatrix{
public:
    TranslateMatrix(double, double);
    TranslateMatrix(double, double, double);
    TranslateMatrix(Vector vec);
};