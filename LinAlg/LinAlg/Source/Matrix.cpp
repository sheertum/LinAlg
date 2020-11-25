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
            int sum = 0;
            for(int q = 0; q < _columnCount; q++){
                sum += _data[getIndex(q,i)]*paraMatrix(j,q);
            }
            result(j,i ) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Vector& vector){
   std::vector<std::vector<int>> vectormatrix {vector.coordinates};
   Matrix paraMatrix{1, vector.getDimension()};
   for(int i = 0; i < vector.getDimension(); i++){
       paraMatrix(0,i) = vector[i];
   }

   return *this * paraMatrix;
}

int& Matrix::operator()(int column, int row)
{
    return _data[getIndex(column, row)];
}

int Matrix::operator()(int column, int row) const
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

int Matrix::VectorInproduct(std::vector<int> row, std::vector<int> column){
    int result = 0;
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

const std::vector<int> Matrix::getData() const{
    return _data;
}

void Matrix::translate (int x, int y, int z){
    UnitaryMatrix translateMatrix {_rowCount +1};
    if(_rowCount > 2){
        translateMatrix(_rowCount , 2 ) = z;
    }

    if(_rowCount > 1){
        translateMatrix(_rowCount, 1) = y;
    }

    translateMatrix(_rowCount, 0) = x;

    for (int i = 0; i < _columnCount; i++) {
        Matrix temp = { 1, _rowCount+1 };
        
        for (int j = 0; j < _rowCount; j++) {
            temp(0, j) = this->operator()(i, j);
        }

        temp(0, _rowCount) = 1;

        temp = translateMatrix * temp;

        for (int j = 0; j < _rowCount; j++) {
            this->operator()(i, j) = temp(0, j);
        }
    }
}

void Matrix::scale(int x, int y, int z){
     UnitaryMatrix translateMatrix {_rowCount +1};
    if(_rowCount > 2){
        translateMatrix(2, 2 ) = z;
    }

    if(_rowCount > 1){
        translateMatrix(1, 1) = y;
    }

    translateMatrix(0, 0) = x;

    for (int i = 0; i < _columnCount; i++) {
        Matrix temp = { 1, _rowCount+1 };
        
        for (int j = 0; j < _rowCount; j++) {
            temp(0, j) = this->operator()(i, j);
        }

        temp(0, _rowCount) = 1;

        temp = translateMatrix * temp;

        for (int j = 0; j < _rowCount; j++) {
            this->operator()(i, j) = temp(0, j);
        }
    }
}