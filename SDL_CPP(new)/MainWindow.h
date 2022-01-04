#pragma once
#include"SWindow.h"
class MainWindow:public  SWindow
{
public:
	bool event(SDL_Event* ev)override;
	void draw()override;
};

