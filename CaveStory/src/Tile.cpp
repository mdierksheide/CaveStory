#include "SDL.h"

#include "Graphics.h"
#include "Tile.h"

Tile::Tile() 
{
}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPos,
	Vector2 pos) :
		_tileset(tileset),
		_size(size),
		_tilesetPos(tilesetPos),
		_pos(Vector2(pos.x * Globals::SPRITE_SCALE,
			pos.y * Globals::SPRITE_SCALE))
{
}

void Tile::Update(int dt)
{
}

void Tile::Draw(Graphics &gfx)
{
	SDL_Rect destRect = { _pos.x, _pos.y, _size.x * Globals::SPRITE_SCALE,
		_size.y * Globals::SPRITE_SCALE };
	SDL_Rect srcRect = { _tilesetPos.x, _tilesetPos.y, _size.x, _size.y };

	gfx.BlitSurface(_tileset, &srcRect, &destRect);
}