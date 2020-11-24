#include "Matrix.h"

#include <iostream>
#include <string>

Matrix::Matrix(int width, int height) : _width(width), _height(height), _data{ width + height }{
    if(width = 0 || height == 0){
        throw "rows or columns cant be 0";
    }

    std::fill(_data.begin(), _data.end(), 0);
}

void Matrix::fillColumn(const std::vector<int>& column)
{
    if (column.size() > getHeight())
    {
        throw "column size is to big";
    }

    for (size_t i = 0; i < getHeight(); i++)
    {
        get() 
    }
}

Matrix Matrix::operator+(const Matrix& paraMatrix){
    if(!hasSameDimensions(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForAddition");
    }
    Matrix result{_rowSize, _columnSize};
    for(int i =0 ; i < _rowSize; i++ ){
        std::vector<int> paraColumn {paraMatrix[i]};
        std::vector<int> thisColumn {_coordinates[i]};
        std::vector<int> columnSum{};

        for(int j = 0; j <_columnSize; j++){
            columnSum.push_back(paraColumn[j]+thisColumn[j]);
        }
        result[i] = columnSum;
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& paraMatrix){
    if(!hasSameDimensions(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForSubtraction");
    }

    Matrix result{_rowSize, _columnSize};
    for(int i =0 ; i < _rowSize; i++ ){
        std::vector<int> paraColumn {paraMatrix[i]};
        std::vector<int> thisColumn { _coordinates[i]};
        std::vector<int> columnSum{};

        for(int j = 0; j <_columnSize; j++){
            columnSum.push_back(paraColumn[j]-thisColumn[j]);
        }
        result[i] = columnSum;
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& paraMatrix){
    if(!hasMultiplicableDimension(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForMultiplication");
    }
    int resultcolumnSize = paraMatrix.getDimensions()[1];
    int resultrowSize = _rowSize;
    Matrix result{resultrowSize, resultcolumnSize};

    for(int i = 0; i < resultrowSize; i++){
        std::vector<int> newColumn {};
        std::vector<int> row = _coordinates[i];

        for(int j = 0; j < resultcolumnSize; j++){
            std::vector<int> column = paraMatrix.convertColumnToVector(j);
            newColumn.push_back(VectorInproduct(row, column));
        }
        result[i] = newColumn;
    }
    return result;
}

Matrix Matrix::operator*(const Vector& vector){
    std::vector<std::vector<int>> vectormatrix {vector.coordinates};
    Matrix paraMatrix{1, 3, vectormatrix};
    Matrix result = *this * paraMatrix;
    return result;
}

int& Matrix::operator()(int row, int column)
{
    int index  = row * _width + column
}

int Matrix::operator()(int column, int row) const
{
    return 0;
}

int Matrix::getWidth() const
{
    return _width;
}

int Matrix::getHeight() const
{
    return _height;
}

std::vector<int> Matrix::convertColumnToVector(int columnNumber)const {
    std::vector<int> result{};

    for(int i = 0; i < _rowSize; i++){
        result.push_back(_coordinates[i][columnNumber]);
    }
    return result;
}

bool Matrix::hasMultiplicableDimension(const Matrix& parameterMatrix){
    return( parameterMatrix.getDimensions()[1] == _rowSize);
}

bool Matrix::hasSameDimensions(const Matrix& parameterMatrix){
    return (parameterMatrix.getDimensions()[1] == _columnSize && parameterMatrix.getDimensions()[0] == _rowSize);
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
            std::cout << _coordinates[i][j] << " ";
        }
        std::cout << std::endl;
    }   
}