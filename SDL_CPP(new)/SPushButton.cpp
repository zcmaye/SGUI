#include "SPushButton.h"

SPushButton::SPushButton(SWidget* parent)
	:SWidget(parent)
	,_hoverColor(SColor::DarkGray)
	,_bkColor(SColor::Gray)
{
	setBackgroundColor(SColor::Gray);
	setWindowSize(100, 25);
	setWindowTitle("SPushButton");
}

void SPushButton::setColor(const SColor& bkcolor, const SColor& hovercolor)
{
	_bkColor = bkcolor;
	_hoverColor = hovercolor;
}

void SPushButton::enterEvent(SDL_Event* ev)
{
	
	std::clog << "pushbutton enter" << std::endl;
	setBackgroundColor(_hoverColor);
}

void SPushButton::leaveEvent(SDL_Event* ev)
{
	std::clog << "pushbutton leave" << std::endl;
	setBackgroundColor(_bkColor);
}

void SPushButton::paintEvent(SDL_Event* ev)
{
	SWidget::paintEvent(ev);
}
