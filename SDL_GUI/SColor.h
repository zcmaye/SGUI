#pragma once
#include"Configure.h"

class SColor
{
public:
	enum GlobalColor :Uint32	//RGBA
	{
		White 		= 0xffffffff,
		Black 		= 0x000000ff,
		Red			= 0xff0000ff,
		DarkRed		= 0x800000ff,
		Green		= 0x00ff00ff,
		DarkGreen	= 0x008000ff,
		Blue		= 0x0000ffff,
		DarkBlue	= 0x000080ff,
		Cyan		= 0x00ffffff,
		DarkCyan	= 0x008080ff,
		Magenta		= 0xff00ffff,
		DarkMagenta	= 0x800080ff,
		Yellow		= 0xffff00ff,
		DarkYellow	= 0x808000ff,
		Gray		= 0xa0a0a4ff,
		DarkGray	= 0x808080ff,
		LightGray	= 0xc0c0c0ff
	};
public:
	SColor(const SColor& color);
	SColor(int r, int g, int b, int a = 0xff);
	SColor(SColor::GlobalColor color);
	SColor();

	int red() const;
	int green() const;
	int blue() const;
	int alpha() const;
	SDL_Color sdlColor() const;
private:
	Uint8 _r;
	Uint8 _g;
	Uint8 _b;
	Uint8 _a;
};

