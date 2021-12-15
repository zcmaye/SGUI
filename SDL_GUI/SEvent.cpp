#include "SEvent.h"

SEvent::SEvent(int type)
	:_type(type)
{
}

SEvent::~SEvent()
{
}

int SEvent::type()
{
	return _type;
}

SMouseEvent::SMouseEvent(SDL_EventType type, const SPoint& localPos)
	:SEvent(type)
	, _pos(localPos)
{
}

SMouseEvent::~SMouseEvent()
{
}

SPoint SMouseEvent::pos()
{
	return _pos;
}
