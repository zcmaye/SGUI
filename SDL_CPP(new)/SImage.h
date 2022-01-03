#pragma once
#include"SColor.h"
struct SDL_Texture;
typedef struct SDL_Texture SDL_Texture;
class SImage
{
public:
	SImage();
	virtual int width() const = 0;
	virtual int height()const = 0;
	virtual SDL_Texture* sdlTexture() const = 0;
};

