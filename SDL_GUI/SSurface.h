#pragma once
typedef struct SDL_Surface SDL_Surface;
#include<string>
class SSurface
{
public:
	SSurface();
	SSurface(const std::string& file);
	SSurface(SDL_Surface* _surface);
	~SSurface();
	//调用函数获取surface
	SDL_Surface* surface();
	//类型转换重载 把SSurface转换成SDL_Surface*
	operator SDL_Surface* ();
private:
	SDL_Surface* _surface;
};

