#pragma once
#include<SDL_events.h>
#include"SGeometry.h"
#include<iostream>
class SPoint;
class SEvent;
class SObject;

namespace SGUI
{
	enum MouseButton
	{
		NoButton = 0x00000000,
		LeftButton=0x00000001,
		RightButton=0x00000002,
		MidButton = 0x00000004
	};
	using MouseButtons = enum MouseButton ;
}


class SEvent
{
public:
	enum Type
	{
		Paint = SDL_USEREVENT,	//绘图事件
		Enter,	
		Leave,
	};
public:
	SEvent(int type);
	virtual ~SEvent();
	virtual int type();

	//接受事件处理
	void accept();
	void ignore();
	bool isAccepted() const;
	void setAccepted(bool accepted);
public:
	friend std::ostream& operator<<(std::ostream& out, const SEvent* const ev);
private:
	int _type;			//事件类型
	bool _accepted;		//是否接受事件
};


class SMouseEvent:public  SEvent
{
public:
	SMouseEvent(SDL_EventType type, const SPoint& localPos, const SPoint& globalPos);
	SMouseEvent(SDL_EventType type, const SPoint& localPos, const SPoint& globalPos,SGUI::MouseButton button, SGUI::MouseButtons buttons);
	~SMouseEvent();
	SPoint pos();
	SPoint globalPos();

	inline SGUI::MouseButton button() const { return m_button; }
	inline SGUI::MouseButtons buttons() const { return m_mouseState; }

private:
	SPoint _pos;			//相对于接受事件的控件的坐标
	SPoint _globalPos;		//全局坐标

	SGUI::MouseButton m_button  = SGUI::NoButton;
	SGUI::MouseButtons m_mouseState = SGUI::NoButton;

	static SGUI::MouseButton getButton(int button);	//更具sdl的鼠标按键获取自定义的按键事件
};