#include "SApplication.h"
#include"Configure.h"
#include"SWidget.h"
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
				w->clear();							//先清屏
				w->event(&ev);						//处理窗口事件
				SDL_RenderPresent(w->renderer());	//显示界面
			}
			if (allWindowIsHidden())
			{
				quit = true;
			}		
		}
	}
	return 0;
}

void SApplication::addWindow(SWidget* window)
{
	s_WindowQue.insert(window);
}

void SApplication::removeWindow(SWidget* window)
{
	s_WindowQue.erase(window);
}

bool SApplication::destroyAllWindows()
{
	for (auto w : s_WindowQue)
	{
		SDL_DestroyWindow(w->sdlWindow());
	}
	return false;
}

bool SApplication::allWindowIsHidden()
{
	if (s_WindowQue.empty())
		return false;

	bool isAllHidden = true;
	for (auto w : s_WindowQue)
	{
		if (!w->isHidden())
		{
			isAllHidden = false;
		}
	}
	return isAllHidden;
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
