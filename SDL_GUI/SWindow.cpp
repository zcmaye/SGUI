#include "SWindow.h"

static SWindow* s_instance = nullptr;

SWindow::SWindow(int w, int h)
	:_width(w),_height(h)
	,_window(nullptr)
	,_winRenderer(nullptr)
{
	_window = SDL_CreateWindow("SWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		SDL_Log("window create failed %s\n", SDL_GetError());
		return;
	}
	_winRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	s_instance = this;


	SWidget::setWindowPos(0, 0);
	SWidget::setWindowSize(_width, _height);
	
}

SWindow::~SWindow()
{
	SDL_DestroyRenderer(_winRenderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

int SWindow::flash(SDL_FlashOperation operation)
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

void SWindow::setWindowPos(int x, int y)
{
	SDL_SetWindowPosition(_window, x, y);
}

SSize SWindow::windowSize()
{
	int tw, th;
	SDL_GetWindowSize(_window, &tw, &th);
	return SSize(tw,th);
}

void SWindow::setWindowSize(int w, int h)
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
	SWidget::show();
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

SDL_Renderer* SWindow::renderer()
{
	return _winRenderer;
}

SWindow::operator SDL_Renderer* ()
{
	return _winRenderer;
}

SWindow* SWindow::instance()
{
	if (s_instance == nullptr)
		throw nullptr;
	return s_instance;
}

//bool SWindow::event(SEvent* ev)
//{
//	SDL_Log("SWindow event\n");
//	return false;
//}
