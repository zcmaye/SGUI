#pragma once
#include"Configure.h"
#include<set>

class SObject;

class SWindow;
class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();
	int exec();

public:
	inline static std::set<SWindow*> s_WindowQue;	//窗口事件队列
	static void addWindow(SWindow* window);
	static void removeWindow(SWindow* window);
private:
	static bool init();
	static bool close();
};



