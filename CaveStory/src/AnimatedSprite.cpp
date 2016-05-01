#include "AnimatedSprite.h"
#include "Graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &gfx, const std::string &filePath,
	int sourceX, int sourceY, int width, int height, float posX,
	float posY, float timeToUpdate) :
		Sprite(gfx, filePath, sourceX, sourceY, width, height, posX, posY),
		_iFrame(0),
		_timeToUpdate(timeToUpdate),
		_visible(true),
		_timeElapsed(0),
		_currentAnimationOnce(false),
		_currentAnimation("")
{
}

void AnimatedSprite::AddAnimation(int frames, int x, int y,
	std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rects;

	for (int i = 0; i < frames; i++)
	{
		SDL_Rect rect = { x + width * i, y, width, height };
		rects.push_back(rect);
	}

	_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rects));
	_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::ResetAnimation()
{
	_animations.clear();
	_offsets.clear();
}

void AnimatedSprite::PlayAnimation(std::string name, bool once)
{
	_currentAnimationOnce = once;

	if (_currentAnimation != name)
	{
		_currentAnimation = name;
		_iFrame = 0;
	}
}

void AnimatedSprite::SetVisibility(bool visible)
{
	_visible = visible;
}

void AnimatedSprite::StopAnimation()
{
	_iFrame = 0;
	AnimationDone(_currentAnimation);
}

void AnimatedSprite::Update(float dt)
{
	Sprite::Update();

	_timeElapsed += dt;
	if (_timeElapsed > _timeToUpdate)
	{
		_timeElapsed -= _timeToUpdate;

		if (_iFrame < _animations[_currentAnimation].size() - 1)
		{
			_iFrame++;
		}
		else
		{
			if (_currentAnimationOnce)
			{
				SetVisibility(false);
			}
			_iFrame = 0;
			AnimationDone(_currentAnimation);
		}
	}
}

void AnimatedSprite::Draw(Graphics &gfx, int x, int y)
{
	if (_visible)
	{
		SDL_Rect destRect;
		destRect.x = x + _offsets[_currentAnimation].x;
		destRect.y = y + _offsets[_currentAnimation].y;
		destRect.w = _sourceRect.w * Globals::SPRITE_SCALE;
		destRect.h = _sourceRect.h * Globals::SPRITE_SCALE;

		SDL_Rect srcRect = _animations[_currentAnimation][_iFrame];
		gfx.BlitSurface(_spriteSheet, &srcRect, &destRect);
	}
}