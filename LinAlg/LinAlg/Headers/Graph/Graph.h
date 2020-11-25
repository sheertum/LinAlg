#pragma once
#include "Rendering/Renderer.h"
#include <unordered_map>
#include "Vector.h"
#include "Figure.h"

class SDL_Texture;

class Graph {
public:
	Graph(unsigned int width, unsigned int height, unsigned int xCount, unsigned int yCount);

	void show();
	void drawAxes();
	void drawLine(int x1, int y1, int x2, int y2, const Color&);

	void drawLine(const Vector&, const Vector&, const Color&);
	void drawLine(const std::vector<int>&, const std::vector<int>&, const Color&);
	void drawLine(const Vector&, const Color&);

	void draw(const Figure&, const Color&, bool loopBack = true);

private:
	Renderer _renderer;
	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> _base;
	unsigned int _width;
	unsigned int _height;
	unsigned int _xLineDistance;
	unsigned int _yLineDistance;
};