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

    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator*(const Vector&) const;

    void translate (double, double, double);
    void scale (double, double, double);
    void scale (double);
    void xRotate(double);
    void yRotate(double);
    void zRotate(double);
    void originLineRotate(Vector, double);
    void randomLineRotate(Vector, Vector, double);
    double& operator()(int row, int column);
    double operator()(int row, int column) const;

    void draw();
    const std::vector<double> getData() const;

    Vector toVector();

private:
    int getIndex(int, int) const;
    void itirativeMultiply(Matrix);

protected:
    bool hasMultiplicableDimension(const Matrix&) const;
    bool hasSameDimensions(const Matrix&) const;
    double VectorInproduct(std::vector<double>, std::vector<double>) const;

    std::vector<double> _data;
    int _columnCount;
    int _rowCount;
};