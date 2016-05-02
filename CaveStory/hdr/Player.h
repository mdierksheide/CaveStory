#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"

class Graphics;

class Player : public AnimatedSprite
{
	public:
		Player();
		Player(Graphics &gfx, Vector2 spawn);

		virtual void SetupAnimation();
		virtual void AnimationDone(std::string name);

		void Draw(Graphics &gfx);
		void Update(float dt);

		// Moves the player left by dx
		void MoveLeft();

		// Moves the player right by dx
		void MoveRight();

		// Stops moving the player
		void StopMoving();

		void HandleTileCollisions(std::vector<Rectangle> &others);

		// Getters
		const float GetX() const;
		const float GetY() const;

	private:
		float _dx, _dy;
		Direction _facing;
		bool _grounded;
};

#endif