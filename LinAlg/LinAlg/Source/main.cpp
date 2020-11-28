#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"
#include "UnitaryMatrix.h"

#include "Figure.h"

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
    
    while (true)
    {

    }

    return 0;
}