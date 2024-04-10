#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../include/types.h"
#include <string.h>
#include <libxml/xmlreader.h>
#include <stdio.h>
#include "../include/map.h"



char Load_File_path( char File_folder_path[],  char File_file_name[], char File_extension[]) {

	char File_name_1[] = "../data/";

	//sadly strcpy_s is not part of open standard, thus ggc on linux doesnt supports it
	#ifdef _WIN32
		char File_path[UINT8_MAX];
		strcpy_s(File_path, sizeof(File_name_1), *File_name_1);
		strcpy_s(File_path, sizeof(File_folder_path), *File_folder_path);
		strcpy_s(File_path, sizeof(File_file_name), *File_file_name);
		strcpy_s(File_path, 1, ".");
		strcpy_s(File_path, sizeof(File_extension), *File_extension);
	#else
		char ExtDot[1] = ".";	
		char File_path[(strlen(File_name_1)-1)+(strlen(File_folder_path)+strlen(File_file_name))+(strlen(File_file_name)+strlen(File_extension))+(strlen(ExtDot)-1)];
		//cursed but memory safe
		//TODO: add for loops 
		char* buffer = malloc(300);
		if (buffer != NULL) {		
			u16 i;
			memset(buffer, "\0", 300);		
			memcpy(buffer, File_name_1, strlen(File_name_1)-1);
			for(i=0;i<=(strlen(File_name_1)-1);i+1)
			{
				File_path[i] = buffer[i];					
			}
			memcpy(buffer, File_folder_path, strlen(File_folder_path));
			for(i=(strlen(File_name_1)+1);(i>strlen(File_name_1)) && (i<=strlen(File_folder_path));i+1)
			{
				File_path[i] = buffer[i];					
			}			
			memcpy(buffer, File_file_name, strlen(File_file_name));
			for(i=(strlen(File_folder_path)+1);(i>strlen(File_folder_path)) && (i<=strlen(File_file_name));i+1)
			{
				File_path[i] = buffer[i];					
			}				
			File_path[strlen(File_folder_path)] = File_path + *buffer;
			memcpy(buffer, ExtDot, strlen(ExtDot)-1);
			for(i=(strlen(File_file_name)+1);(i>strlen(File_file_name)) && (i<=(strlen(ExtDot)-1));i+1)
			{
				File_path[i] = buffer[i];					
			}				
			File_path[strlen(File_file_name)] = File_path + *buffer;
			memcpy(buffer, File_extension, strlen(File_extension));		
			for(i=(strlen(File_name_1)-1);(i>File_name_1) && (i<=File_folder_path);i+1)
			{
				File_path[i] = buffer[i];					
			}				
			File_path[strlen(ExtDot)-1] = File_path + *buffer;
			if(File_path[(strlen(File_name_1)-1)+(strlen(File_folder_path)+strlen(File_file_name))+(strlen(File_file_name)+strlen(File_extension))+(strlen(ExtDot)-1)] == NULL)
			{
				free(buffer);
				return -1;
			}
			else
			{
				free(buffer);
			}
		}
		else {
			free(buffer);
			return -1;
		}					
	#endif

	return *File_path;
};

int Load_texture_from_path(SDL_Surface* Image, SDL_Renderer* Renderer, SDL_Texture* Texture, char File_path[])
{
	SDL_RWops* RW_ops;
	RW_ops = SDL_RWFromFile(File_path, "r");

	return 0;
};



int Load_Wav_from_path() //Mix_OpenAudio(44100,AUDIO_F32SYS,2,??? )
{

}

xmlChar Parse_map_XML_values(xmlDocPtr doc, xmlNodePtr cur, char childname[]) {

	xmlChar key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"layer"))) {
			cur = cur->xmlChildrenNode;
			while (cur != NULL) {
				if ((!xmlStrcmp(cur->name, (const xmlChar*)childname))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					return key;
				}
				cur = cur->next;
			}
		}
		cur = cur->next;
	}
	xmlFreeDoc(key);
	return -1;
}

int Get_Properties_Value(xmlDocPtr doc, xmlNodePtr cur, char propertyname[])
{
	xmlChar* key;
	xmlAttr* attribute;
	if (cur && cur->properties)
	{
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar)"property"))) {
				if (attribute->name == propertyname)
				{
					key = xmlGetProp(cur, attribute->name);
					xmlFree(attribute);
					return key;
				}
			}
			attribute = attribute->next;
		}
		return -1;
	}
	return -1;
}

/*
TODO
-check how the tile value block is handled
-make tiles save into their proper indexed place
-handle map changes
*/

int Load_Map_data_from_path( char *chapterID, char *chaptermapid, CurrentMap Map )
{
	//char mapname[INT8_MAX];

	#ifdef _WIN32
		strcpy_s(mapname, 2, chapterID); //current chapter
		strcpy_s(mapname, 1, "_");	
		strcpy_s(mapname, 2, chaptermapid); //most of times = 1 in special cases it can spawn a new map if chapter is multimap
	#else
		char mapnamestring[1+(strlen(chapterID)+strlen(chaptermapid))];
		char* mapname = malloc(30);
		if (mapname != NULL) {		
			memset(mapname, "\0", 30);
			char bufr[] = "_";
			memmove(mapname, chapterID ,strlen(chapterID));
			mapnamestring[0]=*mapname;
			memmove(mapname,bufr,1);
			mapnamestring[1]=*mapname;
			memmove(mapname,chaptermapid,strlen(chaptermapid));	
			mapnamestring[2]=*mapname;
			mapnamestring[3]="\0";
			free(mapname);
		}
		else
		{
			free(mapname);		
			return -1;
		}
	#endif

	printf(mapnamestring);

	char docname[UINT8_MAX]; Load_File_path("../map/map_", mapnamestring, ".tmx");

	xmlDocPtr doc;
	xmlNodePtr cur;
	char outputstring; //its always an string....

	doc = xmlParseFile(docname);

	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully. \n");
		return 0;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return 0;
	}

	if (xmlStrcmp(cur->name, (const xmlChar*)"map")) {
		fprintf(stderr, "document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return 0;
	}

	//get 2 properties held on "map"
	xmlChar MapX = Get_Properties_Value(doc, cur, "width");						//map X (width)
	xmlChar MapY = Get_Properties_Value(doc, cur, "height");						//map Y (height)

	cur = cur -> xmlChildrenNode;
	while (cur != NULL) {
		
		//get properties	
		xmlChar ChapterID = Get_Properties_Value(doc, cur, "ChapterID");			//map chapter id
		xmlChar MapChangesID = Get_Properties_Value(doc, cur, "MapChangesID");		//how many map changes there are
		xmlChar TileConfig = Get_Properties_Value(doc, cur, "TileConfig");			//which internal tileset it is using
		xmlChar TilePalette = Get_Properties_Value(doc, cur, "TilePalette");		//which internal tileset palette it is using

		//get map tile data
		xmlChar* MaptileData = Parse_map_XML_values(doc, cur, "data");

		//finally free memory, this is bc we dont need to reside in memory 100% of the time
		xmlFree(cur);
		xmlFree(doc);

		//save data to map structs >:)
		Map.Map->MapX = (intptr_t)MapX;
		Map.Map->MapY = (intptr_t)MapY;
		Map.Map->UsedTileSet = (intptr_t)TileConfig;
		Map.Map->UsedPallete = (intptr_t)TilePalette;
	
		//now to handle the meh stuff

		//test for tommorow
		printf(MaptileData);
	}

}