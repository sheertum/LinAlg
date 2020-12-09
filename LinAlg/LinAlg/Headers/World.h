#pragma once
#include <Rendering/Renderer.h>
#include "ProjectionMatrix.h"
#include "Vector.h"
#include "Figure.h"

class World {
public:
	World(unsigned int width, unsigned int height, unsigned int depth);

	void drawLine(const Vector&, const Vector&, const Color&);
	void draw(const Figure&, const Color&, bool loopBack = true);

	void show();

private:
	double _widthFactor, _heightFactor, _depthFactor;
	double _aspectRatio, _fieldOfView, _zNormalization;
	Renderer _renderer;
	ProjectionMatrix _projectionMatrix;
};