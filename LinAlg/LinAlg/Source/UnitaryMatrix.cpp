#include "UnitaryMatrix.h"

UnitaryMatrix::UnitaryMatrix(int size) : Matrix(size, size){
    for(int i = 0; i < size; i++){
        this->operator()(i,i) = 1;
    }
}