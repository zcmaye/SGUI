#pragma once
#include<SDL_events.h>
#include"SGeometry.h"
class SPoint;

class SEvent
{
public:
	enum Type
	{
		Paint = SDL_USEREVENT,	//��ͼ�¼�
	};
public:
	SEvent(int type);
	~SEvent();
	virtual int type();
private:
	int _type;
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