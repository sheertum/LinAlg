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

    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    Matrix operator*(const Vector&);

    void translate (double, double, double);
    void scale (double, double, double);
    void rotate(double);
    double& operator()(int row, int column);
    double operator()(int row, int column) const;

    void draw();
    const std::vector<double> getData() const;

private:
    int getIndex(int, int) const;
    void itirativeMiltiply(Matrix);

protected:
    bool hasMultiplicableDimension(const Matrix&);
    bool hasSameDimensions(const Matrix&);
    double VectorInproduct(std::vector<double>, std::vector<double>);

    std::vector<double> _data;
    int _columnCount;
    int _rowCount;
};