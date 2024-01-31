#include <SDL.h>
#include <SDL_image.h>
#include "../include/types.h"
#include <string.h>



int Load_Texture_path(char File_gfx_folder[], char File_file_name[], char File_extension[]) {

	char File_name_1[] = "./data/gfx/";
	char File_path[UINT8_MAX];
	strcpy_s(File_path, sizeof(File_name_1), File_name_1);
	strcpy_s(File_path, sizeof(File_gfx_folder), File_gfx_folder);
	strcpy_s(File_path, sizeof(File_file_name), File_file_name);
	strcpy_s(File_path, 1, ".");
	strcpy_s(File_path, sizeof(File_extension), File_extension);


	return File_path;
};

int Load_texture_from_path(SDL_Surface* Image, SDL_Renderer* Renderer, SDL_Texture* Texture, char File_path[])
{
	SDL_RWops* RW_ops;
	RW_ops = SDL_RWFromFile(File_path, "r");

	return 0;
};
