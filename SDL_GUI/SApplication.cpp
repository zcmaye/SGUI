#include "SApplication.h"
#include"SEvent.h"
#include"SObject.h"
#include"SWindow.h"
static SApplication* g_instance = nullptr;

SApplication::SApplication(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1 ||
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
	{
		return;
	}
	g_instance = this;
}

SApplication::~SApplication()
{

}

bool SApplication::notify(SObject* receiver, SEvent* event)
{
	receiver->event(event);
	return false;
}

SApplication* SApplication::instance()
{
	return g_instance;
}

bool SApplication::handingEvent()
{
	static SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		SObject* root = SWindow::instance();
		switch (ev.type)
		{
		case SDL_QUIT:
			return true;
		case SDL_MOUSEBUTTONDOWN:
		{
			SEvent* mouseEv = new SMouseEvent(SDL_MOUSEBUTTONDOWN, SPoint(ev.button.x, ev.button.y));
			//SApplication::eventQueue.insert(new SMouseEvent(SDL_MOUSEBUTTONDOWN, SPoint(ev.button.x, ev.button.y)));
			//SDL_Log("mousepos %d %d\n", ev.button.x, ev.button.y);
			bool isInChild = false;	//鼠标事件是否在孩子上
			for (auto child : SWindow::instance()->children())
			{
				auto* widget = dynamic_cast<SWidget*>(child);
				if (widget && widget->frameGeometry().contains(ev.button.x, ev.button.y))
				{
					notify(child, mouseEv);
					isInChild = true;
				}		
				//SRect r = widget->frameGeometry();
				//SDL_Log("%d %d %d %d\n", r.x1(), r.y1(), r.x2(), r.y2());			
			}
			//没有在任何孩子身上，就传给主窗口
			if (!isInChild)
			{
				notify(root, mouseEv);
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
			SApplication::eventQueue.insert(new SMouseEvent(SDL_MOUSEBUTTONUP, SPoint(ev.button.x, ev.button.y)));
			break;
		default:
			break;
		}
		//SDL_Log("%p\n", g_rootObj);
	}
	return false;
}
int SApplication::exec()
{
	int isDone = false;
	while (!isDone)
	{
		isDone = handingEvent();
	}
    return 0;
}


