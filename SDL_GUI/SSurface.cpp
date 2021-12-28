#include "SSurface.h"
#include"Configure.h"
#include"SWindow.h"
SSurface::SSurface()
	:_surface(nullptr)
{
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
