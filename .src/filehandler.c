
#include "../include/filehandler.h"

char* Load_File_path( char File_folder_path[],  char File_file_name[], char File_extension[]) {

	char File_name_1[] = "./data/";

	//sadly strcpy_s is not part of open standard, thus ggc on linux doesnt supports it
	char ExtDot[1] = ".";	
	//cursed but memory safe
	char* buffer = malloc((strlen(File_name_1)+strlen(File_folder_path)+strlen(File_file_name)+1+strlen(File_extension)+1));

	if (buffer != NULL) {		
		//u16 i;
		memset(buffer, '\0', (strlen(File_name_1)+strlen(File_folder_path)+strlen(File_file_name)+strlen(ExtDot)+strlen(File_extension)+1));		
		memcpy(buffer, File_name_1, strlen(File_name_1));
		memcpy(buffer+strlen(File_name_1), File_folder_path, strlen(File_folder_path));		
		memcpy(buffer+(strlen(File_name_1)+strlen(File_folder_path)), File_file_name, strlen(File_file_name));
		memcpy(buffer+(strlen(File_name_1)+strlen(File_folder_path)+strlen(File_file_name)), ExtDot, 1);
		memcpy(buffer+(strlen(File_name_1)+strlen(File_folder_path)+strlen(File_file_name)+1), File_extension, strlen(File_extension));
		memcpy(buffer+(strlen(File_name_1)+strlen(File_folder_path)+strlen(File_file_name)+1+strlen(File_extension)), "\0" , 1);	
	}
	else {
		free(buffer);
		return NULL;
	}					
	return buffer;
};

int Load_texture_from_path(SDL_Surface* Image, SDL_Renderer* Renderer, SDL_Texture* Texture, char File_path[])
{
	SDL_RWops* RW_ops;
	RW_ops = SDL_RWFromFile(File_path, "r");

	return 0;
};

int Load_Wav_from_path() //Mix_OpenAudio(44100,AUDIO_F32SYS,2,??? )
{
	return 0;
}

int Parse_map_XML_values(xmlDocPtr doc, xmlNodePtr cur, char childname[]) {

	xmlChar* key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar*)"layer"))) {
			cur = cur->xmlChildrenNode;
			while (cur != NULL) {
				if ((!xmlStrcmp(cur->name, (const xmlChar*)childname))) {
					key  = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					return key;
				}
				cur = cur->next;
			}
		}
		//cur = cur->next;
	}
	xmlFreeDoc(doc);
	return -1;
}

char Get_Properties_Value(xmlDocPtr doc, xmlNodePtr cur, char propertyname[])
{
	xmlChar* key;
	xmlAttr* attribute;
	if (cur && cur->properties)
	{
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar)"property"))) {
				if (attribute->name == &propertyname)
				{
					key = xmlGetProp(cur, attribute->name);
					xmlFree(attribute);
					return &key;
				}
			}
			//attribute = attribute->next;
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

int* Load_Map_data_from_path( char *chapterID, char *chaptermapid)
{
	struct CurrentMap *Map = malloc(sizeof(*Map));
	
	printf("%i\n",sizeof(Map));

	char bufr[] = "_";
	char* mapname = malloc(sizeof(chapterID)+sizeof(bufr)+sizeof(chaptermapid));
	if (mapname != NULL) {		
		memset(mapname, '\0', (sizeof(chapterID)+sizeof(bufr)+sizeof(chaptermapid)));
		memcpy(mapname, chapterID ,strlen(chapterID));
		memcpy(mapname+strlen(chapterID),bufr,1);
		memcpy(mapname+(strlen(chapterID)+1),chaptermapid,strlen(chaptermapid));
	}
	else
	{
		free(mapname);		
		return NULL;
	}

	char* docname = malloc(strlen(mapname) + 1 + (strlen(chapterID) + strlen(chaptermapid))+1);
	docname = Load_File_path("map/map_", mapname, "tmx");

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	free(docname);

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

	xmlChar *MapX;
	xmlChar *MapY;

	MapY = xmlGetProp(cur,"height");
	MapX = xmlGetProp(cur,"width");
	printf("%s\n", MapX);


	cur = cur -> xmlChildrenNode;
	while (cur != NULL) {
		
		//get properties	
		xmlChar ChapterID = Get_Properties_Value(doc, cur, "ChapterID");			//map chapter id
		xmlChar MapChangesID = Get_Properties_Value(doc, cur, "MapChangesID");		//how many map changes there are
		xmlChar TileConfig = Get_Properties_Value(doc, cur, "TileConfig");			//which internal tileset it is using
		xmlChar TilePalette = Get_Properties_Value(doc, cur, "TilePalette");		//which internal tileset palette it is using

		//get map tile data
		int MaptileData = Parse_map_XML_values(doc, cur, "data");

		//finally free memory, this is bc we dont need to reside in memory 100% of the time
		xmlFree(cur);
		xmlFree(doc);

		Map -> Map = calloc(1,sizeof(*Map -> Map));
		//Map -> Map = Malloc(sizeof(*Map -> Map));
		Map -> Map -> MapX = (u8) calloc(1, 1);
		Map -> Map -> MapY = (u8) calloc(1, 1);
		Map -> Map ->UsedTileSet = (u8) calloc(1, 1);


		//printf(Map -> Map->MapX);

		//save data to map structs >:)
		Map -> Map-> MapX = (u8) GetU8fromChar(MapX);

		Map -> Map-> MapY = (u8) GetU8fromChar(MapY);
		Map -> Map-> UsedTileSet = (u8) GetU8fromChar(TileConfig);
		Map -> Map-> UsedPallete = (u8) GetU8fromChar(TilePalette);
	
		printf("%i\n", Map -> Map->MapX);
		printf("%i\n", Map -> Map->MapY);
		printf("%i\n", Map -> Map->UsedTileSet);
		printf("%i\n", Map -> Map->UsedPallete);						

		//now to handle the meh stuff

		//test for tommorow
		printf("%u\n", MaptileData);

		return 0;
	}

	return 0;
}