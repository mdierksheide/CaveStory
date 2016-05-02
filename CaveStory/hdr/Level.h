#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Globals.h"
#include "Rectangle.h"
#include "Tile.h"

class Graphics;
struct SDL_Rect;
struct SDL_Texture;
struct Tileset;

class Level
{
	public:
		Level();
		Level(std::string map, Vector2 spawnPoint, Graphics &gfx);
		~Level();

		void Update(int dt);
		void Draw(Graphics &gfx);

		std::vector<Rectangle> CheckTileCollisions(const Rectangle &other);

		const Vector2 GetPlayerSpawnPoint() const;

	private:
		std::string _mapName;
		Vector2 _spawnPoint;
		Vector2 _size;
		Vector2 _tileSize;
		SDL_Texture* _bgTexture;
		std::vector<Tile> _tileList;
		std::vector<Tileset> _tilesets;
		std::vector<Rectangle> _collisionRects;

		// Parses the XML file for this level
		void LoadMap(std::string map, Graphics &gfx);

};

struct Tileset
{
	SDL_Texture* Texture;
	int FirstGid;
	
	Tileset()
	{
		FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid)
	{
		Texture = texture;
		FirstGid = firstGid;
	}
};

#endif