#pragma once
#include<SDL_events.h>
#include"SGeometry.h"
#include<iostream>
class SPoint;

class SEvent
{
public:
	enum Type
	{
		Paint = SDL_USEREVENT,	//绘图事件
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
	SMouseEvent(SDL_EventType type, const SPoint& localPos);
	~SMouseEvent();
	SPoint pos();
private:
	SPoint _pos;
};