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
#include "ShipControls.hpp"

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

    std::vector<Triangle> bulletFigure{{ triangle1, triangle2, triangle3, triangle4, triangle5, triangle6, triangle7, triangle8 }};

    std::vector<Triangle> shipFigure = FigureLoader::load("Resources\\SpaceShip.obj", 1000, 0, 0.5);
    std::vector<Triangle> targetFigure = FigureLoader::load("Resources\\target.obj", 1000, 0, 0.5);

    CollisionHandler collision{world};
    world->addShip(shipFigure, bulletFigure);
    world->addTarget(targetFigure, Vector{ {500,-200, 500} }, 1.5, 0);
    auto& ship = world->getShip();


    ShipControls controls{ world->getShip() };

	while (true)
	{
        if (world->hasShip())
        {
            Input& input = controls.getInput();
            input.pollEvents();
            input.handleEvents();
        }

        collision.checkForCollisions();
        
        world->tick();
        if (world->hasShip())
        {
            world->draw(ship, { 255,255,0 });
            world->drawLine(ship->getCenter(), ship->getBigXAxis(), { 0,0,255 });
            world->drawLine(ship->getCenter(), ship->getBigZAxis(), { 0,255,0 });
            world->drawLine(ship->getCenter(), ship->getBigYAxis(), { 255,0,0 });
        }

        for(auto& bullet : world->getBullets())
        {
            //world->drawLine(Vector{ {0,0,0} }, bullet->getCenter(), { 255,255,255 });
            world->draw(bullet, { 255,255,255 });
            world->drawLine(bullet->getCenter(), bullet->getBigXAxis(), { 0,0,255 });
            world->drawLine(bullet->getCenter(), bullet->getBigZAxis(), { 0,255,0 });
            world->drawLine(bullet->getCenter(), bullet->getBigYAxis(), { 255,0,0 }); 
        }

        for (const auto& target : world->getTargets()) {
            world->draw(target, Color{ 255,255,255 });
        }

		world->show();
	}

	SDL_Quit();

	return 0;
}
