#pragma once
#include<vector>
#include<iostream>
#include"SGeometry.h"

class SEvent;
class SSurface;
class SObject;

using SObjectSet = std::vector<SObject*>;

class SObject
{
public:
	SObject(SObject* parent = nullptr);
	virtual ~SObject();
	void setParent(SObject* parent);
	inline  const SObjectSet& children() const { return _children; }
	void clearChildern();
public:
	virtual bool  event(SEvent* ev);
protected:
	SObject* _parent;
	std::vector<SObject*> _children;
private:
	bool isFree = false;	//是否已经释放
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
		std::cout << "~SWidget destroy "<< _title << std::endl;
	}

	//获取窗口坐标
	SPoint windowPos();
	void setWindowPos(int x, int y);
	//获取窗口大小
	SSize windowSize();
	void setWindowSize(int w, int h);
	//获取窗口标题
	std::string windowTitle();
	void setWindowTitle(const std::string& title);
	//设置窗口图标
	SSurface* windowIcon();
	void setWindowIcon(SSurface* icon);
	//隐藏窗口
	void hide();
	//显示窗口
	void show();
	//提升窗口层级
	void raise();
	//设置不透明度
	float windowOpacity();
	void setWindowOpacity(float opacity);
	//获取窗口几何区域
	SRect frameGeometry();

	//更新窗口
	void  update();
protected:
	bool  event(SEvent* ev) override;
	void paintEvent();
private:
	std::string _title;
	SPoint		_pos;
	SSize		_size;
	SSurface*	_icon;
	float		_opacity;

	bool		_isHiden;	//是隐藏的？
	int			_z;			//层级

};
