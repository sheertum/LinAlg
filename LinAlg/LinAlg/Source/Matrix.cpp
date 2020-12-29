#include "Matrix.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"
#include "ScalarMatrix.h"
#include "XRotateMatrix.h"
#include "YRotateMatrix.h"
#include "ZRotateMatrix.h"
#include "BottomOnesMatrix.h"

#include <iostream>
#include <string>

Matrix::Matrix(int columnCount, int rowCount) : _columnCount(columnCount), _rowCount(rowCount){
    if(columnCount < 1 || rowCount < 1){
        throw "rows or columns cant be 0";
    }

    _data.resize(columnCount * rowCount);
    std::fill(_data.begin(), _data.end(), 0);
}

Matrix::Matrix(int width, int height, std::vector<double> data) : Matrix(width, height)
{
    _data = data;
}

Matrix Matrix::operator+(const Matrix& paraMatrix) const{
   if(!hasSameDimensions(paraMatrix))
   {
       throw("MatrixesHaveIncompatibleDimensionsForAddition");
   }
   Matrix result{_columnCount, _rowCount};

   for(int i =0 ; i < _columnCount; i++ ){
       for(int j = 0; j <_rowCount; j++){
           result (i, j) = _data[getIndex(i,j)] + paraMatrix(i,j);
       }
   }

   return result;
}

Matrix Matrix::operator-(const Matrix& paraMatrix) const{
   if(!hasSameDimensions(paraMatrix))
   {
       throw("MatrixesHaveIncompatibleDimensionsForSubtraction");
   }

   Matrix result{_rowCount, _columnCount};

   for(int i =0 ; i < _columnCount; i++ ){
       for(int j = 0; j <_rowCount; j++){
           result (i, j) = _data[getIndex(i,j)] - paraMatrix(i,j);
       }
   }
   return result;
}

Matrix Matrix::operator*(const Matrix& paraMatrix) const{
    if(!hasMultiplicableDimension(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForMultiplication");
    }

    int resultcolumnSize = paraMatrix.getColumnCount();
    int resultrowSize = _rowCount;
    Matrix result{resultcolumnSize, resultrowSize};
    
    for(int i = 0; i < resultrowSize; i++){
        for(int j = 0; j < resultcolumnSize; j++){
            double sum = 0;
            for(int q = 0; q < _columnCount; q++){
                sum += _data[getIndex(q,i)]*paraMatrix(j,q);
            }
            result(j,i ) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Vector& vector) const{
   std::vector<std::vector<double>> vectormatrix {vector.coordinates};
   Matrix paraMatrix{1, vector.getDimension()};
   for(int i = 0; i < vector.getDimension(); i++){
       paraMatrix(0,i) = vector[i];
   }

   return *this * paraMatrix;
}

double& Matrix::operator()(int column, int row)
{
    return _data[getIndex(column, row)];
}

double Matrix::operator()(int column, int row) const
{
    return _data[getIndex(column, row)];
}

void Matrix::operator()(int row, int column, const Vector& vec, bool vertical)
{
    for (size_t i = 0; i < vec.getDimension(); i++)
    {
        if (vertical)
        {
            this->operator()(row, column + i) = vec[i];
        }
        else
        {
            this->operator()(row + i, column) = vec[i];
        }
    }
}

int Matrix::getColumnCount() const
{
    return _columnCount;
}

int Matrix::getRowCount() const
{
    return _rowCount;
}

bool Matrix::hasMultiplicableDimension(const Matrix& parameterMatrix) const {
    return(_columnCount == parameterMatrix.getRowCount());
}

bool Matrix::hasSameDimensions(const Matrix& parameterMatrix) const{
    return (parameterMatrix.getColumnCount() == _columnCount && parameterMatrix.getRowCount() == _rowCount);
}

double Matrix::VectorInproduct(std::vector<double> row, std::vector<double> column) const {
    double result = 0;
    for(int i = 0; i < (int)row.size(); i++){
        result += row[i]*column[i];
    }
    return result;
}

void Matrix::draw(){
    for(int i =0 ; i < _rowCount; i++ ){
        for(int j = 0; j < _columnCount; j++){
            std::cout << this->operator()(j, i) << " ";
        }
        std::cout << std::endl;
    }   
}

int Matrix::getIndex(int x, int y) const{
    if(x > _columnCount || y > _rowCount){
        throw "IndexOutOfBoundsException";
    }

    return x + (y * _columnCount);    
}

const std::vector<double> Matrix::getData() const{
    return _data;
}

Vector Matrix::toVector()
{
    return Vector{ _data };
}

Matrix Matrix::simpleInverse() const
{
    Matrix matrix(4,4);
    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t y = 0; y < 3; y++)
        {
            matrix(i, y) = this->operator()(y, i);
            matrix(3, y) = 0.0;
        }
    }

    matrix(0,3) = -(this->operator()(0,3) * matrix(0,0) + this->operator()(1, 3) * matrix(0, 1) + this->operator()(2, 3) * matrix(0, 2));
    matrix(0,3) = -(this->operator()(0,3) * matrix(1,0) + this->operator()(1, 3) * matrix(1, 1) + this->operator()(2, 3) * matrix(1, 2));
    matrix(0,3) = -(this->operator()(0,3) * matrix(2,0) + this->operator()(1, 3) * matrix(2, 1) + this->operator()(2, 3) * matrix(2, 2));
    matrix(3, 3) = 1;

    return matrix;
}

void Matrix::translate (double x, double y, double z){
    upsize();
    TranslateMatrix translateMatrix{x,y,z};
    itirativeMultiply(translateMatrix);
    downsize();
}

void Matrix::translate (Vector vec){
    upsize();
    TranslateMatrix translateMatrix{vec};
    itirativeMultiply(translateMatrix);
    downsize();
}

void Matrix::scale(double x, double y, double z){
    ScalarMatrix scalarMatrix {x,y,z};
    itirativeMultiply(scalarMatrix);
}

void Matrix::scale(double x){
    ScalarMatrix scalarMatrix {x,x,x};
    itirativeMultiply(scalarMatrix);
}

void Matrix::zRotate(double alpha) {
    upsize();
    itirativeMultiply(ZRotateMatrix(alpha, _rowCount));
    downsize();
}

void Matrix::yRotate(double alpha) {
    upsize();
    itirativeMultiply(YRotateMatrix(alpha, _rowCount));
    downsize();
}

void Matrix::xRotate(double alpha) {
    upsize();
    itirativeMultiply(XRotateMatrix(alpha, _rowCount));
    downsize();
}

void Matrix::originLineRotate(Vector line, double alpha){
    double x = line.coordinates[0];
    double y = line.coordinates[1];
    double z = line.coordinates[2];
    if (x == 0 && z == 0 && y == 0) {
        throw "CantRotateAroundPoint";
    }

    if (x == 0) {
        if (z == 0) {
            yRotate(alpha);
            return;
        }
        else if (y == 0) {
            zRotate(alpha);
            return;
        }
    }

    double x2z2 = sqrt(x*x+z*z);
    double x2y2z2 = sqrt(x*x+y*y+z*z);

    Matrix M1 = UnitaryMatrix(4);
    M1(0, 0) = x / x2z2;
    M1(0, 2) = -1*z / x2z2;
    M1(2, 0) = z / x2z2;
    M1(2, 2) = x / x2z2;

    Matrix M2 = UnitaryMatrix(4);
    M2(0, 0) = x2z2 / x2y2z2;
    M2(1, 1) = x2z2 / x2y2z2;
    M2(0, 1) = -1*y / x2y2z2;
    M2(1, 0) = y / x2y2z2;
    
    Matrix M3 = XRotateMatrix(alpha, 4);
    
    Matrix M4 = UnitaryMatrix(4);
    M4._data= M2._data;
    M4(1,0) = M4(1,0)*-1;
    M4(0,1) = M4(0,1)*-1;
    
    Matrix M5 = UnitaryMatrix(4);
    M5._data = M1._data;
    M5(2,0) = M5(2,0)*-1;
    M5(0,2) = M5(0,2)*-1;
    
    Matrix total = M1 * M2 * M3 * M4 * M5;
    upsize();
    itirativeMultiply(total);
    downsize();
}

void Matrix::randomLineRotate(Vector first, Vector second, double alpha){
    translate(first*-1);
    Vector originLine = second - first;
    originLineRotate(originLine, alpha);
    translate(first);
}


void Matrix::itirativeMultiply(Matrix changeMatrix){
    for (int i = 0; i < _columnCount; i++) {
        Matrix temp{ 1, _rowCount };

        for (int j = 0; j < _rowCount; j++) {
            temp(0, j) = this->operator()(i, j);
        }

        temp = changeMatrix * temp;

        for (int j = 0; j < _rowCount; j++) {
            this->operator()(i, j) = temp(0, j);
        }
    }
}

void Matrix::upsize(){
    Matrix growHeightMatrix = UnitaryMatrix(_rowCount, _rowCount+1);
    Matrix bottomOnes = BottomOnesMatrix(_columnCount, _rowCount + 1);
    
    Matrix result{ _columnCount, _rowCount, _data};

    result = growHeightMatrix * result;
    result = result + bottomOnes;
    _data = result._data;
    _columnCount = result._columnCount;
    _rowCount = result._rowCount;
}

void Matrix::downsize(){
    Matrix shrinkHeightMatrix = UnitaryMatrix(_rowCount, _rowCount-1);
    Matrix result{ _columnCount, _rowCount, _data};

    result = shrinkHeightMatrix * result;
    _data = result._data;
    _columnCount = result._columnCount;
    _rowCount = result._rowCount;
}