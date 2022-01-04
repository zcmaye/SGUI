#pragma once
#include"Configure.h"
#include<vector>

class SObject;

class SWindow;
class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();
	static int exec();
	static void setFrameRate(double f);	//设置帧率
	static double currentFrameRate();

public:
	inline static std::vector<SWindow*> s_WindowQue;	//窗口事件队列
	static void addWindow(SWindow* window);
	static void removeWindow(SWindow* window);
private:
	static bool init();
	static bool close();

	inline static double s_ticksPerFrame;			//每帧时间
	inline static double s_frameRate = 0;			//帧率
	inline static double s_currentFrameRate = 0;	//实际帧率
};



