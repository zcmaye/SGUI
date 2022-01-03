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
	//调用函数获取surface
	SDL_Surface* surface();
	//类型转换重载 把SSurface转换成SDL_Surface*
	operator SDL_Surface* ();

	int width()const override;
	int height()const override;
	SDL_Texture* sdlTexture()const override;

	bool lock()const;
	void unlock()const;

	//设置关键颜色，绘制的时候不会绘制(透明)
	bool setColorKey(const SColor& color) const;

	//用指定颜色填充指定矩形区域
	bool fillRect(const SRect& rect, const SColor& color)const;

		
private:
	SDL_Surface* _surface;
};

