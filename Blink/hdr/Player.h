#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"

class Graphics;

class Player : AnimatedSprite
{
	public:
		Player();
		Player(Graphics &gfx, float x, float y);

		virtual void SetupAnimation();
		virtual void AnimationDone(std::string name);

		// Moves the player left by dx
		void MoveLeft();

		// Moves the player right by dx
		void MoveRight();

		// Stops moving the player
		void StopMoving();

		void Draw(Graphics &gfx);
		void Update(float dt);

	private:
		float _dx, _dy;
		Direction _facing;
};

#endif