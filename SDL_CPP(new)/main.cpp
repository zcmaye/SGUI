#include"MainWindow.h"
#include"SApplication.h"
int main(int argc,char*argv[])
{
	SApplication a(argc, argv);
	MainWindow w;

	return a.exec();
}