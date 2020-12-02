#include "World.h"
#include <math.h>

World::World(unsigned int width, unsigned int height, unsigned int depth) : _renderer{ width, height }, _projectionMatrix{ width, height, 90, 0.1, 1000 }
{
	_widthFactor	= width  / 2;
	_heightFactor	= height / 2;
	_depthFactor	= depth  / 2;
}

void World::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{
	Vector realV1 = _projectionMatrix*v1;
	Vector realV2 = _projectionMatrix*v2;

	realV1[0] += 1;
	realV1[1] += 1;
	realV1[0] *= _widthFactor;
	realV1[1] *= _heightFactor;

	realV2[0] += 1;
	realV2[1] += 1;
	realV2[0] *= _widthFactor;
	realV2[1] *= _heightFactor;

	_renderer.drawLine(realV1[0], realV1[1], realV2[0], realV2[1], color);
}

void World::show()
{
	_renderer.show();
}

