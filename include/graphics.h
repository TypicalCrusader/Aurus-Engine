#pragma once
#ifndef _MYHEADER_H_
#define _MYHEADER_H_
#endif
#pragma once

#include <SDL.h>
#include <SDL_image.h>

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;