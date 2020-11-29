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

    Vector p1{ {-50, -50, -50} };
    Vector p2{ {50, -50, -50} };
    Vector p3{ {50, 50, -50} };
    Vector p4{ {-50, 50, -50} };

    Vector p5{ {-50, -50, 0} };
    Vector p6{ {50, -50, 0} };
    Vector p7{ {50, 50, 0} };
    Vector p8{ {-50, 50, 0} };

    //Figure figure({ p1, p2, p3, p4 });//, p5, p6, p7, p8 });
    Figure figure({ p5, p6, p7, p8 });

    figure.translate(-31.5, -31.5, 1);
    figure.calculateCenter();
    //figure.translate(31.5, 31.5, 1);

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
    matrix.zRotate(90);
    matrix.draw();
    
    std::function<void()> rotate = [&]() {
        figure.moveToOrigin();
        figure.yRotate(5);
        figure.moveBack();

        figure.moveToOrigin();
        figure.zRotate(5);
        figure.moveBack();
        
        figure.moveToOrigin();
        figure.xRotate(5);
        figure.moveBack();
        
    };

    std::function<void()> scaleUp = [&]() {
        //figure.scaleFromOrigin(1.2, 1.2, 1.2);
        figure.moveToOrigin();
        figure.scale(1.2, 1.2, 1.2);
        figure.moveBack();
    };

    std::function<void()> scaleDown = [&]() {
        figure.moveToOrigin();
        figure.scale(0.8, 0.8, 0.8);
        figure.moveBack();
    };

    Input input;
    input.addBinding(SDLK_r, rotate);
    input.addBinding(SDLK_p, scaleUp);
    input.addBinding(SDLK_m, scaleDown);
   
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