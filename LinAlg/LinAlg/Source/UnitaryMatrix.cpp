#include "UnitaryMatrix.h"

UnitaryMatrix::UnitaryMatrix(int size) : Matrix(size, size){
    for(int i = 0; i < size; i++){
        this->operator()(i,i) = 1;
    }
}

UnitaryMatrix::UnitaryMatrix(int width, int height) : Matrix(width, height){
    int minimum = (width < height) ? width : height;
    for(int i = 0; i < minimum; i++){
        this->operator()(i,i) = 1;
    }
}