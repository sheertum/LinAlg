#pragma once
#include <Rendering/Renderer.h>
#include "ProjectionMatrix.h"
#include "Ship.h"
#include "Bullet.h"
#include "Vector.h"
#include "Figure.h"
#include "Camera.h"

class World {
public:
	World(unsigned int width, unsigned int height, unsigned int depth);

	void drawLine(const Vector&, const Vector&, const Color&);
	void draw(const std::shared_ptr<Figure>&, const Color&);

	void show();

	Camera& getCamera();

	std::vector<std::shared_ptr<Figure>>& getFigures();
	void addFigure(Figure);
	void addShip(const std::vector<Triangle>& triangles);
	void addTarget(Figure);
	void addBullet(Vector);
	std::shared_ptr<Ship>& getShip();

	Vector view1;
	Vector view2;

private:
	std::vector<std::shared_ptr<Figure>> _figures;
	std::shared_ptr<Ship> _ship;

	double _widthFactor, _heightFactor, _depthFactor;
	double _aspectRatio, _fieldOfView, _zNormalization;
	Renderer _renderer;
	ProjectionMatrix _projectionMatrix;
	Camera _camera;
};
