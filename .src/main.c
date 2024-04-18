/*
MIT License

Copyright (c) 2024 TypicalCrusader

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "../include/global.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	int* MapStructPtr = Load_Map_data_from_path("1","1");
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
