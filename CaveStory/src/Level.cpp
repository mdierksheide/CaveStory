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

	// Load tile layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");

	if (pLayer != NULL)
	{
		while (pLayer)
		{
			// Load the data element
			XMLElement* pData = pLayer->FirstChildElement("data");

			if (pData != NULL)
			{
				while (pData != NULL)
				{
					//Load the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");

					if (pTile != NULL)
					{
						int tileCnt = 0;

						while (pTile)
						{
							// Build each tile. Gid of 0 means skip tile
							int gid = pTile->IntAttribute("gid");

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
									SDL_QueryTexture(tls.Texture, NULL, NULL,
										&tilesetWidth, &tilesetHeight);
									int tsxx = 
										gid % (tilesetWidth / tileWidth);
									tsxx *= tileWidth;
									int tsyy =
										gid / (tilesetWidth / tileWidth);
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
					}

					pData = pData->NextSiblingElement("tile");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
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