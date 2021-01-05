#pragma once
#include <Rendering/Renderer.h>
#include "ProjectionMatrix.h"
#include "Ship.h"
#include "Bullet.h"
#include "Vector.h"
#include "Figure.h"
#include "Target.h"
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
	void addShip(std::vector<Triangle>&, std::vector<Triangle>&);
	void addTarget(std::vector<Triangle>&, Vector, double, int, bool);
	void addBullet(std::shared_ptr<Bullet>);
	void tick();
	std::shared_ptr<Ship>& getShip();
	std::vector<std::shared_ptr<Bullet>>& getBullets();

	Vector view1;
	Vector view2;

private:
	std::vector<std::shared_ptr<Figure>> _figures;
	std::vector<std::shared_ptr<Bullet>> _bullets;
	std::vector<std::shared_ptr<Target>> _targets;
	std::shared_ptr<Ship> _ship;

	double _widthFactor, _heightFactor, _depthFactor;
	double _aspectRatio, _fieldOfView, _zNormalization;
	Renderer _renderer;
	ProjectionMatrix _projectionMatrix;
	Eye _camera;
};
