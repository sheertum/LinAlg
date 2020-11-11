#include <SDL.h>
#include "Vector.h"
#undef main
#include <iostream>

int main(int argc, char* argv[]) {
    Vector test1 {{1,2,0}};
    Vector test2 {{2,3,-1}};
    Vector result =  test1 + test2;
    result.print();

    Vector minResult = test1 - test2;
    minResult.print();
    return 0;
}