#include "World.h"
#include <math.h>
#include <iostream>

World::World(unsigned int width, unsigned int height, unsigned int depth, double start, double end) :
	_renderer{ width, height, start, end },
	_projectionMatrix{ width, height, 10, -0.1, -1000 },
	_camera{},
	view1{ {0,0,0} }, 
	view2{{0,0,0}}
{
	_widthFactor	= width  / 2;
	_heightFactor	= height / 2;
	_depthFactor	= depth  / 2;
}

void World::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{
	std::array<Vector, 2> viewed{ _camera.getPerspective(v1, v2) };

	Vector projected1 = viewed[0];//_projectionMatrix * viewed[0];
	Vector projected2 = viewed[1];// _projectionMatrix * viewed[1];

	_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
	_renderer.drawLine(projected1[0], projected1[1], projected2[0], projected2[1], color);
}

void World::draw(const Figure& figure, const Color& color)
{
	for (const auto& triangle : figure.getTriangles())
	{
		//TODO: perspective
		std::vector<Vector> vectors;
		vectors.reserve(3);

		for (const auto& vector : triangle.getVectors()) {
			Vector copy{ vector };
			copy.pushBack(1);
			//copy = _projectionMatrix * copy;
			vectors.push_back((_camera._view * copy).toVector());
		}
		Triangle viewed{ vectors[0], vectors[1], vectors[2] };
		_renderer.drawTriangle(viewed, color);
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

void World::addFigure(Figure newFigure)
{
	_figures.push_back(newFigure);
}

std::vector<Figure> World::getFigures()
{
	return _figures;
}

