#pragma once
typedef struct SDL_Surface SDL_Surface;
#include<string>
#include"SImage.h"
class SSurface : public SImage
{
public:
	SSurface();
	SSurface(int w,int h);
	SSurface(const std::string& file);
	SSurface(SDL_Surface* _surface);
	~SSurface();
	//���ú�����ȡsurface
	SDL_Surface* surface();
	//����ת������ ��SSurfaceת����SDL_Surface*
	operator SDL_Surface* ();

	int width()const override;
	int height()const override;
	SDL_Texture* sdlTexture()const override;

	bool lock()const;
	void unlock()const;

	//���ùؼ���ɫ�����Ƶ�ʱ�򲻻����(͸��)
	bool setColorKey(const SColor& color) const;

	//��ָ����ɫ���ָ����������
	bool fillRect(const SRect& rect, const SColor& color)const;

		
private:
	SDL_Surface* _surface;
};

