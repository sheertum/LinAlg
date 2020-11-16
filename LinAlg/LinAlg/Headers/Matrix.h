#pragma once

#include <vector>

class Matrix
{
public:
    Matrix(int rows, int columns, std::vector<std::vector<int>>);
    Matrix(int rows, int columns);
    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    int& operator[](int);
    const int& operator[](int) const;
    const std::vector<int> getDimensions() const;
protected:
    bool hasMultiplicableDimension(const Matrix&);
    bool hasSameDimensions(const Matrix&);
    std::vector<std::vector<int>> _rows;
    std::vector<int> _columns;
    std::vector<std::vector<int>> _coordinates;
};