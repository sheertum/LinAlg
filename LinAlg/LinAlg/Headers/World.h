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
	void draw(const std::shared_ptr<Figure>&, const Color&);

	void show();

	Eye& getCamera();

	std::vector<std::shared_ptr<Figure>>& getFigures();
	void addFigure(Figure);
	void addShip(Figure);
	void addTarget(Figure);
	void addBullet(Figure);
	std::shared_ptr<Figure>& getShip();

	Vector view1;
	Vector view2;

private:
	std::vector<std::shared_ptr<Figure>> _figures;
	std::shared_ptr<Figure> _ship;

	double _widthFactor, _heightFactor, _depthFactor;
	double _aspectRatio, _fieldOfView, _zNormalization;
	Renderer _renderer;
	ProjectionMatrix _projectionMatrix;
	Eye _camera;
};
