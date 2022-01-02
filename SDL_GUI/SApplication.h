#pragma once
#include"Configure.h"
#include<set>

class SObject;

class SWidget;
class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();
	int exec();

public:
	inline static std::set<SWidget*> s_WindowQue;	//窗口事件队列
	static void addWindow(SWidget* window);
	static void removeWindow(SWidget* window);
	static bool destroyAllWindows();
private:
	//判断所有窗口是否隐藏，根据这个判断应用程序是否退出
	static bool  allWindowIsHidden();
	static bool init();
	static bool close();
};



