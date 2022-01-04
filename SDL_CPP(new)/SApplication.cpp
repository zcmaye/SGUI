#include "SApplication.h"
#include"SWindow.h"
#include"SElapsedTimer.h"

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
	SElapsedTimer elapsedTimer;
	//调用初始化函数
	for (auto w : s_WindowQue)
	{
		w->init();
	}
	bool quit = false;
	while (!quit)
	{
		elapsedTimer.start();
		static  SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}
			//处理事件
			for (auto w : s_WindowQue)
			{
				w->clear();							//先清屏
				w->event(&ev);						//处理窗口事件
				w->flush();	//显示界面
			}	
		}

		//调用游戏主循环
		for (auto w : s_WindowQue)
		{
			w->mainLoop();
		}
		//绘制
		for (auto w : s_WindowQue)
		{
			w->draw();
		}

		//获取经过了多少时间
		Uint32 frameTicks = elapsedTimer.elapsed();
		
		//如果帧提前完成
		if (frameTicks < (Uint32)s_ticksPerFrame)
		{
			s_currentFrameRate = 60.0;
			SDL_Delay((Uint32)s_ticksPerFrame - frameTicks);
		}
		else
		{
			s_currentFrameRate = 1000.0 / frameTicks;
		}
		SDL_Log("fps:%lf\n", s_currentFrameRate);
	}
	//退出后调用
	for (auto w : s_WindowQue)
	{
		w->quit();
	}
	return 0;
}

void SApplication::setFrameRate(double f)
{
	s_frameRate = f;
	s_ticksPerFrame = 1000.0 / s_frameRate;
}

double SApplication::currentFrameRate()
{
	return s_currentFrameRate;
}

void SApplication::addWindow(SWindow* window)
{
	s_WindowQue.push_back(window);
}

void SApplication::removeWindow(SWindow* window)
{
	auto it =  std::find(s_WindowQue.begin(), s_WindowQue.end(), window);
	if(it!=s_WindowQue.end())
		s_WindowQue.erase(it);
}

bool SApplication::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_Log("cannot init SDL：%s", SDL_GetError());
		return false;
	}
	setFrameRate(60.0);
	return true;
}

bool SApplication::close()
{
	SDL_Quit();
	return true;
}
