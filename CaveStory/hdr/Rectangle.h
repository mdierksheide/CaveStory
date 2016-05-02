#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Globals.h"

class Rectangle
{
	public:
		Rectangle() {}
		Rectangle(int x, int y, int w, int h) :
			_x(x),
			_y(y),
			_width(w),
			_height(h)
		{}

		// Getters
		const int GetCenterX() const { return _x + _width / 2; }
		const int GetCenterY() const { return _y + _height / 2; }
		const int GetLeft() const { return _x; }
		const int GetRight() const { return _x + _width; }
		const int GetTop() const { return _y; }
		const int GetBottom() const { return _y + _height; }
		const int GetWidth() const { return _width; }
		const int GetHeight() const { return _height; }

		const int GetSide(const Sides::Side side) const
		{
			if (side == Sides::TOP) { return GetTop(); }
			else if (side == Sides::BOTTOM) { return GetBottom(); }
			else if (side == Sides::LEFT) { return GetLeft(); }
			else if (side == Sides::RIGHT) { return GetRight(); }
			else { return Sides::NONE; }
		}

		const bool CollidesWith(const Rectangle &other) const
		{
			return GetRight() >= other.GetLeft() &&
				GetLeft() <= other.GetRight() &&
				GetTop() <= other.GetBottom() &&
				GetBottom() >= other.GetTop();
		}

		const bool IsValidRectangle() const
		{
			return _x >= 0 && _y >= 0 && _width >= 0 && _height >= 0;
		}

	private:
		int _x, _y, _width, _height;
};

#endif