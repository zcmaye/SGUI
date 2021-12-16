#pragma once
#include<SDL_rect.h>
#include<iostream>
struct SPoint
{
	SPoint();
	SPoint(int x, int y);
	SPoint operator+(const SPoint& point) const;
	int x;
	int y;
};

struct SSize
{
	SSize();
	SSize(int w, int h);
	int w;
	int h;
};

class SRect
{
public:
	SRect();
	SRect(int x, int y, int width, int height);
	SRect(const SPoint& topLeft, const SSize& size);
	SRect(const SPoint& topLeft, const SPoint& bottomRight);

	bool contains(const SRect& rect, bool proper = false) const;
	bool contains(const SPoint& point) const;
	bool contains(int x, int y) const;

	inline int x1() { return _x1; }
	inline int y1() { return _y1; }
	inline int x2() { return _x2; }
	inline int y2() { return _y2; }

	inline SDL_Rect sdlRect()
	{ 
		return SDL_Rect{ _x1,_y1, _x2 - _x1,_y2 - _y1 }; 
	}
	friend std::ostream& operator<<(std::ostream& out, const SRect& rect);

private:
	int _x1;
	int _y1;
	int _x2;
	int _y2;
};

