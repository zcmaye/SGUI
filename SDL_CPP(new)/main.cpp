#if 1
#include"SApplication.h"
#include"SWindow.h"
#include"STexture.h"
using namespace std;


int main(int argc, char* argv[])
{
	SApplication a(argc, argv);

	SWindow w(640,480);

	STexture tet("./assets/images/test.bmp");
	STexture tet1("./assets/images/test.png");
	//tet.render(SRect(),SRect(0,0,200,200));
	tet1.render(20,20,50,100);


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