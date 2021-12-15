#pragma once
#include"Configure.h"
#include<set>
struct SEvent
{
	int type;
};
class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();
	static SApplication* instance();
	static int exec();
	inline static std::set<SEvent*> eventQueue;
};

