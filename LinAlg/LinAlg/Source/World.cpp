#include "World.h"

#include <math.h>
#include <iostream>

World::World(unsigned int width, unsigned int height, unsigned int depth) : 
	_renderer{ width, height },
	_projectionMatrix{ width, height, 90, -0.1, -1000 },
	_camera{},
	view1{ {0,0,0} }, 
	view2{{0,0,0}},
	_ship{nullptr}
{
	_widthFactor	= width  / 2;
	_heightFactor	= height / 2;
	_depthFactor	= depth  / 2;
}

void World::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{

	Vector projected1 = _projectionMatrix * v1;
	Vector projected2 = _projectionMatrix * v2; 

	//projected1[0] += 1;
	//projected1[1] += 1;

	//projected2[0] += 1;
	//projected2[1] += 1;

	_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
	_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
}

void World::draw(const std::shared_ptr<Figure>& figure, const Color& color)
{
	for (const auto& triangle : figure->getTriangles())
	{
		std::vector<Vector> vectors;
		vectors.reserve(3);
		for (auto& vector : triangle.getVectors())
		{
			vectors.push_back(_projectionMatrix * vector);
		}
		if (!_projectionMatrix.correctMultiply())
		{
			continue;
		}
		_renderer.drawTriangle(Triangle{ vectors[0], vectors[1], vectors[2] }, color);
	}
}

void World::removeFigure(int index)
{
	_removeFigures.insert(index);
}

void World::removeBullet(int index)
{
	_removeBullets.insert(index);
}

void World::removeTarget(int index)
{
	_removeTargets.insert(index);
}

void World::removeShip()
{
	_hasShip = false;
	_ship.reset();
}

bool World::hasShip()
{
	return _hasShip;
}

void World::cleanup()
{
	int removed = 0;
	for (const auto& it : _removeTargets) {
		_targets.erase(_targets.begin() + it - removed++);
	}

	removed = 0;
	for (const auto& it : _removeBullets) {
		_bullets.erase(_bullets.begin() + it - removed++);
	}

	removed = 0;
	for (const auto& it : _removeFigures) {
		_figures.erase(_figures.begin() + it - removed++);
	}

	_removeBullets.clear();
	_removeFigures.clear();
	_removeTargets.clear();
}

void World::show()
{
	_renderer.show();
	_renderer.startDrawing();
}

Eye& World::getCamera()
{
	return _camera;
}

void World::addShip(std::vector<Triangle>& newFigure, std::vector<Triangle>& bullet){
	_hasShip = true;
	if(_ship == nullptr){
		std::vector<Triangle> _bullet = bullet;
		for (auto& triangle : newFigure) {
			triangle.translate(500, 500, 600);
		}

		_ship = std::make_shared<Ship>(newFigure, this, _bullet);
		std::shared_ptr<Figure> figure = _ship;
		_figures.push_back(figure);
	}
	else {
		std::cout << "Ship already added" << std::endl;
	}
}

void World::addTarget(std::vector<Triangle>& newFigure, Vector position, double velocity, int growthLimit, bool isGrowing){
	double pi = 3.14159265359;

	for (auto& triangle : newFigure) {
		triangle.yRotate(pi / 4 * -1);
		triangle.translate(position);
	}
	std::shared_ptr<Target> target = std::make_shared<Target>(newFigure, this, position, velocity, growthLimit, isGrowing);
	_targets.push_back(target);
	std::shared_ptr<Figure> figure = target;
	_figures.push_back(figure);
}

void World::addBullet(std::shared_ptr<Bullet> bullet){
	_bullets.push_back(bullet);
}


void World::addFigure(Figure newFigure)
{
	_figures.push_back(std::make_unique<Figure>(newFigure));
}

std::vector<std::shared_ptr<Figure>>& World::getFigures()
{
	return _figures;
}

std::shared_ptr<Ship>& World::getShip() 
{
	return _ship;
}

std::vector<std::shared_ptr<Bullet>>& World::getBullets() 
{
	return _bullets;
}

std::vector<std::shared_ptr<Target>>& World::getTargets()
{
	return _targets;
}

void World::tick(){
	if (_hasShip)
	{
		_ship->move();
	}
	
	for(auto& bullet : _bullets){
		bullet->move();
		bullet->tick();
	}

	for(auto& target : _targets){
		target->tick();
	}

	cleanup();
}