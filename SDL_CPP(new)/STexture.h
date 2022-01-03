#pragma once
#include"SImage.h"
class SSurface;
class STexture : public SImage
{
public:
	STexture();
	STexture(const std::string& filename);
	int width()const override;
	int height()const override;
	SDL_Texture *sdlTexture()const override;

	//渲染到目标上
	bool render(int x,int y,int w = 0,int h = 0)const;
	bool render(const SRect& srcrect = SRect(), const SRect& dstrect = SRect())const;
private:
	SDL_Texture* _texture;
	int _width;
	int _height;
	void updateSize();	//更新纹理大小
};

