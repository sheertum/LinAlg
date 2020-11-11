#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Vector.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {
    Vector test1 {{1,2,0}};
    Vector test2 {{2,3,-1}};
    Vector result =  test1 + test2;
    Vector result =  test1 - test2;

    Graph graph{ 500,500, 10, 10 };
    graph.startDrawing();
    graph.drawLine(-5, -1, 2, -2, {0,255,0});
    graph.show();

    while (true)
    {

    }
    return 0;
}