#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Vector.h"

#undef main
#include <iostream>

int main(int argc, char* argv[]) {
    Vector test1 {{5,1,0}};
    Vector test2 {{-2,3,-1}};
    Vector result =  test1 + test2;
    //Vector result =  test1 - test2;

    Graph graph{ 500,500, 20, 20 };
    graph.startDrawing();

    graph.drawVector(test1, {100,255,0});
    graph.drawVector(test2, {0,255,100});
    graph.drawVector(result, {100,0,100});
    result = test1 - test2;
    graph.drawVector(result, { 255,100,100 });

    graph.show();

    while (true)
    {

    }
    return 0;
}