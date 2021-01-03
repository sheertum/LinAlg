#include "World.h"

#include <math.h>
#include <iostream>

World::World(unsigned int width, unsigned int height, unsigned int depth) : 
	_renderer{ width, height },
	_projectionMatrix{ width, height, 10, -0.1, -1000 },
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
	Vector newV1 = v1 - 500;
	newV1[2] = 0;
	Vector newV2 = v2 - 500;
	newV2[2] = 0;

	std::array<Vector, 2> viewed{ _camera.getPerspective(newV1, newV2) };

	Vector projected1 = v1 /*viewed[0] + 500*/;//_projectionMatrix * viewed[0];
	Vector projected2 = v2 /*viewed[1] + 500*/;// _projectionMatrix * viewed[1];

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
		//TODO: perspective
		_renderer.drawTriangle(triangle, color);
	}
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

void World::addShip(std::vector<Triangle>& newFigure){
	if(_ship == nullptr){
		_ship = std::make_shared<Ship>(newFigure, this);
		std::shared_ptr<Figure> figure = _ship;
		_figures.push_back(figure);
	}
	else {
		std::cout << "Ship already added" << std::endl;
	}
}

void World::addTarget(std::vector<Triangle>& newFigure, Vector position, double velocity, int growthLimit, bool isGrowing = true){
	//std::shared_ptr<Target> target = std::make_shared<Target>(newFigure, this, position, velocity);
	//_targets.push_back(target);
	//std::shared_ptr<Figure> figure = target;
	//_figures.push_back(figure);
}

void World::addBullet(std::vector<Triangle>& newFigure, Vector startPosition, Matrix axis, double velocity){
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(newFigure, this, startPosition, axis, velocity);
	_bullets.push_back(bullet);
	std::shared_ptr<Figure> figure = bullet;
	_figures.push_back(figure);
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

void World::tick(){
	_ship->move();
	for(auto& bullet : _bullets){
		bullet->move();
	}

	for(auto& target : _targets){
		target->tick();
	}
}