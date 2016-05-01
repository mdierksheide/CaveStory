/* AnimatedSprite
 * Holds logic for animating sprites.
 */

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <vector>

#include <SDL.h>

#include "Globals.h"
#include "Sprite.h"

class Graphics;

class AnimatedSprite : public Sprite
{
	public:
		AnimatedSprite();
		AnimatedSprite(Graphics &gfx, const std::string &filePath,
			int sourceX, int sourceY, int width, int height, float posX,
			float posY, float timeToUpdate);

		// Plays the animation given if not already playing
		void PlayAnimation(std::string animation, bool once = false);

		// Updates the animated sprite
		void Update(float dt);

		// Draws the sprite to the screen
		void Draw(Graphics &graphics, int x, int y);

	protected:
		double _timeToUpdate;
		bool _currentAnimationOnce;
		std::string _currentAnimation;

		// Adds animation to the map of animations for this sprite
		void AddAnimation(int frames, int x, int y, std::string name,
			int width, int height, Vector2 offset);

		// Resets all animations associated with this sprite
		void ResetAnimation();

		// Stops the current animation
		void StopAnimation();

		void SetVisibility(bool visible);

		// Sets up all animations for a sprite
		virtual void SetupAnimation() = 0;

		// Logic that triggers when the given animation finishes
		virtual void AnimationDone(std::string currentAnimation) = 0;

	private:
		std::map<std::string, std::vector<SDL_Rect>> _animations;
		std::map<std::string, Vector2> _offsets;

		unsigned int _iFrame;
		double _timeElapsed;
		bool _visible;
};

#endif