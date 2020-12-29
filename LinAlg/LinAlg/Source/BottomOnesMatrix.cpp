#include "BottomOnesMatrix.h"

BottomOnesMatrix::BottomOnesMatrix(int width, int height) : Matrix(width, height){
    for(int i = 0; i < width; i++){
        this->operator()(i,_rowCount-1) = 1;
    }
}