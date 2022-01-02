#pragma once
#include"Configure.h"
#include<queue>

class SObject;
class SEvent;

class SPostEvent
{
public:
	SObject* receiver;
	SEvent* event;
	inline SPostEvent()
		: receiver(nullptr), event(nullptr)
	{ }
	inline SPostEvent(SObject* r, SEvent* e)
		: receiver(r), event(e)
	{ }
};
using SPostEventQue = std::queue<SPostEvent>;

class SApplication
{
public:
	SApplication(int argc, char* argv[]);
	~SApplication();

	void processEvents();
	virtual bool notify(SObject* receiver, SEvent* event);

	static SApplication* instance();
	int exec();
	inline static SPostEventQue postEventQue;	//事件队列
private:
	bool handingEvent();

};

