#pragma once
#include <Rendering/Renderer.h>
#include "ProjectionMatrix.h"
#include "Vector.h"
#include "Figure.h"
#include "newCamera.h"

class World {
public:
	World(unsigned int width, unsigned int height, unsigned int depth);

	void drawLine(const Vector&, const Vector&, const Color&);
	void draw(const std::unique_ptr<Figure>&, const Color&);

	void show();

	Eye& getCamera();

	std::vector<std::unique_ptr<Figure>>& getFigures();
	void addFigure(Figure);
	void addShip();
	void addTarget();
	void addBullet();
	Vector view1;
	Vector view2;

private:
	std::vector<std::unique_ptr<Figure>> _figures;
	double _widthFactor, _heightFactor, _depthFactor;
	double _aspectRatio, _fieldOfView, _zNormalization;
	Renderer _renderer;
	ProjectionMatrix _projectionMatrix;
	Eye _camera;
};
