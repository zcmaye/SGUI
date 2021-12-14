#include"SWindow.h"
#include"SSurface.h"
void handingEvent(SWindow*w);
int main(int argc, char* argv[])    
{
	SDL_Init(SDL_INIT_VIDEO);
	SWindow w(640, 480);
	
	SSurface surface("res/blueFrame.bmp");
	w.setWindowIcon(surface);

	auto size = w.windowSize();
	auto  point = w.windowPos();
	auto title = w.windowTitle();
	SDL_Log("%d %d %d %d %s\n", size.w, size.h, point.x, point.y, title.c_str());

	w.setWindowOpacity(0.5);

	while (true)
	{
		handingEvent(&w);
	}
	
	return 0;
}
void handingEvent(SWindow* w)
{
	static SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			
			break;
		default:

			break;
		}
	}
}