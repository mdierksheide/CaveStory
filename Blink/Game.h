#ifndef GAME_H
#define GAME_H

class Graphics;

class Game
{
public:
	Game();
	~Game();
private:
	void GameLoop();
	void Draw(Graphics& graphics);
	void Update(float dt);
};

#endif