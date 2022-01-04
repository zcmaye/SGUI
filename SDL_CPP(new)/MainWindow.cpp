#include "MainWindow.h"

bool MainWindow::event(SDL_Event* ev)
{

	return false;
}

void MainWindow::draw()
{
	//SDL_Log("draw");
	SDL_Delay(rand()%10+10);
}
