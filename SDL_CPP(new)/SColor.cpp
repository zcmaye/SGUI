#include "SColor.h"

SColor::SColor(const SColor& color)
    :_r(color._r),_g(color._g),_b(color._b),_a(color._b)
{
}

SColor::SColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
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

Uint8 SColor::red() const
{
    return _r;
}

Uint8 SColor::green() const
{
    return _g;
}

Uint8 SColor::blue() const
{
    return _b;
}

Uint8 SColor::alpha() const
{
    return _a;
}

SDL_Color SColor::sdlColor() const
{
    return SDL_Color{_r,_g,_b,_a};
}

