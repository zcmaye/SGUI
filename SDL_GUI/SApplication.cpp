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

SObject* findLastChild(SObject* obj, int x, int y)
{
	SObject* returnObj = nullptr;
	for (auto child : obj->children())
	{
		auto* widget = dynamic_cast<SWidget*>(child);
		auto* parentWidget = dynamic_cast<SWidget*>(obj);
		SPoint leftTop =widget->mapFrom(parentWidget, SPoint(x, y));

		if (widget && widget->rect().contains(leftTop.x(), leftTop.y()))
		{
			if (!widget->children().empty())
				returnObj = findLastChild(widget,leftTop.x(), leftTop.y());
			if(returnObj == nullptr)
				return widget;
			else
				return returnObj;

		}

	}
	return returnObj;
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
			//鼠标事件是否在孩子上
			auto* widget = findLastChild(root, ev.button.x, ev.button.y);
			if (widget)
			{
				std::clog << ((SWidget*)widget) << std::endl;
				notify(widget, mouseEv);
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				notify(root, mouseEv);
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			//SApplication::eventQueue.insert(new SMouseEvent(SDL_MOUSEBUTTONUP, SPoint(ev.button.x, ev.button.y)));
			SEvent* mouseEv = new SMouseEvent(SDL_MOUSEBUTTONUP, SPoint(ev.button.x, ev.button.y));
			//鼠标事件是否在孩子上
			auto* widget = findLastChild(root, ev.button.x, ev.button.y);
			if (widget)
			{
				notify(widget, mouseEv);
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				notify(root, mouseEv);
			}
			break;
		}
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


