#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"

#include "Figure.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {

    Vector p1{ {0, 0} };
    Vector p2{ {50, 0}};
    Vector p3{{50, 50}};
    Vector p4{{0, 50}};

    Figure figure({ p1, p2, p3, p4 });
    figure.draw();

     Graph graph{ 500,500, 500, 500 };
     
     graph.drawAxes();
     graph.draw(figure, { 255,255,255 });

     graph.show();

    while (true)
    {

    }

    return 0;
}