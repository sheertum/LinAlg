#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"
#include "UnitaryMatrix.h"
#include "Camera.h"

#include "Figure.h"
#include "Input.h"
#include "Triangle.h"

#include "World.h"

#undef main
#include <iostream>

int main() {
	World world{ 1000,1000,1000 };
	
	Vector p1{ {-0.5, -0.5,  -4.5 } };
    Vector p2{ { 0.5, -0.5,  -4.5 } };
    Vector p3{ { 0.5,  0.5,  -4.5 } };
    Vector p4{ {-0.5,  0.5,  -4.5 } };

    Vector p5{ {-0.5, -0.5, -5 } };
    Vector p6{ { 0.5, -0.5, -5 } };
    Vector p7{ { 0.5,  0.5, -5 } };
    Vector p8{ {-0.5,  0.5, -5 } };

	Figure figure({ p1, p2, p3, p4, p5, p6, p7, p8 });

    Camera camera{ Vector{{0, 0, 0, 0}}, Vector{{1,1,1,1}}, {-10, 20} };

    //Vector p9{ {-0.5, -0.5,  -4.5 } };
    //Vector p10{ { 0.5, -0.5,  -4.5 } };
    //Vector p11{ { 0.5,  0.5,  -4.5 } };
    //Vector p12{ {-0.5,  0.5,  -4.5 } };

    //Vector p13{ {-0.5, -0.5, -5 } };
    //Vector p6{ { 0.5, -0.5, -5 } };
    //Vector p7{ { 0.5,  0.5, -5 } };
    //Vector p8{ {-0.5,  0.5, -5 } };

    //Figure figure({ p1, p2, p3, p4, p5, p6, p7, p8 });
    //figure.createShape({ 0, 1, 2, 3 });
    //figure.createShape({ 4, 5, 6, 7 });
    //figure.createShape({ 0, 4 });
    //figure.createShape({ 1, 5 });
    //figure.createShape({ 2, 6 });
    //figure.createShape({ 3, 7 });

    std::function<void()> moveBack = [&]() {
        figure.translate(-.01, -0.01, -0.01);
        figure.calculateCenter();
    };

    std::function<void()> moveForward = [&]() {
        figure.translate(0, 0, 0.01);
        figure.calculateCenter();
    };

    std::function<void()> rotateY = [&]() {
        figure.moveToOrigin();
        figure.yRotate(5);
        figure.moveBack();
    };

    std::function<void()> rotateZ = [&]() {
        figure.moveToOrigin();
        figure.zRotate(5);
        figure.moveBack();
    };

    std::function<void()> rotateX = [&]() {
        figure.moveToOrigin();
        figure.xRotate(5);
        figure.moveBack();
    };

    std::function<void()> print = [&]() {
        //std::cout << world.getCamera()._position[0] << "\t"
        //    << world.getCamera()._position[1] << "\t"
        //    << world.getCamera()._position[2] << "\t" << "\n";
        //std::cout << world.getCamera()._direction[0] << "\t"
        //    << world.getCamera()._direction[1] << "\t"
        //    << world.getCamera()._direction[2] << "\t" << "\n" << "\n";
    };

#define CAMERA_MOVEMENT 0.2

    std::function<void()> camRotX = [&]() {
        // world.getCamera()._direction[0] += CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camRotY = [&]() {
        // world.getCamera()._direction[1] += CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camRotZ = [&]() {
        // world.getCamera()._direction[2] += CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camRotXN = [&]() {
        // world.getCamera()._direction[0] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camRotYN = [&]() {
        // world.getCamera()._direction[1] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camRotZN = [&]() {
        // world.getCamera()._direction[2] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };


    std::function<void()> camXPos = [&]() {
        // world.getCamera()._position[0] += CAMERA_MOVEMENT;
        world.getCamera().update();
        //print();
    };

    std::function<void()> camXNeg = [&]() {
        // world.getCamera()._position[0] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camYPos = [&]() {
        // world.getCamera()._position[1] += CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camYNeg = [&]() {
        // world.getCamera()._position[1] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };


    std::function<void()> camZPos = [&]() {
        // world.getCamera()._position[2] += CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> camZNeg = [&]() {
        // world.getCamera()._position[2] -= CAMERA_MOVEMENT;
        world.getCamera().update();
        print();
    };

    std::function<void()> quit = [&]() {
        SDL_Quit();
    };

    Input input;
    input.addBinding(SDLK_b, moveBack);
    input.addBinding(SDLK_v, moveForward);

    input.addBinding(SDLK_y, rotateY);
    input.addBinding(SDLK_x, rotateX);
    input.addBinding(SDLK_z, rotateZ);

    input.addBinding(SDLK_F1, camRotX);
    input.addBinding(SDLK_F2, camRotY);
    input.addBinding(SDLK_F3, camRotZ);
    input.addBinding(SDLK_F5, camRotXN);
    input.addBinding(SDLK_F6, camRotYN);
    input.addBinding(SDLK_F7, camRotZN);

    input.addBinding(SDLK_1, camXPos);
    input.addBinding(SDLK_2, camXNeg);

    input.addBinding(SDLK_3, camYPos);
    input.addBinding(SDLK_4, camYNeg);

    input.addBinding(SDLK_5, camZPos);
    input.addBinding(SDLK_6, camZNeg);

    input.addBinding(SDLK_p, print);

	while (true)
	{
		input.pollEvents();
        input.handleEvents();
		world.draw(figure, { 255,255,255 });
		world.show();
	}

	SDL_Quit();

	return 0;
}
