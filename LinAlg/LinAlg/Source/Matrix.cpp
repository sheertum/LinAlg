#include "Matrix.h"

#include <iostream>
#include <string>

Matrix::Matrix(int columnCount, int rowCount) : _columnCount(columnCount), _rowCount(rowCount), _data{ columnCount +rowCount }{
    if(columnCount = 0 || rowCount == 0){
        throw "rows or columns cant be 0";
    }

    std::fill(_data.begin(), _data.end(), 0);
}

void Matrix::fillColumn(const std::vector<int>& column)
{
    if (column.size() > getRowCount())
    {
        throw "column size is to big";
    }

    for (size_t i = 0; i < getRowCount(); i++)
    {
    }
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
    
    for(int i = 0; i < _columnCount; i++){
        for(int j = 0; j < _rowCount; j++){
            
        }
    }
    return result;
}

Matrix Matrix::operator*(const Vector& vector){
    std::vector<std::vector<int>> vectormatrix {vector.coordinates};
    Matrix paraMatrix{1, 3, vectormatrix};
    Matrix result = *this * paraMatrix;
    return result;
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

std::vector<int> Matrix::convertColumnToVector(int columnNumber)const {
    std::vector<int> result{};

    for(int i = 0; i < _rowCount; i++){
        result.push_back(_data[i][columnNumber]);
    }
    return result;
}

bool Matrix::hasMultiplicableDimension(const Matrix& parameterMatrix){
    return(_rowCount == parameterMatrix.getColumnCount());
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
    for(int i =0 ; i < (int)_rows.size(); i++ ){
        for(int j = 0; j < (int)_columns.size(); j++){
            std::cout << _data[i][j] << " ";
        }
        std::cout << std::endl;
    }   
}

int Matrix::getIndex(int x, int y) const{
    if(x > _columnCount || y > _rowCount){
        throw "IndexOutOfBoundsException";
    }

    return x + ((y-1) * _rowCount);    
}

const std::vector<int> Matrix::getData() const{
    return _data;
}