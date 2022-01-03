#pragma once
#include<vector>
#include<iostream>
#include"SGeometry.h"
#include"SColor.h"

class SEvent;
class SMouseEvent;
class SSurface;
class SObject;

union SDL_Event;
typedef union SDL_Event SDL_Event;


using SObjectSet = std::vector<SObject*>;

class SObject
{
public:
	SObject(SObject* parent = nullptr);
	virtual ~SObject();
	SObject* parent();
	void setParent(SObject* parent);
	inline  const SObjectSet& children() const { return _children; }
	void clearChildern();

	
public:
	virtual bool  event(SDL_Event* ev);
protected:
	SObject* _parent;
	SObjectSet _children;
private:
	bool isFree = false;	//是否已经释放
};


