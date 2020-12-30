#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Triangle.h"

#include <memory>
#include <map>
#include <array>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Color {
public:
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255):
		r{red}, g{green}, b{blue}, a{alpha}{}
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

class Renderer {
private:
	using Texture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>;
public:
	Renderer(unsigned int width, unsigned int height, double start, double end);

	void drawLine(int x1, int y1, int x2, int y2, const Color&);
	void drawTriangle(const Triangle& triangle, const Color& color);
	void draw(SDL_Texture&);

	void show();
	void startDrawing();

	void createCanvasTexture(unsigned int width, unsigned int height);
	std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>& getCanvasTexture();

private:
	uint32_t convertRGBtoHex(const Color&);
	Texture createTexture(unsigned int width, unsigned int height) const;
	std::array<int, 2> toSDLPosition(const Vector&) const;

private:
	std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> _window;
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _renderer;
	Texture _buffer;
	std::map<double, std::vector<Texture>> _textures;
	double _start, _end;
	unsigned int _width, _height;
};