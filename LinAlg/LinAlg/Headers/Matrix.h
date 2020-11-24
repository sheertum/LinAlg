#pragma once

#include <vector>
#include "Vector.h"

class Matrix
{
public:
    Matrix(int width, int height);

    //void setData(const std::vector<int>&);

    int getColumnCount() const;
    int getRowCount() const;

    //Matrix operator+(const Matrix&);
    //Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    //Matrix operator*(const Vector&);
    
    int& operator()(int row, int column);
    int operator()(int row, int column) const;

    void draw();
    const std::vector<int> getData() const;

private:
    int getIndex(int, int) const;

protected:
    bool hasMultiplicableDimension(const Matrix&);
    bool hasSameDimensions(const Matrix&);
    //std::vector<int> convertColumnToVector(int) const;
    int VectorInproduct(std::vector<int>, std::vector<int>);

    std::vector<int> _data;
    int _columnCount;
    int _rowCount;
};