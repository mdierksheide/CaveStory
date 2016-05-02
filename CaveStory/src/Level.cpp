#include <algorithm>
#include <cmath>
#include <sstream>

#include <SDL.h>
#include "tinyxml2.h"

#include "Graphics.h"
#include "Level.h"

using namespace tinyxml2;

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
	// Load the .tmx document
	XMLDocument doc;
	std::stringstream ss;
	ss << "res\\maps\\" << map << ".tmx";
	doc.LoadFile(ss.str().c_str());

	// Parse the .tmx document
	XMLElement* mapNode = doc.FirstChildElement("map");

	// Get the width and height of the whole map in tiles
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	_size = Vector2(width, height);

	// Get the width and height of each tile in pixels
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	_tileSize = Vector2(width, height);

	// Load the tilesets
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");

	if (pTileset != NULL)
	{
		while (pTileset)
		{
			int firstGid;
			const char* src = pTileset->FirstChildElement("image")
				->Attribute("source");
			std::stringstream ss;

			pTileset->QueryIntAttribute("firstgid", &firstGid);
			ss << "res\\maps\\" << src;
			SDL_Texture* texture = SDL_CreateTextureFromSurface(
				gfx.GetRenderer(), gfx.LoadImage(ss.str()));
			_tilesets.push_back(Tileset(texture, firstGid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	// Parse tile layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");

	while (pLayer)
	{
		// Load the data element
		XMLElement* pData = pLayer->FirstChildElement("data");

		while (pData)
		{
			//Load the tile element
			XMLElement* pTile = pData->FirstChildElement("tile");
			int tileCnt = 0;

			while (pTile)
			{
				// Build each tile
				int gid = pTile->IntAttribute("gid");

				// Gid of 0 means no tile in this spot
				if (gid != 0)
				{
					Tileset tls;

					for (unsigned int i = 0; i < _tilesets.size(); i++)
					{
						// Look for tileset corresponding to gid
						if (_tilesets[i].FirstGid <= gid)
						{
							tls = _tilesets.at(i);
							gid -= tls.FirstGid;
							break;
						}
					}

					// Safety check that a tileset was found
					if (tls.FirstGid != -1)
					{
						// Get position of the tile in the level
						int xx = (tileCnt % width) * tileWidth;
						int yy = (tileCnt / width) * tileHeight;
						Vector2 finalTilePos = Vector2(xx, yy);

						// Calculate pos of the tile in tileset
						int tilesetWidth, tilesetHeight;
						SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth,
							&tilesetHeight);
						int tsxx = gid % (tilesetWidth / tileWidth);
						tsxx *= tileWidth;
						int tsyy = gid / (tilesetWidth / tileWidth);
						tsyy *= tileHeight;
						Vector2 finalTilesetPos(tsxx, tsyy);

						// Build tile and add to level
						Tile tile(tls.Texture, Vector2(tileWidth,
							tileHeight), finalTilesetPos, finalTilePos);
						_tileList.push_back(tile);
					}
				}

				tileCnt++;
				pTile = pTile->NextSiblingElement("tile");
			}

			pData = pData->NextSiblingElement("tile");
		}

		pLayer = pLayer->NextSiblingElement("layer");
	}

	// Parse collisions
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");

	while (pObjectGroup)
	{
		const char* name = pObjectGroup->Attribute("name");
		std::stringstream ss;
		ss << name;

		if (ss.str() == "collisions")
		{
			XMLElement* pObject = pObjectGroup->FirstChildElement("object");

			while (pObject)
			{
				float x, y, width, height;
				x = pObject->FloatAttribute("x");
				y = pObject->FloatAttribute("y");
				width = pObject->FloatAttribute("width");
				height = pObject->FloatAttribute("height");
				Rectangle obj = Rectangle(
					(int)std::ceil(x) * Globals::SPRITE_SCALE,
					(int)std::ceil(y) * Globals::SPRITE_SCALE,
					(int)std::ceil(width) * Globals::SPRITE_SCALE,
					(int)std::ceil(height) * Globals::SPRITE_SCALE);
				_collisionRects.push_back(obj);

				pObject = pObject->NextSiblingElement("object");
			}
		}
		else if (ss.str() == "spawn points")
		{
			XMLElement* pObject = pObjectGroup->FirstChildElement("object");

			while (pObject)
			{
				float x = pObject->FloatAttribute("x");
				float y = pObject->FloatAttribute("y");
				const char* name = pObject->Attribute("name");
				std::stringstream ss;
				ss << name;

				if (ss.str() == "player")
				{
					_spawnPoint = Vector2(std::ceil(x) * Globals::SPRITE_SCALE,
						std::ceil(y) * Globals::SPRITE_SCALE);
				}

				pObject = pObject->NextSiblingElement("object");
			}
		}

		pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
	}
}

void Level::Update(int dt)
{

}

void Level::Draw(Graphics &gfx)
{
	for (unsigned int i = 0; i < _tileList.size(); i++)
	{
		_tileList.at(i).Draw(gfx);
	}
}

std::vector<Rectangle> Level::CheckTileCollisions(const Rectangle &other)
{
	std::vector<Rectangle> others;

	for (unsigned int i = 0; i < _collisionRects.size(); i++)
	{
		if (_collisionRects.at(i).CollidesWith(other))
		{
			others.push_back(_collisionRects.at(i));
		}
	}

	return others;
}

const Vector2 Level::GetPlayerSpawnPoint() const
{
	return _spawnPoint;
}