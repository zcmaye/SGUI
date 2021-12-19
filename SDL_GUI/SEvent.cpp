#include "SEvent.h"
/*@ 事件基类*/
SEvent::SEvent(int type)
	:_type(type)
	,_accepted(true)
{
}

SEvent::~SEvent()
{
	//std::cout << "~SEvent "<<type() << std::endl;
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
SMouseEvent::SMouseEvent(SDL_EventType type, const SPoint& localPos, const SPoint& globalPos)
	:SEvent(type)
	, _pos(localPos)
	, _globalPos(globalPos)
{

}

SMouseEvent::SMouseEvent(SDL_EventType type, const SPoint& localPos, const SPoint& globalPos, SGUI::MouseButton button, SGUI::MouseButtons buttons)
	:SEvent(type)
	, _pos(localPos)
	, _globalPos(globalPos)
	,m_button(button)
	, m_mouseState(buttons)
{

}

SMouseEvent::~SMouseEvent()
{
}

SPoint SMouseEvent::pos()
{
	return _pos;
}

SPoint SMouseEvent::globalPos()
{
	return _globalPos;
}



SGUI::MouseButton SMouseEvent::getButton(int button)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		return SGUI::MouseButton::LeftButton;
	case SDL_BUTTON_RIGHT:
		return SGUI::MouseButton::RightButton;
	case SDL_BUTTON_MIDDLE:
		return SGUI::MouseButton::MidButton;
	default:
		return SGUI::MouseButton::NoButton;
	}
}
