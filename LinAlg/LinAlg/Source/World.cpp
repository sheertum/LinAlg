#include "World.h"
#include <math.h>

World::World(unsigned int width, unsigned int height, unsigned int depth) : _renderer{ width, height }, _projectionMatrix{ width, height, 90, -0.1, -1000 }, _camera{ Vector{{0.01, -0.1, -0.1, 1}}, Vector{{0, 0, -0.001, 1}}, Limit{-0.1, 1000} }
{
	_widthFactor	= width  / 2;
	_heightFactor	= height / 2;
	_depthFactor	= depth  / 2;
}

void World::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{
	Vector projected1 = _projectionMatrix * v1;
	Vector projected2 = _projectionMatrix * v2;

	projected1[0] += 1;
	projected1[1] += 1;
	//realV1[0] *= _widthFactor;
//realV1[1] *= _heightFactor;

	projected2[0] += 1;
	projected2[1] += 1;
	//realV2[0] *= _widthFactor;
//realV2[1] *= _heightFactor;

	std::vector<Vector> result = _camera.toCameraPerspective(projected1, projected2);

	_renderer.drawLine(result[0][0], result[0][1], result[1][0], result[1][1], color);
}

void World::draw(const Figure& figure, const Color& color, bool loopBack)
{
	for (const auto& shape : figure.getShapes())
	{
		int previousIndex = -1;
		int firstIndex = -1;
		for (int index : shape._indices)
		{
			if (previousIndex >= 0) {
				drawLine(figure.getVector(previousIndex), figure.getVector(index), color);
			}
			else {
				firstIndex = index;
			}
			previousIndex = index;
		}
		drawLine(figure.getVector(firstIndex), figure.getVector(previousIndex), color);
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

