#pragma once

#include "UnitaryMatrix.h"

class ZRotateMatrix : public UnitaryMatrix{
public:
    explicit ZRotateMatrix(double,int);
};