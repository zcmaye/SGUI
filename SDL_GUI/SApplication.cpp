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

void SApplication::processEvents()
{
	SPostEventQue& que = SApplication::postEventQue;
	if (que.empty())
		return;

	const SPostEvent& postEvent =  que.front();	//取出队头元素
	que.pop();	//从事件队列中移除
	notify(postEvent.receiver, postEvent.event);
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
/*
* 查找指定坐标所在的第一个控件，把obj的所有子控件都遍历一遍
*/
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
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>(findLastChild(root, ev.button.x, ev.button.y));
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			if (widget)
			{
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));
				SApplication::postEventQue.push(SPostEvent(widget, new SMouseEvent(SDL_MOUSEBUTTONDOWN, localPos, globalPos)));
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				SApplication::postEventQue.push(SPostEvent(root, new SMouseEvent(SDL_MOUSEBUTTONDOWN, globalPos, globalPos)));
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>( findLastChild(root, ev.button.x, ev.button.y));
			if (widget)
			{
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));		
				SApplication::postEventQue.push(SPostEvent(widget, new SMouseEvent(SDL_MOUSEBUTTONUP, localPos, globalPos)));
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				SApplication::postEventQue.push(SPostEvent(root, new SMouseEvent(SDL_MOUSEBUTTONUP, globalPos, globalPos)));
			}
			break;
		}
		case SDL_MOUSEMOTION:	//鼠标移动
		{
			SPoint globalPos = SPoint(ev.button.x, ev.button.y);
			//鼠标事件是否在孩子上
			auto* widget = dynamic_cast<SWidget*>( findLastChild(root, ev.motion.x, ev.motion.y));
			if (widget)
			{
				SPoint localPos = widget->mapFrom((SWidget*)root, SPoint(ev.button.x, ev.button.y));
				SApplication::postEventQue.push(SPostEvent(widget, new SMouseEvent(SDL_MOUSEMOTION, localPos, globalPos)));
				//鼠标进入和离开控件事件处理
			}
			//没有在任何孩子身上，就传给主窗口
			else
			{
				SApplication::postEventQue.push(SPostEvent(root, new SMouseEvent(SDL_MOUSEMOTION, globalPos, globalPos)));
			}

			break;
		}
		case SDL_SYSWMEVENT:
			std::clog << "SDL_SYSWMEVENT" << std::endl;
			break;
		case SDL_WINDOWEVENT:
			std::clog << "SDL_WINDOWEVENT"<<ev.syswm.msg << std::endl;
			break;
		default:
			break;
		}
		//重绘所有控件
		auto postEvent = SPostEvent(root, new SEvent(SDL_EventType(SEvent::Paint)));
		SApplication::postEventQue.push(postEvent);
	}

	while (!SApplication::postEventQue.empty())
	{
		processEvents();
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


