#include "SObject.h"
#include"SApplication.h"
#include"SWindow.h"
using namespace std;
/*@ SObject*/

SObject::SObject(SObject* parent)
	:_parent(parent)
{
	if (_parent)
		_parent->_children.push_back(this);	//把this设为父对象的孩子


	std::cout << "SObject init" << std::endl;
}
SObject::~SObject()
{
	//1,先释放孩子
	if(!_children.empty())
		this->clearChildern();

	if (_parent)
	{
		//把this从原来的父对象的孩子列表中移除
		auto it = std::find(_parent->_children.begin(), _parent->_children.end(),this);
		if (it != _parent->_children.end())
		{
			_parent->_children.erase(it);
		}
	}

	std::cout << "~SObject destroy" << std::endl;
}
SObject* SObject::parent()
{
	return _parent;
}
void SObject::setParent(SObject* parent)
{
	if (_parent)
	{
		//把this从原来的父对象的孩子列表中移除
		auto it = std::find(_parent->_children.begin(), _parent->_children.end(), this);
		//auto it = _parent->_children.find(this);
		if (it != _parent->_children.end())
		{
			_parent->_children.erase(it);
		}
	}
	//设置新的父对象，并添加进孩子列表
	_parent = parent;
	if (_parent)
		_parent->_children.push_back(this);
}

void SObject::clearChildern()
{
	//1,先释放孩子
	for (auto& child : _children)
	{
		delete child;
		child = nullptr;
	}
	//2,清空
	_children.clear();
}

bool SObject::event(SDL_Event* ev)
{
	SDL_Log(" SObject  event\n");
	return false;
}

