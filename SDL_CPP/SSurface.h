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
	//���ú�����ȡsurface
	SDL_Surface* surface();
	//����ת������ ��SSurfaceת����SDL_Surface*
	operator SDL_Surface* ();
private:
	SDL_Surface* _surface;
};

