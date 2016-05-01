/* Sprite
 * Handles the drawing and updating of all sprites.
 */

#ifndef SPRITE_H
#define SPRITE_H

#include<string>

#include "SDL.h"

class Graphics;

class Sprite
{
	public:
		Sprite();
		Sprite(Graphics &gfx, const std::string &filePath, int sourceX,
			int sourceY, int width, int height, float posX, float posY);
		virtual ~Sprite();

		virtual void Update();
		void Draw(Graphics &graphics, int x, int y);

	protected:
		SDL_Rect _sourceRect;
		SDL_Texture* _spriteSheet;
		
		float _x, _y;
};

#endif