#include "STexture.h"
#include"SWindow.h"



STexture::STexture()
    :_width(0)
    ,_height(0)
    ,_texture(nullptr)
{
}
STexture::STexture(const std::string& filename)
    : STexture()
{
#ifdef HAVE_IMAGE
    SDL_Surface* sfc = IMG_Load(filename.c_str());
    if (sfc == nullptr)
    {
        return;
    }
#else
    SDL_Surface* sfc = SDL_LoadBMP(filename.c_str());
#endif
    if (!sfc)
    {
        SDL_Log("SSurface load failed\n");
        return;
    }
    _texture = SDL_CreateTextureFromSurface(SWindow::instance()->renderer(), sfc);
    if (_texture == nullptr)
    {
        SDL_Log("CreateTextureFromSurface failed\n");
    }
    SDL_FreeSurface(sfc);
    updateSize();
}
int STexture::width() const
{
    return _width;
}

int STexture::height() const
{
    return _height;
}

SDL_Texture* STexture::sdlTexture() const
{
    return _texture;
}

bool STexture::render(int x, int y,int w,int h) const
{
    SDL_Rect rect = { x,y };
    if (w == 0 || h == 0)
    {
        rect.w = _width;
        rect.h = _height;
    }
    else
    {
        rect.w = w;
        rect.h = h;
    }
 
    SDL_RenderCopy(SWindow::instance()->renderer(), _texture, NULL, &rect);
    return false;
}

bool STexture::render(const SRect& srcrect , const SRect& dstrect) const
{
    const SDL_Rect& srcr = srcrect.sdlRect();
    const SDL_Rect& dstr = dstrect.sdlRect();
    const SDL_Rect* psrcr = &srcr;
    const SDL_Rect* pdstr = &dstr;
    if (srcrect.isNull())
    {
        psrcr = NULL;
    }
    if (dstrect.isNull())
    {
        pdstr = NULL;
    }
    if (0 > SDL_RenderCopy(SWindow::instance()->renderer(), _texture, psrcr, pdstr))
    {
        return false;
    }
    return true;
}

void STexture::updateSize()
{
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}

