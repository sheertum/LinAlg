#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {
    std::vector<int> first { 1,2,3};
    std::vector<int> second { 4,5,6};
    
    std::vector<int> first3d { 1,4};
    std::vector<int> second3d { 2,5};
    std::vector<int> third3d { 5, -3};


    Matrix test1 {2, 3, {first, second}};
    Matrix test2 {2, 3, {first, second}};
    Matrix test3 {3, 2, {first3d, second3d, third3d}};

    Matrix sum = test1 + test2;
    Matrix multi = test1 * test3;

    //test1.draw();
    //std::cout << std::endl;
    //test3.draw();
    //std::cout << std::endl;
    //multi.draw();
    //std::cout << std::endl;
    //sum.draw();

     Graph graph{ 500,500, 20, 20 };
     graph.drawAxes();
     graph.drawMatrix(test3, {100, 255, 0 });
     //graph.drawVector(test1, {100,255,0});
     //graph.drawVector(test2, {0,255,100});
     //graph.drawVector(result, {100,0,100});
     //result = test1 - test2;
     //graph.drawVector(result, { 255,100,100 });

     graph.show();

    while (true)
    {

    }
    return 0;
}