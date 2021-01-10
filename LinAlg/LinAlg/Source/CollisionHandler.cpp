#include "CollisionHandler.h"
#include <iostream>
#include <typeinfo>
#include "Ship.h"
#include "Bullet.h"

CollisionHandler::CollisionHandler(std::shared_ptr<World> world) : _world(world)
{

}

bool CollisionHandler::checkAABBCollisions(std::shared_ptr<Figure>& figA, std::shared_ptr<Figure>& figB)
{
	BoundingSphere boundingA = figA->getBoundingSphere();
	BoundingSphere boundingB = figB->getBoundingSphere();
	double touchingLength = boundingA.getRadius() + boundingB.getRadius();

	Vector difference = boundingA.getCenter() - boundingB.getCenter();

	if (difference.length() > touchingLength) {
		return false;
	}
	return true;
}

void CollisionHandler::checkForCollisions()
{
	auto& figures = _world->getFigures();
	std::vector<CollisionEvent> collisions;

	for (int i = 0; i < figures.size(); i++) {
		for(int j = i+1; j < figures.size(); j++){
			if (checkAABBCollisions(figures[i], figures[j])) {
				collisions.push_back(CollisionEvent(figures[i], figures[j]));
			}
		}
	}
	collideFigures(collisions);
}

void CollisionHandler::collideFigures(std::vector<CollisionEvent>& collisions)
{
	for (auto& collision : collisions) {
		bool ship = (dynamic_cast<Ship*>(collision.figA.get())) || (dynamic_cast<Ship*>(collision.figB.get()));
		bool bullet = (dynamic_cast<Bullet*>(collision.figA.get())) || (dynamic_cast<Bullet*>(collision.figB.get()));
		if (!(ship && bullet))
		{
			collision.figA->collide();
			collision.figB->collide();
		}
	}
}
