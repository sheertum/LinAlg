#include "Matrix.h"

Matrix::Matrix(int rows, int columns, std::vector<std::vector<int>> coordinates) : _rows(rows), _columns(columns), _coordinates(coordinates){}

Matrix::Matrix(int rows, int columns) : _rows(rows), _columns(columns) {
    for(int i=0 ; i < (int)_rows.size(); i++){
        std::vector<int> newColumn{};
        for(int j=0 ; j < (int)_columns.size(); j++){
            newColumn[j] = 0;
        }
        _coordinates[i] = newColumn;
    }
}

Matrix Matrix::operator+(const Matrix& paraMatrix){
    if(!hasSameDimensions(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForAddition");
    }
}

Matrix Matrix::operator-(const Matrix& paraMatrix){
    if(!hasSameDimensions(paraMatrix))
    {
        throw("MatrixesHaveIncompatibleDimensionsForSubtraction");
    }

}

const std::vector<int> Matrix::getDimensions() const{
    return std::vector{(int)_rows.size(), (int)_columns.size()};
}
bool Matrix::hasMultiplicableDimension(const Matrix& parameterMatrix){
    if(parameterMatrix.getDimensions()[0] == (int)_columns.size() && parameterMatrix.getDimensions()[1] == (int)_rows.size()){
        return true;
    }
    return false;
}

bool Matrix::hasSameDimensions(const Matrix& parameterMatrix){
    if(parameterMatrix.getDimensions()[0] == (int)_rows.size() && parameterMatrix.getDimensions()[1] == (int)_columns.size()){
        return true;
    }
    return false;
}