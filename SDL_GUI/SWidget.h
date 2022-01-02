#pragma once
#include"SObject.h"
class SWidget :public SObject
{
public:
	SWidget(SObject* parent = nullptr);
	virtual ~SWidget();

	//��ȡ��������
	SPoint windowPos()const;
	void setWindowPos(int x, int y);
	void setWindowPos(const SPoint& pos);
	void move(int x, int y);
	void move(const SPoint& pos);
	//��ȡ���ڴ�С
	SSize windowSize()const;
	void setWindowSize(int w, int h);
	//��ȡ���ڱ���
	std::string windowTitle()const;
	void setWindowTitle(const std::string& title);
	//���ô���ͼ��
	SSurface* windowIcon()const;
	void setWindowIcon(SSurface* icon);
	//���ش���
	void hide();
	bool isHidden()const;
	//��ʾ����
	void show();
	//�������ڲ㼶
	void raise();
	//���ò�͸����
	float windowOpacity()const;
	void setWindowOpacity(float opacity);
	//��ȡ���ڼ�������
	SRect frameGeometry()const;
	SRect rect()const;

	//���´���
	void  update();
	//������ɫ
	void setBackgroundColor(SColor c = SColor::White);

	SWidget* parentWidget()const;

	SPoint mapToGlobal(const SPoint&) const;
	SPoint mapFromGlobal(const SPoint&) const;
	SPoint mapToParent(const SPoint&) const;
	SPoint mapFromParent(const SPoint&) const;
	SPoint mapTo(const SWidget*, const SPoint&) const;
	SPoint mapFrom(const SWidget*, const SPoint&) const;
	SWidget* topLevelParentWidget();	//���㸸����
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
		int mainId = -1;			//root����id
		int selfId = -1;			//�Լ��Ĵ���id
		inline operator int() { return mainId; }
	}m_WinId;

	std::string _text;
	SRect		_rect;		//���ھ���
	SRect		_rrect;		//������Ӵ��ڶѵ���ʵ�ʻ��Ƶľ�������
	SSurface* _icon;
	float		_opacity;

	bool		_isHiden;	//�����صģ�
	int			_z;			//�㼶	

	SColor		_bkColor;	//������ɫ

	bool		m_isPress;	//�������Ƿ���
	SPoint		m_begPos;

private:
	int m_mouseFocus : 1 = 0;		//����꽹��
	int m_keyboardFocus : 1 = 0;	//�м��̽���
};

