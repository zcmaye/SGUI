#pragma once
#include<set>
#include<iostream>
struct SObject
{
	SObject(SObject* parent = nullptr)
		:_parent(parent)
	{
		if(_parent)
			_parent->_children.insert(this);	//把this设为父对象的孩子
		std::cout << "SObject init" << std::endl;
	}
	virtual ~SObject()
	{
		for (auto child : _children)
		{
			if (child)
			{
				delete child;
			}
		}
		std::cout << "~SObject destroy" << std::endl;
	}
	void setParent(SObject* parent)
	{
		if (_parent)
		{
			//把this从原来的父对象的孩子列表中移除
			auto it = _parent->_children.find(this);
			if (it != _parent->_children.end())
			{
				_parent->_children.erase(this);
			}
		}
		//设置新的父对象，并添加进孩子列表
		_parent = parent;
		if(_parent)
			_parent->_children.insert(this);
	}
	SObject* _parent;
	std::set<SObject*> _children;
};


struct SWidget:public SObject
{
	SWidget(SObject* parent = nullptr)
		:SObject(parent)
		,_size(150,25)
	{
		std::cout << "SWidget init" << std::endl;
	}
	virtual ~SWidget()
	{
		std::cout << "~SWidget destroy "<<_text << std::endl;
	}
	void setText(const std::string& text)
	{
		_text = text;
	}
private:
	std::string _text;
	SPoint _pos;
	SSize _size;
};
