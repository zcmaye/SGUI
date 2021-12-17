#if 1
#include"SObject.h"
#include"SApplication.h"
#include"SWindow.h"
using namespace std;
int main(int argc, char* argv[])
{
	SApplication a(argc, argv);
	SWindow w(640, 480);
	w.setBackgroundColor(SColor::White);
	//w.setWindowOpacity(0.5);
	w.show();

	SWidget* sw = new SWidget(&w);
	sw->setWindowTitle("sw");
	sw->setBackgroundColor(SColor::Red);
	sw->setWindowPos(20, 20);
	sw->setWindowSize(250, 250);
	sw->show();


	/*SWidget* sw1 = new SWidget(sw);
	sw1->setWindowTitle("sw1");
	sw1->setWindowPos(50,50);
	sw1->setWindowSize(250, 250);
	sw1->setBackgroundColor(SColor::Green);
	sw1->show();

	SWidget* pw = new SWidget(sw1);
	pw->setWindowTitle("pw");
	pw->setWindowPos(-10, -10);
	pw->setWindowSize(50, 60);
	pw->setBackgroundColor(SColor::Blue);
	pw->show();
	//delete sw;
	std::cout << &w << " " << sw << " " << sw1 << " " << pw << std::endl;*/
	//std::cout 
	//	<< &w << " \n"
	//	<< sw->mapToParent(SPoint(0,0))<<" "<< w.windowPos() << " \n"
	//	<< sw1 << " \n" 
	//	<< pw->mapTo(sw,SPoint(0,0)) << std::endl;


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