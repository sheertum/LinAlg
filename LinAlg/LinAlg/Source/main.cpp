#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>

#undef main


int main(int argc, char* argv[]) {

    Graph graph{ 500,500, 10, 10 };
    graph.startDrawing();
    graph.drawLine(-5, -1, 2, -2, {0,255,0});
    graph.show();

    while (true)
    {

    }
    return 0;
}