#include "CollisionHandler.h"
#include "CollisionEvent.h"

CollisionHandler::CollisionHandler(World& world) : _world(world)
{

}

bool CollisionHandler::checkAABBCollisions(Figure& figA, Figure& figB)
{
	BoundingSphere boundingA = figA.getBoundingSphere();
	BoundingSphere boundingB = figB.getBoundingSphere();
	double touchingLength = boundingA.getRadius() + boundingB.getRadius();

	Vector difference = boundingA.getCenter() - boundingB.getCenter();

	if (difference.length() > touchingLength) {
		return false;
	}
	return true;
}

void CollisionHandler::checkForCollisions()
{
	auto figures = _world.getFigures();
	std::vector<CollisionEvent> collisions;

	for (int i = 0; i < figures.size(); i++) {
		for(int j = i+1; j < figures.size(); j++){
			if (checkAABBCollisions(figures[i], figures[j])) {
				collisions.push_back(CollisionEvent(figures[i], figures[j]));
			}
		}
	}
	//TODO: pixel perfect collision
	for (auto& collision : collisions) {
		collision.figA.collide();
		collision.figB.collide();
	}
}

void CollisionHandler::collideFigures()
{
}
