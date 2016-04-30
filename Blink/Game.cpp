/* Game.cpp
 * This class holds all information for our main game loop
 */

#include <algorithm>

#include "SDL.h"

#include "Game.h"
#include "Graphics.h"
#include "Input.h"

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	GameLoop();
}

Game::~Game()
{

}

void Game::GameLoop()
{
	Graphics gfx;
	Input input;
	SDL_Event event;
	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true)
	{
		input.BeginNewFrame();

		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if (event.key.repeat == 0)
					{
						input.KeyDownEvent(event);
					}
					break;
				case SDL_KEYUP:
					input.KeyUpEvent(event);
					break;
				case SDL_QUIT:
					return;
			}
		}

		if (input.WasKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int dt = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		Update(std::min(dt, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::Draw(Graphics& gfx)
{

}

void Game::Update(float dt)
{

}