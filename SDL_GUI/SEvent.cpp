#include "SEvent.h"
/*@ 事件基类*/
SEvent::SEvent(int type)
	:_type(type)
	,_accepted(true)
{
}

SEvent::~SEvent()
{
	std::cout << "~SEvent "<<type() << std::endl;
}

int SEvent::type()
{
	return _type;
}

void SEvent::accept()
{
	setAccepted(true);
}

void SEvent::ignore()
{
	setAccepted(false);
}

bool SEvent::isAccepted() const
{
	return _accepted;
}

void SEvent::setAccepted(bool accepted)
{
	_accepted = accepted;
}

std::ostream& operator<<(std::ostream& out, const SEvent* const ev)
{
	out << "SEvent(" << ev->_type <<")";
	return out;
}

/*@ 鼠标事件*/
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
