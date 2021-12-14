#pragma once
#include"Configure.h"
class SWindow
{
public:
	SWindow(int w, int h);
	~SWindow();

	//��������ͼ����˸,������˸ѡ��
	int flash(SDL_FlashOperation operation);
	//��ȡ���ڱ�־
	Uint32 windowFlags();
	//δʵ��
	void setWindowFlags(Uint32 flags);
	//��ȡ��������
	SPoint windowPos();
	void setWindowPos(int x, int y);
	//��ȡ���ڴ�С
	SSize windowSize();
	void setWindowSize(int w, int h);
	//��ȡ���ڱ���
	std::string windowTitle();
	void setWindowTitle(const std::string& title);
	//���ô���ͼ��
	void setWindowIcon(SDL_Surface* icon);
	//���ش���
	void hide();
	//��ʾ����
	void show();
	//�����ʾ
	void showMaximize();
	//��С����ʾ
	void showMinimize();
	//������ʾ
	void showNormal();
	//ȫ����ʾ
	void showFullscreen();
	//�������ڲ㼶
	void raise();
	//���ò�͸����
	void setWindowOpacity(float opacity);
	float windowOpacity();

private:
	int _width;
	int _height;
	SDL_Window* _window;
	SDL_Renderer* _winRenderer;
};

