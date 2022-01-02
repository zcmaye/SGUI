#include "SPushButton.h"

SPushButton::SPushButton(SWidget* parent)
	:SWidget(parent)
	,_hoverColor(SColor::DarkGray)
	,_bkColor(SColor::Gray)
{
	setBackgroundColor(SColor::Gray);
	setWindowSize(100, 25);
	
}

void SPushButton::setColor(const SColor& bkcolor, const SColor& hovercolor)
{
	_bkColor = bkcolor;
	_hoverColor = hovercolor;
}

void SPushButton::enterEvent(SEvent* ev)
{
	
	std::clog << "pushbutton enter" << std::endl;
	setBackgroundColor(_hoverColor);
}

void SPushButton::leaveEvent(SEvent* ev)
{
	std::clog << "pushbutton leave" << std::endl;
	setBackgroundColor(_bkColor);
}

void SPushButton::paintEvent()
{
	SWidget::paintEvent();
}
