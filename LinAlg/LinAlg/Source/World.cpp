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

void World::draw(const Figure& figure, const Color& color)
{
	for (const auto& triangle : figure.getTriangles())
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

