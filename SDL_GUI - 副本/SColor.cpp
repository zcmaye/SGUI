#include "SColor.h"

SColor::SColor(const SColor& color)
    :_r(color._r),_g(color._g),_b(color._b),_a(color._b)
{
}

SColor::SColor(int r, int g, int b, int a)
    : _r(r), _g(g), _b(b), _a(a)
{

}

SColor::SColor(SColor::GlobalColor color)
    : SColor(Uint8(color>>24), Uint8(color >> 16), Uint8(color >> 8), (Uint8)color)
{
}

SColor::SColor()
    :SColor(0,0,0,0)
{

}

int SColor::red() const
{
    return _r;
}

int SColor::green() const
{
    return _g;
}

int SColor::blue() const
{
    return _b;
}

int SColor::alpha() const
{
    return _a;
}

SDL_Color SColor::sdlColor() const
{
    return SDL_Color{_r,_g,_b,_a};
}
