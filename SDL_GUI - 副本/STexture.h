#pragma once
#include"SImage.h"
class STexture : public SImage
{
public:
	STexture();
	int width()const override;
	int height()const override;
	SDL_Texture *sdlTexture()const override;

private:
	SDL_Texture* _texture;
};

