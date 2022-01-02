#pragma once
#include"Configure.h"
#include"SObject.h"
class SWindow : public SWidget
{
public:
	SWindow(int w, int h);
	~SWindow();

	//让任务栏图标闪烁,传入闪烁选项
	int flash(SDL_FlashOperation operation);
	//获取窗口标志
	Uint32 windowFlags();
	//未实现
	void setWindowFlags(Uint32 flags);
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
public:
	SDL_Renderer* renderer();
	operator SDL_Renderer* ();
	static SWindow* instance();
protected:
	void mousePressEvent(SMouseEvent* ev)override;
	void mouseReleaseEvent(SMouseEvent* ev)override;
	void mouseMoveEvent(SMouseEvent* ev)override;
	void paintEvent()override;
private:
	int _width;
	int _height;
	SDL_Window* _window;
	SDL_Renderer* _winRenderer;

};

