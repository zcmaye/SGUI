#include"Test.h"
#include"SApplication.h"
#include"SWindow.h"

int main(int argc,char*argv[])
{
	SApplication a(argc, argv);
	SWindow w(640,480);


	w.show();
	return a.exec();
}