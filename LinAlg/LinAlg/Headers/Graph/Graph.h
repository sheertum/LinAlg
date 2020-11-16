#pragma once
#include "Rendering/Renderer.h"
#include <unordered_map>
#include "Vector.h"

class SDL_Texture;

class Graph {
public:
	Graph(unsigned int width, unsigned int height, unsigned int xCount, unsigned int yCount);

	void show();
	void startDrawing();
	void drawLine(int x1, int y1, int x2, int y2, const Color&);
	void drawVector(const Vector&, const Color& color);

private:
	Renderer _renderer;
	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> _base;
	unsigned int _width;
	unsigned int _height;
	unsigned int _xLineDistance;
	unsigned int _yLineDistance;
};