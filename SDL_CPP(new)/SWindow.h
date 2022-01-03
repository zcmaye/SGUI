#pragma once
#include"Configure.h"
#include"SColor.h"

class SWindow
{
public:
	SWindow(int w, int h);
	~SWindow();

	//让任务栏图标闪烁,传入闪烁选项
	int alert(SDL_FlashOperation operation);
	//获取窗口标志
	Uint32 windowFlags();
	//未实现
	void setWindowFlags(Uint32 flags);
	//获取窗口坐标
	SPoint windowPos();
	void move(int x, int y);
	//获取窗口大小
	SSize size();
	void setSize(int w, int h);
	//获取窗口标题
	std::string windowTitle();
	void setWindowTitle(const std::string& title);
	//设置窗口图标
	void setWindowIcon(SDL_Surface* icon);
	//隐藏窗口
	void hide();
	//显示窗口
	void show();
	//最大化显示
	void showMaximize();
	//最小化显示
	void showMinimize();
	//正常显示
	void showNormal();
	//全屏显示
	void showFullscreen();
	//提升窗口层级
	void raise();
	//设置不透明度
	void setWindowOpacity(float opacity);
	float windowOpacity();
	//设置颜色
	void setBackgroundColor(SColor color);
public:
	SDL_Renderer* renderer();
	void clear() const;			//用设置的颜色填充窗口
	void flush() const;			//刷新窗口
	virtual bool event(SDL_Event* ev);
	static SWindow* instance();

private:
	int _width;
	int _height;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SColor  _bkColor;
};

