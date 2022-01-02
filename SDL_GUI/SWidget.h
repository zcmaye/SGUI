#pragma once
#include"SObject.h"
class SWidget :public SObject
{
public:
	SWidget(SObject* parent = nullptr);
	virtual ~SWidget();

	//获取窗口坐标
	SPoint windowPos()const;
	void setWindowPos(int x, int y);
	void setWindowPos(const SPoint& pos);
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
	bool isHidden()const;
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
	SWidget* topLevelParentWidget();	//顶层父窗口
public:
	friend std::ostream& operator<<(std::ostream& out, const SWidget& widget);
	friend std::ostream& operator<<(std::ostream& out, const SWidget* const widget);
	
	bool  event(SDL_Event* ev) override;
	inline SDL_Window* sdlWindow() { return m_Window; }
	void clear()const;
	inline SDL_Renderer* renderer()const { return m_Renderer; };
protected:
	virtual void paintEvent(SDL_Event* ev);
	virtual void mousePressEvent(SDL_MouseButtonEvent* ev);
	virtual void mouseReleaseEvent(SDL_MouseButtonEvent* ev);
	virtual void mouseMoveEvent(SDL_MouseMotionEvent* ev);
	virtual void wheelEvent(SDL_MouseWheelEvent* ev);
	virtual void enterEvent(SDL_Event* ev);
	virtual void leaveEvent(SDL_Event* ev);
	virtual void closeEvent(SDL_Event* ev);
	virtual void showEvent(SDL_Event* ev);
	virtual void hiddenEvent(SDL_Event* ev);
	virtual void resizeEvent(SDL_Event* ev);
	virtual void moveEvent(SDL_Event* ev);
	virtual void changeEvent(SDL_Event* ev);
protected:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	struct WindowId
	{
		int mainId = -1;			//root窗口id
		int selfId = -1;			//自己的窗口id
		inline operator int() { return mainId; }
	}m_WinId;

	std::string _text;
	SRect		_rect;		//窗口矩形
	SRect		_rrect;		//多个父子窗口堆叠，实际绘制的矩形区域
	SSurface* _icon;
	float		_opacity;

	bool		_isHiden;	//是隐藏的？
	int			_z;			//层级	

	SColor		_bkColor;	//背景颜色

	bool		m_isPress;	//鼠标左键是否按下
	SPoint		m_begPos;

private:
	int m_mouseFocus : 1 = 0;		//有鼠标焦点
	int m_keyboardFocus : 1 = 0;	//有键盘焦点
};

