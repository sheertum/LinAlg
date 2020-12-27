#include "Graph/Graph.h"
#include <math.h>
#include <iostream>

Graph::Graph(unsigned int width, unsigned int height, unsigned int xCount, unsigned int yCount) :
	_renderer(width, height), _base{ nullptr,nullptr}, _width{width}, _height{height}
{
	_xLineDistance = (xCount > 0) ? width / xCount : 0;
	_yLineDistance = (yCount > 0) ? height / yCount : 0;

	_renderer.createCanvasTexture(width, height);

	for (size_t x = 0; x < width; x += _xLineDistance)
	{
		_renderer.drawLine(x, 0, x, height, {0,0,255});
	}

	for (size_t y = 0; y < width; y += _yLineDistance)
	{
		_renderer.drawLine(0, y, width, y, { 0,0,255 });
	}

	_renderer.drawLine(width / 2, 0, width / 2, height, { 255,0,0 });
	_renderer.drawLine(0, height/2, width, height/2, { 255,0,0 });

	_base = std::move(_renderer.getCanvasTexture());
}

void Graph::show()
{
	_renderer.show();
}

void Graph::drawAxes()
{
	_renderer.draw(*_base.get());
}

void Graph::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{

	int realx1 = _width / 2 + (x1 * this->_xLineDistance);
	int realy1 = _height / 2 - (y1 * this->_yLineDistance);

	int realx2 = _width / 2 + (x2 * this->_xLineDistance);
	int realy2 = _height / 2 - (y2 * this->_yLineDistance);

	_renderer.drawLine(realx1, realy1, realx2, realy2, color);
	//_renderer.drawline(realx1, realy1, realx2, realy2, color);
	//_renderer.drawLine(x1, y1, x2, y2, color);
}

void Graph::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{
	Vector perspectiveVector1 = applyPerspective(v1);
	Vector perspectiveVector2 = applyPerspective(v2);

	if (perspectiveVector1[3] > 0 || perspectiveVector2[3] > 0)
	{
		drawLine(perspectiveVector1[0], perspectiveVector1[1], perspectiveVector2[0], perspectiveVector2[1], color);
	}
	
}

void Graph::drawLine(const Matrix& m1, const Matrix& m2, const Color& color)
{
	drawLine(Vector{ {m1(0,0),m1(0,1)} }, Vector{ {m2(0,0),m2(0,1)} }, color);
}

void Graph::drawLine(const std::vector<double>& v1, const std::vector<double>& v2, const Color& color)
{
	Vector vector1{ v1 };
	Vector vector2{ v2 };
	drawLine(vector1, vector2, color);
}

void Graph::drawLine(const Vector& vector, const Color& color)
{
	drawLine(0, 0, vector[0], vector[1], color);
}

void Graph::draw(const Figure& figure, const Color& color, bool loopBack)
{
	for (const auto& shape : figure.getTriangles())
	{
		auto vectors = shape.getVectors();
		for(int i = 0; i < 2; i++){
			drawLine(vectors[i], vectors[i+1], color);
		}
		drawLine(vectors[0], vectors[vectors.size()-1], color);
	}
}

Vector Graph::applyPerspective(const Vector& v)
{
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
	Matrix P{ 4,4 }; //Projection matrix
	Matrix V{ 1, 4 };
	Matrix result{ 1, 3 };

	double near = 0;
	double far = -200;
	double fovy = 3.14159265358979323846 / 2;
	double scale = near * std::tan(fovy * 0.5);

	P(0, 0) = 1;
	P(1, 1) = 1;
	P(2, 2) = -far / (far - near);
	P(3, 2) = -1;
	P(2, 3) = (-far * near) / (far - near);
	//P.draw();

	V(0, 0) = v[0];
	V(0, 1) = v[1];
	V(0, 2) = v[2];
	V(0, 3) = 1;

	result = P * V;

	double x = result(0, 0);
	double y = result(0, 1);
	double w = result(0, 3);

	result(0, 0) = x / w;// (SCREEN_WIDTH / 2) + (x / w) * (SCREEN_WIDTH / w);
	result(0, 1) = y / w;// (SCREEN_HEIGHT / 2) + (y / w) * (SCREEN_HEIGHT / w);

	//std::cout << std::endl;
	//result.draw();
	//std::cout << std::endl;

	return Vector{ result.getData() };
}

//Vector Graph::applyPerspective(const Vector& v)
//{
//#define SCREEN_WIDTH 500
//#define SCREEN_HEIGHT 500
//	Matrix P{ 4,4 }; //Projection matrix
//	Matrix V{ 1, 4 };
//	Matrix result{ 1, 3 };
//
//	double near = 0;
//	double far = -200;
//	double fovy = 3.14159265358979323846 / 2;
//	double scale = near * std::tan(fovy * 0.5);
//
//	P(0, 0) = 1;
//	P(1, 1) = 1;
//	P(2, 2) = -far / (far - near);
//	P(3, 2) = -1;
//	P(2, 3) = (-far * near) / (far - near);
//	//P.draw();
//
//	V(0, 0) = v[0];
//	V(0, 1) = v[1];
//	V(0, 2) = v[2];
//	V(0, 3) = 1;
//
//	result = P * V;
//
//	double x = result(0, 0);
//	double y = result(0, 1);
//	double w = result(0, 3);
//
//	result(0, 0) = x / w;// (SCREEN_WIDTH / 2) + (x / w) * (SCREEN_WIDTH / w);
//	result(0, 1) = y / w;// (SCREEN_HEIGHT / 2) + (y / w) * (SCREEN_HEIGHT / w);
//
//	//std::cout << std::endl;
//	//result.draw();
//	//std::cout << std::endl;
//
//	return Vector{ result.getData() };
//}
