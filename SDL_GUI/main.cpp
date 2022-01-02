#if 1
#include"SObject.h"
#include"SApplication.h"
#include"SWindow.h"
#include"SWidget.h"
#include"SPushButton.h"
using namespace std;

int main222(int argc, char* argv[])
{
	SApplication a(argc, argv);

	SWidget w;
	auto* render = w.renderer();
	SDL_Texture* tet = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 250, 250);
	
	SDL_SetRenderTarget(render, tet);
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_Rect rect = { 0,0,250,250 };
	SDL_RenderFillRect(render, &rect);
	SDL_SetRenderTarget(render, nullptr);

	

	SDL_Texture* tet1 = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
	SDL_SetRenderTarget(render, tet1);
	SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	SDL_Rect rect1 = { 0,0,100,100 };
	SDL_RenderFillRect(render, &rect1);
	SDL_SetRenderTarget(render, nullptr);

	if (SDL_SetRenderTarget(render, tet) != 0)
	{
		SDL_Log("SetRenderTarget failed  %s\n", SDL_GetError());
	}

	SDL_RenderCopy(render, tet1, NULL, &rect1);
	SDL_SetRenderTarget(render, nullptr);


	SDL_RenderCopy(render, tet, NULL, &rect);
	SDL_RenderPresent(render);


	return a.exec();
}

int main(int argc, char* argv[])
{
	SApplication a(argc, argv);

	SWidget w;
	w.setBackgroundColor(SColor::White);
	//w.setWindowOpacity(0.5);
	w.show();

	SWidget* sw = new SWidget(&w);
	sw->setWindowTitle("sw");
	sw->setBackgroundColor(SColor::Red);
	sw->setWindowPos(20, 20);
	sw->setWindowSize(500, 250);
	sw->show();


	SWidget* sw1 = new SWidget(sw);
	sw1->setWindowTitle("sw1");
	sw1->setBackgroundColor(SColor::Green);
	sw1->setWindowPos(-10,20);
	sw1->setWindowSize(300, 50);

	sw1->show();


	SPushButton* pw = new SPushButton(sw1);
	pw->setWindowTitle("pw");
	pw->show();
	//delete sw;
	//std::cout << &w << " " << sw << " " << sw1 << " " << pw << std::endl;*/
	//std::cout 
	//	<< &w << " \n"
	//	<< sw->mapToParent(SPoint(0,0))<<" "<< w.windowPos() << " \n"
	//	<< sw1 << " \n" 
	//	<< pw->mapTo(sw,SPoint(0,0)) << std::endl;


	//SWidget w1;
	//w1.setBackgroundColor(SColor::White);
	////w.setWindowOpacity(0.5);
	//w1.show();



	return a.exec();
}
#else
#include<stdio.h>
int main()
{
	int c[4][5] = { 1,2,3,4,5,6,7,8,9 };
	int* cp[4];

	for (int k = 0; k < 4; k++)
	{
		cp[k] = c[k];
	}

	printf("%p %p %d\n", *(cp + 3), *(cp + 1) + 3, cp[2][3]);

	return 0;
}

#endif