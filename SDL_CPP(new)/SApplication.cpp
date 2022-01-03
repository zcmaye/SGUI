#include "SApplication.h"
#include"SWindow.h"
SApplication::SApplication(int argc, char* argv[])
{
	if (!init())
	{
		return;
	}
}

SApplication::~SApplication()
{
	close();
}

int SApplication::exec()
{
	bool quit = false;
	while (!quit)
	{
		static  SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}

			for (auto w : s_WindowQue)
			{
				//w->clear();							//先清屏
				w->event(&ev);						//处理窗口事件
				w->flush();	//显示界面
			}	
		}
	}
	return 0;
}

void SApplication::addWindow(SWindow* window)
{
	s_WindowQue.insert(window);
}

void SApplication::removeWindow(SWindow* window)
{
	s_WindowQue.erase(window);
}

bool SApplication::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_Log("cannot init SDL：%s", SDL_GetError());
		return false;
	}
	return true;
}

bool SApplication::close()
{
	SDL_Quit();
	return true;
}
