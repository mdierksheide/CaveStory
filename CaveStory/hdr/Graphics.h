/* Graphics
 * This class handles all drawing of the screen
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

#include <SDL.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
	public:
		Graphics();
		~Graphics();

		// Loads an image into the _spriteSheets map if it doesn't already exist.
		// Returns the image whether or not it was just loaded.
		SDL_Surface* LoadImage(const std::string &filePath);

		// Draws a texture to a certain part of the screen.
		void BlitSurface(SDL_Texture* src, SDL_Rect* srcRect, SDL_Rect* destRect);

		// Draws contents of _renderer to the screen.
		void Flip();

		// Clears the screen.
		void Clear();

		// Returns the _renderer.
		SDL_Renderer* GetRenderer() const;

	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;

		std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif