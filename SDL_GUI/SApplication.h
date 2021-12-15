#pragma once
#include"Configure.h"
#include<set>

class SObject;
class SEvent;

class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();

	virtual bool notify(SObject* receiver, SEvent* event);

	static SApplication* instance();
	int exec();
	inline static std::set<SEvent*> eventQueue;
private:
	bool handingEvent();
};

