#ifndef TILE_H
#define TILE_H

#include "Globals.h"

struct SDL_Texture;
class Graphics;

class Tile
{
	public:
		Tile();
		Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPos,
			Vector2 pos);

		void Update(int dt);
		void Draw(Graphics &gfx);

	private:
		SDL_Texture* _tileset;
		Vector2 _size;
		Vector2 _tilesetPos;
		Vector2 _pos;
};

#endif