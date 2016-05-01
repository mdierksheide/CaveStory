#include <SDL.h>

#include "Graphics.h"
#include "Level.h"

Level::Level() {}

Level::Level(std::string map, Vector2 spawnPoint, Graphics &gfx) :
	_mapName(map),
	_spawnPoint(spawnPoint),
	_size(Vector2(0, 0))
{
	LoadMap(map, gfx);
}

Level::~Level()
{

}

void Level::LoadMap(std::string map, Graphics &gfx)
{
	// TEMP BACKGROUND LOAD
	_bgTexture = SDL_CreateTextureFromSurface(gfx.GetRenderer(),
		gfx.LoadImage("res\\backgrounds\\bkBlue.png"));
	_size = Vector2(1280, 960);
}

void Level::Update(int dt)
{

}

void Level::Draw(Graphics &gfx)
{
	SDL_Rect srcRect = { 0, 0, 64, 64 };
	SDL_Rect destRect;
	destRect.w = 64;
	destRect.h = 64;

	for (int x = 0; x < _size.x / 64; x++)
	{
		for (int y = 0; y < _size.y / 64; y++)
		{
			destRect.x = x * 64;
			destRect.y = y * 64;
			gfx.BlitSurface(_bgTexture, &srcRect, &destRect);
		}
	}
}