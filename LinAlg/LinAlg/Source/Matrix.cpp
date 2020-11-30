#include "Matrix.h"
#include "UnitaryMatrix.h"

#include <iostream>
#include <string>

Matrix::Matrix(int columnCount, int rowCount) : _columnCount(columnCount), _rowCount(rowCount){
    if(columnCount < 1 || rowCount < 1){
        throw "rows or columns cant be 0";
    }

    _data.resize(columnCount * rowCount);
}

Matrix::Matrix(int width, int height, std::vector<double> data) : Matrix(width, height)
{
    _data = data;
}

Matrix Matrix::operator+(const Matrix& paraMatrix){
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

Matrix Matrix::operator-(const Matrix& paraMatrix){
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

Matrix Matrix::operator*(const Matrix& paraMatrix){
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

Matrix Matrix::operator*(const Vector& vector){
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

int Matrix::getColumnCount() const
{
    return _columnCount;
}

int Matrix::getRowCount() const
{
    return _rowCount;
}

bool Matrix::hasMultiplicableDimension(const Matrix& parameterMatrix){
    return(_columnCount == parameterMatrix.getRowCount());
}

bool Matrix::hasSameDimensions(const Matrix& parameterMatrix){
    return (parameterMatrix.getColumnCount() == _columnCount && parameterMatrix.getRowCount() == _rowCount);
}

double Matrix::VectorInproduct(std::vector<double> row, std::vector<double> column){
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

void Matrix::translate (double x, double y, double z){
    UnitaryMatrix translateMatrix {_rowCount +1};
    if(_rowCount > 2){
        translateMatrix(_rowCount , 2 ) = z;
    }

    if(_rowCount > 1){
        translateMatrix(_rowCount, 1) = y;
    }

    translateMatrix(_rowCount, 0) = x;

    itirativeMultiply(translateMatrix);
}

void Matrix::scale(double x, double y, double z){
     UnitaryMatrix translateMatrix {_rowCount +1};
    if(_rowCount > 2){
        translateMatrix(2, 2 ) = z;
    }

    if(_rowCount > 1){
        translateMatrix(1, 1) = y;
    }

    translateMatrix(0, 0) = x;

    itirativeMultiply(translateMatrix);
}

void Matrix::scale(double x){
     UnitaryMatrix translateMatrix {_rowCount +1};
    if(_rowCount > 2){
        translateMatrix(2, 2 ) = x;
    }

    if(_rowCount > 1){
        translateMatrix(1, 1) = x;
    }

    translateMatrix(0, 0) = x;

    itirativeMultiply(translateMatrix);
}

void Matrix::zRotate(double alpha) {
    UnitaryMatrix translateMatrix{ _rowCount + 1 };

    if (_rowCount > 1) {
        translateMatrix(0, 0) = cos(alpha * 3.14159265 / 180.0 );
        translateMatrix(0, 1) = -sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(1, 0) = sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(1, 1) = cos(alpha * 3.14159265 / 180.0 );
    }

    itirativeMultiply(translateMatrix);
}

void Matrix::yRotate(double alpha) {
    UnitaryMatrix translateMatrix{ _rowCount + 1 };

    if (_rowCount > 1) {
        translateMatrix(0, 0) = cos(alpha * 3.14159265 / 180.0 );
        translateMatrix(0, 2) = sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(2, 0) = -sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(2, 2) = cos(alpha * 3.14159265 / 180.0 );
    }

    itirativeMultiply(translateMatrix);
}

void Matrix::xRotate(double alpha) {
    UnitaryMatrix translateMatrix{ _rowCount + 1 };

    if (_rowCount > 1) {
        translateMatrix(1, 1) = cos(alpha * 3.14159265 / 180.0 );
        translateMatrix(1, 2) = -sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(2, 1) = sin(alpha * 3.14159265 / 180.0 );
        translateMatrix(2, 2) = cos(alpha * 3.14159265 / 180.0 );
    }

    itirativeMultiply(translateMatrix);
}

void Matrix::originLineRotate(Vector line, double alpha){
    double x = line.coordinates[0];
    double y = line.coordinates[1];
    double z = line.coordinates[2];
    double x2z2 = sqrt(x*x+z*z);
    double x2y2z2 = sqrt(x*x+y*y+z*z);

    Matrix M5 = UnitaryMatrix(4);
    M5(0, 0) = x / x2z2;
    M5(0, 2) = -z / x2z2;
    M5(2, 0) = z / x2z2;
    M5(2, 2) = x / x2z2;

    Matrix M4 = UnitaryMatrix(4);
    M4(0, 0) = x2z2 / x2y2z2;
    M4(0, 1) = -y / x2z2;
    M4(1, 0) = y / x2z2;
    M4(1, 1) = x2z2 / x2y2z2;

    Matrix M2 = M4;
    M2(1,0) = M2(1,0)*-1;
    M2(0,1) = M2(1,0)*-1;

    Matrix M1 = M5;
    M1(2,0) = M1(1,0)*-1;
    M1(0,2) = M1(1,0)*-1;

    itirativeMultiply(M5);
    itirativeMultiply(M4);
    xRotate(alpha);
    itirativeMultiply(M2);
    itirativeMultiply(M1);
}

void Matrix::randomLineRotate(Vector first, Vector second, double alpha){
    translate(first.coordinates[0], first.coordinates[1], first.coordinates[2]);
    Vector originLine = second - first;
    originLineRotate(originLine, alpha);
    first = first * -1;
    translate(first.coordinates[0], first.coordinates[1], first.coordinates[2]);
}


void Matrix::itirativeMultiply(Matrix changeMatrix){
        for (int i = 0; i < _columnCount; i++) {
        Matrix temp{ 1, _rowCount + 1 };

        for (int j = 0; j < _rowCount; j++) {
            temp(0, j) = this->operator()(i, j);
        }

        temp(0, _rowCount) = 1;

        temp = changeMatrix * temp;

        for (int j = 0; j < _rowCount; j++) {
            this->operator()(i, j) = temp(0, j);
        }
    }
}