#include "Rendering/Renderer.h"
#include "Graph/Graph.h"
#include <iostream>
#include <SDL.h>
#include "Matrix.h"
#include "UnitaryMatrix.h"
#include "CollisionHandler.h"
#include "Camera.h"

#include "Figure.h"
#include "Input.h"
#include "Triangle.h"
#include "Target.h"

#include "World.h"
#include "FigureLoader.h"

#include <time.h>

#undef main
#include <iostream>

int main() {
	std::shared_ptr<World> world = std::make_shared<World>( 1000,1000,1000 );
    Camera camera{ Vector{{0, 0, 0, 0}}, Vector{{1,1,1,1}}, {-10, 20} };

    Vector vA{ {-100,100,-100} };
    Vector vB{ {-100,-100,-100} };
    Vector vC{ {-100,-100,100} };
    Triangle triangle1{ vA, vB, vC };

    Vector vD{ {-100,100,100} };
    Triangle triangle2{ vA, vD, vC };

    Vector vE{ {100,100,-100} };
    Vector vF{ {100,-100,-100} };
    Vector vG{ {100,-100,100} };
    Triangle triangle3{ vE, vF, vG };

    Vector vH{ {100,100,100} };
    Triangle triangle4{ vE, vH, vG };

    Triangle triangle5{ vD, vC, vG };
    Triangle triangle6{ vD, vH, vG };
    Triangle triangle7{ vA, vB, vF };
    Triangle triangle8{ vA, vE, vF };

    std::vector<Triangle> triangles{{ triangle1, triangle2, triangle3, triangle4, triangle5, triangle6, triangle7, triangle8 }};

    for(auto& triangle : triangles){
        triangle.translate(500,500,0);
    }

    CollisionHandler collision{world};
    world->addShip(triangles);
    auto& ship = world->getShip();

    std::function<void()> moveBack = [&]() {
        ship->grow(1.1);
    };

    std::function<void()> moveForward = [&]() {
        ship->move();
    };

    std::function<void()> rotateY = [&]() {
        ship->yaw(5);
    };

    std::function<void()> rotateZ = [&]() {
        ship->roll(5);
    };

    std::function<void()> rotateX = [&]() {
        ship->pitch(5);
    };

    std::function<void()> grow = [&]() {
        ship->grow(1.2);
    };
    
    std::function<void()> shrink = [&]() {
        ship->shrink(1.2);
    };

    std::function<void()> accelerate = [&]() {
        ship->accelerate(1.1);
    };

    std::function<void()> decelerate = [&]() {
        ship->accelerate(0.9);
    };

    std::function<void()> print = [&]() {
        //std::cout << world->getCamera()._position[0] << "\t"
        //    << world->getCamera()._position[1] << "\t"
        //    << world->getCamera()._position[2] << "\t" << "\n";
        //std::cout << world->getCamera()._direction[0] << "\t"
        //    << world->getCamera()._direction[1] << "\t"
        //    << world->getCamera()._direction[2] << "\t" << "\n" << "\n";
    };

#define CAMERA_MOVEMENT 0.1

    std::function<void()> camRotX = [&]() {
        world->getCamera()._lookAt[0] += CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camRotY = [&]() {
        world->getCamera()._lookAt[1] += CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camRotZ = [&]() {
        world->getCamera()._lookAt[2] += CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camRotXN = [&]() {
        world->getCamera()._lookAt[0] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camRotYN = [&]() {
        world->getCamera()._lookAt[1] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camRotZN = [&]() {
        world->getCamera()._lookAt[2] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };


    std::function<void()> camXPos = [&]() {
        // world->getCamera()._position[0] += CAMERA_MOVEMENT;
        world->getCamera().update();
        //print();
    };

    std::function<void()> camXNeg = [&]() {
        // world->getCamera()._position[0] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camYPos = [&]() {
        // world->getCamera()._position[1] += CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camYNeg = [&]() {
        // world->getCamera()._position[1] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };


    std::function<void()> camZPos = [&]() {
        // world->getCamera()._position[2] += CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> camZNeg = [&]() {
        // world->getCamera()._position[2] -= CAMERA_MOVEMENT;
        world->getCamera().update();
        print();
    };

    std::function<void()> quit = [&]() {
        SDL_Quit();
    };

    Input input;
    input.addBinding(SDLK_b, accelerate);
    input.addBinding(SDLK_v, decelerate);

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
    input.addBinding(SDLK_KP_PLUS, grow);
    input.addBinding(SDLK_KP_MINUS, shrink);

	while (true)
	{
		input.pollEvents();
        input.handleEvents();

        collision.checkForCollisions();
        
        world->draw(ship, { 255,255,0 });
        world->tick();

        world->drawLine(Vector{ {0,0,0} }, ship->getCenter(), { 0,255,255 });
        world->drawLine(ship->getCenter(), ship->getXAxis(), { 0,0,255 });
        world->drawLine(ship->getCenter(), ship->getZAxis(), { 0,255,0 });
        world->drawLine(ship->getCenter(), ship->getYAxis(), { 255,0,0 });
        
        //world->drawLine(ship->getCenter(), ship->getSphereRadius(), { 255,0,0 });

		world->show();
	}

	SDL_Quit();

	return 0;
}
