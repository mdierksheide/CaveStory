#include "Player.h"
#include "Graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_MAX = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &gfx, Vector2 spawn) :
	AnimatedSprite(gfx, "res\\sprites\\MyChar.png", 0, 0, 16, 16,
		(float)spawn.x, (float)spawn.y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false)
{
	gfx.LoadImage("res\\sprites\\MyChar.png");

	SetupAnimation();
	PlayAnimation("RunRight");
}

void Player::SetupAnimation()
{
	AddAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	AddAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	AddAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	AddAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::AnimationDone(std::string name)
{

}

void Player::MoveLeft()
{
	_dx = -player_constants::WALK_SPEED;
	PlayAnimation("RunLeft");
	_facing = LEFT;
}

void Player::MoveRight()
{
	_dx = player_constants::WALK_SPEED;
	PlayAnimation("RunRight");
	_facing = RIGHT;
}

void Player::StopMoving()
{
	_dx = 0.0f;
	
	if (_facing == LEFT) 
	{ 
		PlayAnimation("IdleLeft"); 
	}
	else
	{
		PlayAnimation("IdleRight");
	}
}

void Player::HandleTileCollisions(std::vector<Rectangle> &others)
{
	for (unsigned int i = 0; i < others.size(); i++)
	{
		Sides::Side collisionSide = Sprite::GetCollisionSide(others.at(i));

		if (collisionSide != Sides::NONE)
		{
			switch (collisionSide)
			{
				case Sides::RIGHT:
					_x = (float)others.at(i).GetLeft() - _boundingBox.GetWidth() - 1;
					break;
				case Sides::LEFT:
					_x = (float)others.at(i).GetRight() + 1;
					break;
				case Sides::TOP:
					_y = (float)others.at(i).GetBottom() + 1;
					_dy = 0;
					break;
				case Sides::BOTTOM:
					_y = (float)others.at(i).GetTop() - _boundingBox.GetHeight() - 1;
					_dy = 0;
					_grounded = true;
					break;
				default:
					break;
			}
		}
	}
}

void Player::Update(float dt)
{
	if (_dy <= player_constants::GRAVITY_MAX)
	{
		_dy += player_constants::GRAVITY * dt;
	}

	_x += _dx * dt;
	_y += _dy * dt;

	AnimatedSprite::Update(dt);
}

void Player::Draw(Graphics &gfx)
{
	AnimatedSprite::Draw(gfx, (int)_x, (int)_y);
}

const float Player::GetX() const
{
	return _x;
}

const float Player::GetY() const
{
	return _y;
}