#include "Graph/Graph.h"

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
	int realX1 = _width / 2 + (x1 * _xLineDistance);
	int realY1 = _height / 2 - (y1 * _yLineDistance);

	int realX2 = _width / 2 + (x2 * _xLineDistance);
	int realY2 = _height / 2 - (y2 * _yLineDistance);

	_renderer.drawLine(realX1, realY1, realX2, realY2, color);
}

void Graph::drawLine(const Vector& v1, const Vector& v2, const Color& color)
{
	drawLine(v1[0], v1[1], v2[0], v2[1], color);
}

void Graph::drawLine(const std::vector<int>& v1, const std::vector<int>& v2, const Color& color)
{
	Vector vector1{ v1 };
	Vector vector2{ v2 };
	drawLine(vector1, vector2, color);
}

void Graph::drawLine(const Vector& vector, const Color& color)
{
	drawLine(0, 0, vector[0], vector[1], color);
}

void Graph::drawMatrix(const Matrix& matrix, const Color& color, bool loopBack)
{
	if (matrix.getDimensions()[0] < 2)
	{
		throw "To draw a matrix you need atleast 2 vectors";
	}

	int i;
	for (i = 1; i < matrix.getDimensions()[0]; i++)
	{
		drawLine(matrix[i - 1], matrix[i], color);
	}

	if (loopBack)
	{
		drawLine(matrix[i - 1], matrix[0], color);
	}
}