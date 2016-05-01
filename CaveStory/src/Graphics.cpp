#include "SDL.h"
#include "SDL_image.h"

#include "Globals.h"
#include "Graphics.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0,
		&_window, &_renderer);
	SDL_SetWindowTitle(_window, "Blink");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

SDL_Surface* Graphics::LoadImage(const std::string &filePath)
{
	// If the sprite sheet hasn't been loaded, load it
	if (_spriteSheets.count(filePath) == 0)
	{
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}

	return _spriteSheets[filePath];
}

void Graphics::BlitSurface(SDL_Texture* src, SDL_Rect* srcRect, SDL_Rect* destRect)
{
	SDL_RenderCopy(_renderer, src, srcRect, destRect);
}

void Graphics::Flip()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::Clear()
{
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::GetRenderer() const
{
	return _renderer;
}