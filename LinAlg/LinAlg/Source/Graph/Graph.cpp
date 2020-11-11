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

void Graph::startDrawing()
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
