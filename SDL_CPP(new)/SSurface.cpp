#include "SSurface.h"
#include"Configure.h"
#include"SWindow.h"
SSurface::SSurface()
	:SSurface(250,250)
{
}

SSurface::SSurface(int w, int h)
{
	_surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	if (!_surface)
	{
		SDL_Log("SSurface load failed\n");
		return;
	}
}

SSurface::SSurface(const std::string& file) 
{
#ifdef HAVE_IMAGE
	_surface = IMG_Load(file.c_str());
#else
	_surface = SDL_LoadBMP(file.c_str());
#endif // HAVE_IMAGE
	if (!_surface)
	{
		SDL_Log("SSurface load failed\n");
		return;
	}
}

SSurface::SSurface(SDL_Surface* surface)
{
	_surface = surface;
}

SSurface::~SSurface()
{
	SDL_FreeSurface(_surface);
}

SDL_Surface* SSurface::surface()
{
	return _surface;
}

SSurface::operator SDL_Surface* ()
{
	return _surface;
}

int SSurface::width() const
{
	return _surface->w;
}

int SSurface::height() const
{
	return _surface->h;
}

SDL_Texture* SSurface::sdlTexture() const
{
	return SDL_CreateTextureFromSurface(SWindow::instance()->renderer(), _surface);
}

bool SSurface::lock() const
{
	if (SDL_MUSTLOCK(_surface))
	{
		if(SDL_LockSurface(_surface) < 0)
			return  false;
	}
	return true;
}

void SSurface::unlock() const
{
	if (SDL_MUSTLOCK(_surface))
	{
		SDL_UnlockSurface(_surface);
	}
}

bool SSurface::setColorKey(const SColor& color) const
{
	if (0 > SDL_SetColorKey(_surface, SDL_TRUE, SDL_MapRGBA(_surface->format, color.red(), color.green(), color.blue(),color.alpha())))
	{
		return false;
	}
	return true;
}


bool SSurface::fillRect(const SRect& rect, const SColor& color) const
{
	const SDL_Rect& r = rect.sdlRect();
	if (0 > SDL_FillRect(_surface,&r , SDL_MapRGBA(_surface->format, color.red(), color.green(), color.blue(), color.alpha())))
	{
		return false;
	}
	return true;
}
