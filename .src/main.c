#ifdef _WIN32
	#include <windows.h>
	#include <SDL.h>
	#include <SDL_image.h>
#endif
#ifndef _WIN32
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Renderer* renderer = NULL;
	bool quit = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) //no allocated memory means something brokey
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Aurus Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_INPUT_FOCUS);
	
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		if (window == NULL)
		{
			printf("window could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer == NULL)
		{
			printf("renderer could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		//windowSurface = SDL_GetWindowSurface(window);
		/*if (windowSurface == NULL)
		{
			printf("windowSurface could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}*/
		imageSurface = IMG_Load("./data/gfx/test.png"); //pure fucking cancer
		if (imageSurface == NULL)
		{
			printf("imageSurface could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}
		texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
		if (texture == NULL)
		{
			printf("texture could not initialize! SDL_Error: %s\n", SDL_GetError());
			return -1;
		}

		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000000);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(imageSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}