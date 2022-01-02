#pragma once
#include<vector>
#include<iostream>
#include"SGeometry.h"
#include"SColor.h"

class SEvent;
class SMouseEvent;
class SSurface;
class SObject;

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
	virtual bool  event(SEvent* ev);
protected:
	SObject* _parent;
	std::vector<SObject*> _children;
private:
	bool isFree = false;	//是否已经释放
};


struct SWidget:public SObject
{
	SWidget(SObject* parent = nullptr);
	virtual ~SWidget();

	//获取窗口坐标
	SPoint windowPos()const;
	void setWindowPos(int x, int y);
	void setWindowPos(const SPoint&pos);
	void move(int x, int y);
	void move(const SPoint& pos);
	//获取窗口大小
	SSize windowSize()const;
	void setWindowSize(int w, int h);
	//获取窗口标题
	std::string windowTitle()const;
	void setWindowTitle(const std::string& title);
	//设置窗口图标
	SSurface* windowIcon()const;
	void setWindowIcon(SSurface* icon);
	//隐藏窗口
	void hide();
	//显示窗口
	void show();
	//提升窗口层级
	void raise();
	//设置不透明度
	float windowOpacity()const;
	void setWindowOpacity(float opacity);
	//获取窗口几何区域
	SRect frameGeometry()const;
	SRect rect()const;

	//更新窗口
	void  update();
	//设置颜色
	void setBackgroundColor(SColor c = SColor::White);

	SWidget* parentWidget()const;

	SPoint mapToGlobal(const SPoint&) const;
	SPoint mapFromGlobal(const SPoint&) const;
	SPoint mapToParent(const SPoint&) const;
	SPoint mapFromParent(const SPoint&) const;
	SPoint mapTo(const SWidget*, const SPoint&) const;
	SPoint mapFrom(const SWidget*, const SPoint&) const;
public:
	friend std::ostream& operator<<(std::ostream& out, const SWidget& widget);
	friend std::ostream& operator<<(std::ostream& out, const SWidget*const widget);
protected:
	bool  event(SEvent* ev) override;
	virtual void paintEvent();
	virtual void mousePressEvent(SMouseEvent*ev);
	virtual void mouseReleaseEvent(SMouseEvent* ev);
	virtual void mouseMoveEvent(SMouseEvent* ev);
	virtual void enterEvent(SEvent* ev);
	virtual void leaveEvent(SEvent* ev);
protected:
	std::string _text;
	SRect		_rect;		//窗口矩形
	SRect		_rrect;		//多个父子窗口堆叠，实际绘制的矩形区域
	SSurface*	_icon;
	float		_opacity;

	bool		_isHiden;	//是隐藏的？
	int			_z;			//层级	

	SColor		_bkColor;	//背景颜色

	bool		m_isPress;	//鼠标左键是否按下
	SPoint		m_begPos;
};
