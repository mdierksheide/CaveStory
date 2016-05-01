#include "Globals.h"
#include "Graphics.h"
#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &gfx, const std::string &filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY) :
		_x(posX),
		_y(posY)
{
	_sourceRect.x = sourceX;
	_sourceRect.y = sourceY;
	_sourceRect.w = width;
	_sourceRect.h = height;

	_spriteSheet = SDL_CreateTextureFromSurface(gfx.GetRenderer(),
		gfx.LoadImage(filePath));
	if (_spriteSheet == NULL)
	{
		printf("Error: Unable to load image.\n");
	}
}

Sprite::~Sprite() {}

void Sprite::Draw(Graphics &gfx, int x, int y)
{
	SDL_Rect destRect = { x, y, _sourceRect.w * Globals::SPRITE_SCALE,
		_sourceRect.h * Globals::SPRITE_SCALE };

	gfx.BlitSurface(_spriteSheet, &_sourceRect, &destRect);
}

void Sprite::Update() {}