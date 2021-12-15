#include"SObject.h"
#include"SApplication.h"
#include"SWindow.h"

int main(int argc,char*argv[])
{
	SApplication a(argc, argv);
	SWindow w(640,480);


	SWidget* sw = new SWidget(&w);
	sw->setWindowTitle("sw");
	sw->show();

	SWidget* sw1 = new SWidget(&w);
	sw1->setWindowTitle("sw1");
	sw1->setWindowPos(0, 300);
	sw1->show();

	//SWidget* pw = new SWidget(sw1);
	//pw->setWindowTitle("pw");
	//pw->show();

	std::cout << &w << " " << sw << " " << sw1 << " " /*<< pw*/ << std::endl;

	return a.exec();
}