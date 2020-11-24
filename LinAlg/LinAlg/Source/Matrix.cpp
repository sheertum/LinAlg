#include "Matrix.h"

#include <iostream>

Matrix::Matrix(int rows, int columns, std::vector<std::vector<int>> coordinates) : _rows(rows), _columns(columns), _coordinates(coordinates){
    if(rows = 0 || columns == 0){
        std::cout << "rows or columns cant be 0";
    }
    _rowSize = _rows.size();
    _columnSize = _columns.size();
}

Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
    if(rows = 0 || columns == 0){
        std::cout << "rows or columns cant be 0";
    }
    _rowSize = _rows.size();
    _columnSize = _columns.size();

    for(int i=0 ; i < _rowSize; i++){
        std::vector<int> newColumn{};
        for(int j=0 ; j < _columnSize; j++){
            newColumn.push_back(0);
        }
        _coordinates.push_back(newColumn);
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

const  std::vector<int>& Matrix::operator[](int target) const
{
    return _coordinates[target];
}

std::vector<int>& Matrix::operator[](int target)
{
    return _coordinates[target];
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

std::vector<int> Matrix::getDimensions() const{
    return std::vector<int>{_rowSize, _columnSize};
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