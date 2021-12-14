#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"SGeometry.h"

#ifdef SDL_IMAGE_H_
#define HAVE_IMAGE	//ÓÐSDL_image
#endif 

#ifdef SDL_TTF_H_
#define HAVE_TTF	//ÓÐSDL_ttf
#endif 

#ifdef SDL_MIXER_H_
#define HAVE_MIXER	//ÓÐSDL_mixer
#endif 


