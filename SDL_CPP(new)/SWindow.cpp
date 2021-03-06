#include "SWindow.h"
#include "SApplication.h"
static SWindow* s_instance = nullptr;

SWindow::SWindow(int w, int h, const std::string& title)
	:_width(w),_height(h)
	,_window(nullptr)
	,_renderer(nullptr)
	,_bkColor(SColor::White)
{
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		SDL_Log("window create failed %s\n", SDL_GetError());
		return;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SApplication::addWindow(this);
	s_instance = this;
}

SWindow::~SWindow()
{
	SApplication::removeWindow(this);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

int SWindow::alert(SDL_FlashOperation operation)
{	
	return SDL_FlashWindow(_window, operation);
}

Uint32 SWindow::windowFlags()
{
	return SDL_GetWindowFlags(_window);
}

void SWindow::setWindowFlags(Uint32 flags)
{

}

SPoint SWindow::windowPos()
{
	int tx, ty;
	SDL_GetWindowPosition(_window, &tx, &ty);
	return SPoint(tx,ty);
}

void SWindow::move(int x, int y)
{
	SDL_SetWindowPosition(_window, x, y);
}

SSize SWindow::size()
{
	int tw, th;
	SDL_GetWindowSize(_window, &tw, &th);
	return SSize(tw,th);
}

void SWindow::setSize(int w, int h)
{
	SDL_SetWindowSize(_window,w, h);
}

std::string SWindow::windowTitle()
{
	
	return std::string(SDL_GetWindowTitle(_window));
}

void SWindow::setWindowTitle(const std::string& title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

void SWindow::setWindowIcon(SDL_Surface* icon)
{
	SDL_SetWindowIcon(_window, icon);
}

void SWindow::hide()
{
	SDL_HideWindow(_window);
}

void SWindow::show()
{
	SDL_ShowWindow(_window);
}

void SWindow::showMaximize()
{
	SDL_MaximizeWindow(_window);
}

void SWindow::showMinimize()
{
	SDL_MinimizeWindow(_window);
}

void SWindow::showNormal()
{
	SDL_RestoreWindow(_window);
}

void SWindow::showFullscreen()
{
	SDL_SetWindowFullscreen(_window,SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void SWindow::raise()
{
	SDL_RaiseWindow(_window);
}

void SWindow::setWindowOpacity(float opacity)
{
	SDL_SetWindowOpacity(_window,opacity);
}

float SWindow::windowOpacity()
{
	float op;
	SDL_GetWindowOpacity(_window, &op);
	return op;
}

void SWindow::setBackgroundColor(SColor color)
{
	_bkColor = color;
}

SDL_Renderer* SWindow::renderer()
{
	return _renderer;
}

void SWindow::clear() const
{
	SDL_SetRenderDrawColor(_renderer, _bkColor.red(), _bkColor.green(), _bkColor.blue(), _bkColor.alpha());
	SDL_RenderClear(_renderer);
}

void SWindow::flush() const
{
	SDL_RenderPresent(_renderer);
}

bool SWindow::event(SDL_Event* ev)
{
	return false;
}

bool SWindow::init()
{
	return true;
}

void SWindow::mainLoop()
{

}

void SWindow::quit()
{
}

void SWindow::draw()
{
}

SWindow* SWindow::instance()
{
	if (s_instance == nullptr)
		throw nullptr;
	return s_instance;
}
