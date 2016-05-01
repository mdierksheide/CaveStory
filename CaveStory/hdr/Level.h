#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "Globals.h"

class Graphics;
struct SDL_Texture;

class Level
{
	public:
		Level();
		Level(std::string map, Vector2 spawnPoint, Graphics &gfx);
		~Level();

		void Update(int dt);
		void Draw(Graphics &gfx);

	private:
		std::string _mapName;
		Vector2 _spawnPoint;
		Vector2 _size;
		SDL_Texture* _bgTexture;

		void LoadMap(std::string map, Graphics &gfx);

};

#endif