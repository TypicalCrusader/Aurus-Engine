#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <stdio.h>
#include "types.h"
#include "map.h"
#include "char.h"
#include "misc.h"


char* Load_File_path( char File_folder_path[],  char File_file_name[], char File_extension[]);
int Load_texture_from_path(SDL_Surface* Image, SDL_Renderer* Renderer, SDL_Texture* Texture, char File_path[]);
int Load_Wav_from_path();
int Parse_map_XML_values(xmlDocPtr doc, xmlNodePtr cur, char childname[]);
char Get_Properties_Value(xmlDocPtr doc, xmlNodePtr cur, char propertyname[]);
int* Load_Map_data_from_path( char *chapterID, char *chaptermapid);