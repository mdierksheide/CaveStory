#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int SPRITE_SCALE = 2;
}

namespace Sides
{
	enum Side
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side GetOppositeSide(Side side)
	{
		if      (side == TOP) { return BOTTOM; }
		else if (side == BOTTOM) { return TOP; }
		else if (side == LEFT) { return RIGHT; }
		else if (side == RIGHT) { return LEFT; }
		else { return NONE; }
	}
}

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2
{
	int x;
	int y;
	Vector2() :
		x(0), y(0)
	{
	}
	Vector2(int x, int y) :
		x(x), y(y)
	{
	}
	Vector2 zero()
	{
		Vector2(0, 0);
	}
};

#endif