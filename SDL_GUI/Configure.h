#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"SGeometry.h"

#ifdef SDL_IMAGE_H_
#define HAVE_IMAGE	//��SDL_image
#endif 

#ifdef SDL_TTF_H_
#define HAVE_TTF	//��SDL_ttf
#endif 

#ifdef SDL_MIXER_H_
#define HAVE_MIXER	//��SDL_mixer
#endif 


