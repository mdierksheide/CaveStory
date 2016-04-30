#include "SDL.h"
#include "Graphics.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(640, 480, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Blink");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(_window);
}