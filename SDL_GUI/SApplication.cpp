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
			//SEvent* mouseEv = new SMouseEvent(SDL_MOUSEBUTTONDOWN, SPoint(ev.button.x, ev.button.y));
			//SApplication::eventQueue.insert(new SMouseEvent(SDL_MOUSEBUTTONDOWN, SPoint(ev.button.x, ev.button.y)));
			//SDL_Log("mousepos %d %d\n", ev.button.x, ev.button.y);
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>(findLastChild(root, ev.button.x, ev.button.y));
			if (widget)
			{
				//std::clog << ((SWidget*)widget) << std::endl;
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));
				notify(widget, new SMouseEvent(SDL_MOUSEBUTTONDOWN, localPos,globalPos));
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				notify(root, new SMouseEvent(SDL_MOUSEBUTTONDOWN, globalPos, globalPos));
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			//SApplication::eventQueue.insert(new SMouseEvent(SDL_MOUSEBUTTONUP, SPoint(ev.button.x, ev.button.y)));
			//SEvent* mouseEv = new SMouseEvent(SDL_MOUSEBUTTONUP, SPoint(ev.button.x, ev.button.y));
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>( findLastChild(root, ev.button.x, ev.button.y));
			if (widget)
			{
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));		
				notify(widget, new SMouseEvent(SDL_MOUSEBUTTONUP, localPos,globalPos));
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				notify(root, new SMouseEvent(SDL_MOUSEBUTTONUP, globalPos, globalPos));
			}
			break;
		}
		case SDL_MOUSEMOTION:	//鼠标移动
		{
			//SEvent* mouseEv = new SMouseEvent(SDL_MOUSEMOTION, SPoint(ev.motion.x, ev.motion.y));
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>( findLastChild(root, ev.motion.x, ev.motion.y));
			if (widget)
			{
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));
				notify(widget, new SMouseEvent(SDL_MOUSEMOTION, localPos, globalPos));
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				notify(root, new SMouseEvent(SDL_MOUSEMOTION, globalPos, globalPos));
			}
			break;
		}
		default:
			break;
		}
		//重绘所以有控件
		notify(root, new SMouseEvent(SDL_EventType(SEvent::Paint), SPoint(), SPoint()));
		SDL_RenderPresent(SWindow::instance()->renderer());;
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


