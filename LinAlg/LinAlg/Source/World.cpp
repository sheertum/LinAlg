#include "World.h"

#include <math.h>
#include <iostream>

World::World(unsigned int width, unsigned int height, unsigned int depth) :
	_renderer{ width, height},
	_projectionMatrix{ width, height, 90, -0.1, -1000 },
	_camera{ Vector{{0.01, -0.1, -0.1, 1}}, Vector{{0, 0, -0.001, 1}}, Limit{-0.1, 1000} },
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
	//std::array<Vector, 2> viewed{ _camera.getPerspective(v1, v2) };

	//Vector projected1 = viewed[0];//_projectionMatrix * viewed[0];
	//Vector projected2 = viewed[1];// _projectionMatrix * viewed[1];

	//_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
	//_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
	_renderer.drawLine(v1[0], v1[1], v2[0], v2[1], color);
}

void World::draw(const std::shared_ptr<Figure>& figure, const Color& color)
{
	for (const auto& triangle : figure->getTriangles())
	{
		//TODO: perspective
		std::vector<Vector> vectors;
		vectors.reserve(3);

		for (const auto& vector : triangle.getVectors()) {
			Vector copy{ vector };
			copy.pushBack(1);
			copy = _projectionMatrix * copy;

			//copy = copy * 100;
			//copy.translate(Vector{ {500,500,0} });
			//copy[2] /= 10;
			//copy.pushBack(1);
			//copy.translate(Vector{ {} });
			//copy = _projectionMatrix * (copy);
			//copy[0] += 1;
			//copy[1] += 1;
			//std::vector<Vector> result = _camera.toCameraPerspective(copy, Vector{ {1,1,1} });
			//result[0].translate(figure.getCenter());
			
			vectors.push_back(copy);
		}
		Triangle viewed{ vectors[0], vectors[1], vectors[2]};
		//_renderer.drawTriangle(triangle, Color{255,0,0});
		_renderer.drawTriangle(viewed, color);
	}
}

void World::show()
{
	_renderer.show();
	_renderer.startDrawing();
}

Camera& World::getCamera()
{
	return _camera;
}

void World::addShip(const std::vector<Triangle>& newFigure){
	if(_ship == nullptr){
		_ship = std::make_shared<Ship>(newFigure, this);
		std::shared_ptr<Figure> figure = _ship;
		_figures.push_back(figure);
	}
	else {
		std::cout << "Ship already added" << std::endl;
	}
}

void World::addTarget(Figure newFigure){
	_figures.push_back(std::make_shared<Figure>(newFigure));
}

void World::addBullet(Vector startPosition){
	//std::shared_ptr<Bullet> _bullet = std::make_shared<Bullet>(newFigure, this);
	std::shared_ptr<Figure> figure = _ship;
	_figures.push_back(figure);

	//_figures.push_back(std::make_shared<Figure>(newFigure));
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