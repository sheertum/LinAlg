#include "Rendering/Renderer.h"
//#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"
#include "UnitaryMatrix.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {
    Matrix matrix{ 6, 2 };
    matrix(0, 0) = 1;
    matrix(0, 1) = 1;

    matrix(1, 0) = 4;
    matrix(1, 1) = 4;
    
    matrix(2, 0) = 5;
    matrix(2, 1) = 5;

    matrix(3, 0) = 6;
    matrix(3, 1) = 6;

    matrix(4, 0) = 7;
    matrix(4, 1) = 7;

    matrix(5, 0) = 8;
    matrix(5, 1) = 8;
    

    matrix.draw();
    matrix.rotate(90);
    matrix.draw();
    
    // left(0, 0) = 1
    ;
    // left(1, 0) = 2;
    // left(2, 0) = 3;
    // left(0, 1) = 4;
    // left(1, 1) = 5;
    // left(2, 1) = 6;

    // right(0, 0) = 7;
    // right(1, 0) = 8;
    // right(0, 1) = 9;
    // right(1, 1) = 10;
    // right(0, 2) = 11;
    // right(1, 2) = 12;

    // Matrix testMatrix(3,3);
    // testMatrix(0, 0) = 1;
    // testMatrix(1, 0) = 2;
    // testMatrix(2, 0) = 3;

    // testMatrix(0, 1) = 1;
    // testMatrix(1, 1) = 2;
    // testMatrix(2, 1) = 3;

    // testMatrix(0, 2) = 1;
    // testMatrix(1, 2) = 2;
    // testMatrix(2, 2) = 3;

    // Vector testVector{{ 1,2,3 } };

    // left.draw();

    // std::cout << std::endl;

    // right.draw();

    // std::cout << std::endl;
    
    // //Matrix result = left * right;
    // //result.draw();

    // std::cout << std::endl;
    
    // Matrix result = testMatrix * testVector;
    // result.draw();
    //test1.draw();
    //std::cout << std::endl;
    //test3.draw();
    //std::cout << std::endl;
    //multi.draw();
    //std::cout << std::endl;
    //sum.draw();

     //Graph graph{ 500,500, 20, 20 };
     //graph.drawAxes();
     //graph.drawMatrix(test3, {100, 255, 0 });
     ////graph.drawVector(test1, {100,255,0});
     ////graph.drawVector(test2, {0,255,100});
     ////graph.drawVector(result, {100,0,100});
     ////result = test1 - test2;
     ////graph.drawVector(result, { 255,100,100 });

     //graph.show();

    while (true)
    {

    }
    return 0;
}