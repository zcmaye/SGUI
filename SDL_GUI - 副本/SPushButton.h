#pragma once
#include"SObject.h"
class SPushButton  :public SWidget
{
public:
	SPushButton(SWidget* parent = nullptr);
	void setColor(const SColor& bkcolor, const SColor& hovercolor);
	void enterEvent(SEvent* ev)override;
	void leaveEvent(SEvent* ev)override;
	void paintEvent()override;
protected:
	SColor _bkColor;
	SColor _hoverColor;	//Êó±êÐüÍ£ÑÕÉ«
};

