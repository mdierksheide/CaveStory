#include "Player.h"
#include "Graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &gfx, float x, float y) :
	AnimatedSprite(gfx, "res\\sprites\\MyChar.png", 0, 0, 16, 16, x, y, 100)
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

void Player::Update(float dt)
{
	_x += _dx * dt;

	AnimatedSprite::Update(dt);
}

void Player::Draw(Graphics &gfx)
{
	AnimatedSprite::Draw(gfx, _x, _y);
}

