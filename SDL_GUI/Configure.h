#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"SGeometry.h"

#define clog cout<<"[line "<<__LINE__<<"]:"

#ifdef SDL_IMAGE_H_
#define HAVE_IMAGE	//有SDL_image
#endif 

#ifdef SDL_TTF_H_
#define HAVE_TTF	//有SDL_ttf
#endif 

#ifdef SDL_MIXER_H_
#define HAVE_MIXER	//有SDL_mixer
#endif 


