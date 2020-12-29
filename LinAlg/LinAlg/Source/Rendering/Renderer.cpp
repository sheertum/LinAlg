#include "Rendering/Renderer.h"
#include <string>
#include <iostream>
#include <SDL.h>
#include "../../Dependencies/SDL_GFX/SDL2_gfxPrimitives.h"

Renderer::Renderer(unsigned int width, unsigned int height) :
	_window{ nullptr,nullptr }, _renderer{ nullptr,nullptr }, _buffer{nullptr,nullptr}
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string errorMessage = "SDL VIDEO could not be initialised, SDL message: ";
        errorMessage += SDL_GetError();
        throw std::logic_error{ errorMessage.c_str() };
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Could not initialise" << std::endl;
        return;
    }

    SDL_Window* window =
        SDL_CreateWindow("FlatGalaxy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if (!window) {
        std::string errorMessage = "SDL window could not be created, SDL message: ";
        errorMessage += SDL_GetError();
        throw std::logic_error{ errorMessage.c_str() };
    }
    _window = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>{ window, SDL_DestroyWindow };

    SDL_Renderer* renderer = SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::string errorMessage = "SDL renderer could not be created, SDL message: ";
        errorMessage += SDL_GetError();
        throw std::logic_error{ errorMessage.c_str() };
    }
    _renderer = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>{ renderer, SDL_DestroyRenderer };
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
    SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
}

void Renderer::drawTriangle(const Triangle triangle, const Color& color){ 
    Texture buffer{ createTexture(1000,1000) };
    SDL_SetRenderTarget(_renderer.get(), buffer.get());

    int n = 3;
    int i = 0;
    Sint16 vx[3]{};
    Sint16 vy[3]{};

    Uint32 hexColor = convertRGBtoHex(color);

    for(auto vector : triangle.getVectors()){
        vx[i] = vector.coordinates[0];
        vy[i] = vector.coordinates[1];
        i++;
    }

    filledPolygonColor(_renderer.get(), vx, vy, n, hexColor);
    _textures[triangle.getMaxZ()].push_back(std::move(buffer));
}

void Renderer::draw(SDL_Texture& texture)
{
    SDL_RenderCopy(_renderer.get(), &texture, nullptr, nullptr);
}

void Renderer::show()
{
    SDL_SetRenderTarget(_renderer.get(), nullptr);
    for (const auto& textures : _textures) {
        for (const auto& texture : textures.second) {
            draw(*texture);
        }
    }
    SDL_RenderPresent(_renderer.get());
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 0);
    SDL_RenderClear(_renderer.get());
}

void Renderer::startDrawing()
{
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 0);
    SDL_RenderClear(_renderer.get());
}

void Renderer::createCanvasTexture(unsigned int width, unsigned int height)
{
    _buffer = createTexture(width, height);
    SDL_SetRenderTarget(_renderer.get(), _buffer.get());
}

std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>& Renderer::getCanvasTexture()
{
    SDL_SetRenderTarget(_renderer.get(), nullptr);
    return _buffer;
}

uint32_t Renderer::convertRGBtoHex(const Color& color)
{
    return ((color.r) << 24) + ((color.g) << 16) + ((color.b) << 8) + 0xff;
}

std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> Renderer::createTexture(unsigned int width, unsigned int height) const
{
    Texture buffer{
        SDL_CreateTexture(_renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height),
        SDL_DestroyTexture };

    if (!buffer) {
        std::string errorMessage = "SDL targeted texture could not be created, SDL message: ";
        errorMessage += SDL_GetError();
        throw std::logic_error{ errorMessage.c_str() };
    }

    SDL_SetTextureBlendMode(buffer.get(), SDL_BLENDMODE_BLEND);

    return buffer;
}
