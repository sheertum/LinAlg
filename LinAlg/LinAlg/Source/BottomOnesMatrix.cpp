#include "BottomOnesMatrix.h"

BottomOnesMatrix::BottomOnesMatrix(int width) : Matrix(width, width){
    for(int i = 0; i < width; i++){
        this->operator()(i,_rowCount-1) = 1;
    }
}