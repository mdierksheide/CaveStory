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

	_boundingBox = Rectangle(_x, _y, width * Globals::SPRITE_SCALE,
		height * Globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::Draw(Graphics &gfx, int x, int y)
{
	SDL_Rect destRect = { x, y, _sourceRect.w * Globals::SPRITE_SCALE,
		_sourceRect.h * Globals::SPRITE_SCALE };

	gfx.BlitSurface(_spriteSheet, &_sourceRect, &destRect);
}

void Sprite::Update() 
{
	_boundingBox = Rectangle(_x, _y, _sourceRect.w * Globals::SPRITE_SCALE,
		_sourceRect.h * Globals::SPRITE_SCALE);
}

const Rectangle Sprite::GetBoundingBox() const
{
	return _boundingBox;
}

const Sides::Side Sprite::GetCollisionSide(Rectangle &other) const
{
	int overlapR, overlapL, overlapT, overlapB;

	overlapR = _boundingBox.GetRight() - other.GetLeft();
	overlapL = other.GetRight() - _boundingBox.GetLeft();
	overlapT = other.GetBottom() - _boundingBox.GetTop();
	overlapB = _boundingBox.GetBottom() - other.GetTop();

	int vals[4] = { abs(overlapR), abs(overlapL), abs(overlapT), abs(overlapB) };
	int minVal = vals[0];

	for (int i = 0; i < 4; i++)
	{
		if (vals[i] < minVal)
		{
			minVal = vals[i];
		}
	}

	if      (minVal == abs(overlapR)) { return Sides::RIGHT; }
	else if (minVal == abs(overlapL)) { return Sides::LEFT; }
	else if (minVal == abs(overlapT)) { return Sides::TOP; }
	else if (minVal == abs(overlapB)) { return Sides::BOTTOM; }
	else { return Sides::NONE; }
}