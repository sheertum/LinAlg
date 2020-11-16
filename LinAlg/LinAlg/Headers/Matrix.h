#pragma once

#include <vector>
#include "Vector.h"

class Matrix
{
public:
    Matrix(int rows, int columns, std::vector<std::vector<int>>);
    Matrix(int rows, int columns);

    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    Matrix operator*(const Vector&);
    std::vector<int>& operator[](int);
    const std::vector<int>& operator[](int) const;
    void draw();

    std::vector<int> getDimensions() const;
protected:
    bool hasMultiplicableDimension(const Matrix&);
    bool hasSameDimensions(const Matrix&);
    std::vector<int> convertColumnToVector(int) const;
    int VectorInproduct(std::vector<int>, std::vector<int>);

    std::vector<std::vector<int>> _rows;
    std::vector<int> _columns;
    std::vector<std::vector<int>> _coordinates;
    int _rowSize;
    int _columnSize;
};