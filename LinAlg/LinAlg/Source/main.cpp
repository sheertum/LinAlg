#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"
#include "UnitaryMatrix.h"

#include "Figure.h"
#include "Input.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {

    Vector p1{ {0, 0} };
    Vector p2{ {63, 0}};
    Vector p3{{63, 63}};
    Vector p4{{0, 63}};

    Figure figure({ p1, p2, p3, p4 });
    figure.draw();
    figure.translate(-31.5, -31.5, 1);
    //figure.rotate(35);
    figure.scale(0.5);
    figure.translate(31.5, 31.5, 1);

     Graph graph{ 500,500, 500, 500 };
     graph.draw(figure, { 255,255,255 });

     graph.show();
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
    
    std::function<void()> rotate = [&]() {
        figure.rotate(5);
    };

    std::function<void()> scaleUp = [&]() {
        figure.scaleFromOrigin(1.2, 1.2, 1.2);
    };

    std::function<void()> scaleDown = [&]() {
        figure.scaleFromOrigin(0.8, 0.8, 0.8);
    };

    Input input;
    input.addBinding(SDLK_r, rotate);
    input.addBinding(SDLK_p, scaleUp);
    input.addBinding(SDLK_m, scaleDown);
    // left(0, 0) = 1
    
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
        input.pollEvents();
        input.handleEvents();

        graph.drawAxes();
        graph.draw(figure, { 255,255,255 });

        graph.show();
    }
        SDL_Quit();

    return 0;
}