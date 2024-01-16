#include "types.h"

struct DialogueDataEntry
{
    u32 DialogueID;
    int DialogueData[]; //tbh i think that reading one utf8 character at the time into memory might be the best option here... just to make sure it will always find special characters for ends and such
};


enum SpecialCharacters
{
    ENUM_SPECIAL_NEW_LINE  = 0xc28c,       //0xC2 0x8C
    ENUM_SPECIAL_END_ENTRY = 0xc28e,       //0xC2 0x8E
    ENUM_SPECIAL_MID_ENTRY_EVENT = 0xc29c, //0xC2 0x9C
    ENUM_SPECIAL_CHANGE_COLOR = 0xc2bf,    //0xC2 0xBF next 2 bytes = charid
    ENUM_SPECIAL_DISPLAY_VALUE = 0xc7bb,   //0xC7 0xBB taken from internal value slot 3
    ENUM_SPECIAL_DISPLAY_GOLD = 0xc7bf,    //0xC7 0xBF
};