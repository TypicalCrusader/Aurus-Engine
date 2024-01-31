#pragma once

#include <SDL.h>
#include <SDL_image.h>

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;