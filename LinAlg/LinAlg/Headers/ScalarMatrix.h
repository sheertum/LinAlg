#pragma once
#include "UnitaryMatrix.h"

class ScalarMatrix : public UnitaryMatrix{
public:
    ScalarMatrix(double x, double y);
    ScalarMatrix(double x, double y, double z);
};