#pragma once
#include"SWidget.h"
class SPushButton  :public SWidget
{
public:
	SPushButton(SWidget* parent = nullptr);
	void setColor(const SColor& bkcolor, const SColor& hovercolor);
	void enterEvent(SDL_Event* ev)override;
	void leaveEvent(SDL_Event* ev)override;
	void paintEvent(SDL_Event* ev)override;
protected:
	SColor _bkColor;
	SColor _hoverColor;	//Êó±êÐüÍ£ÑÕÉ«
};

