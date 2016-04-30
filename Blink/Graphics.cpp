#include "SDL.h"

#include "Graphics.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Blink");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(_window);
}