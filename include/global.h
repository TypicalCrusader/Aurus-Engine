#pragma once
#define SDL_MAIN_HANDLED
#ifdef _WIN32 //MSCV MY BELOATHED
	#include <windows.h>
	#include <SDL2/SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "map.h"
#include "misc.h"

enum Renderer
{
	RENDERER_SOFTWARE,
	RENDERER_OPENGL,
	RENDERER_VULCAN,
	RENDERER_DIRECTX
};

extern struct gamestate
{
	u8 CurrentState;
	u32 ResX;
	u32 ResY;
	u8 RefreshRate;
	u8 Renderer;
	bool isOnionOnioned;
	bool IsBlackFlagSailed;
	MainData *MainData
};


//GLOBAL DEFINES HERE
