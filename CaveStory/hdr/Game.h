/* Game.cpp
 * This class holds all information for our main game loop
 */

#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "Player.h"

class Game
{
	public:
		Game();
		~Game();
	private:
		void GameLoop();
		void Draw(Graphics& graphics);
		void Update(float dt);

		Player _player;
};

#endif