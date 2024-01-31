#include "types.h"

struct DialogueDataEntry
{
    char DialogueData[50]; //Yaml Entry 
};

enum SpecialCharacters
{
    ENUM_SPECIAL_NEW_LINE  = 0xc28c,       //0xC2 0x8C
    ENUM_SPECIAL_END_ENTRY = 0xc28e,       //0xC2 0x8E
    ENUM_SPECIAL_MID_ENTRY_EVENT = 0xc29c, //0xC2 0x9C
    ENUM_SPECIAL_CHANGE_COLOR = 0xc2bf,    //0xC2 0xBF next 2 bytes = charid
    ENUM_SPECIAL_DISPLAY_VALUE = 0xc7bb,   //0xC7 0xBB taken from internal value slot 3
    ENUM_SPECIAL_DISPLAY_GOLD = 0xc7bf,    //0xC7 0xBF
    ENUM_SPECIAL_BEGIN_NARROW = 0x7B,      //0x7B 
    ENUM_SPECIAL_END_NARROW = 0x7D,        //0x7D
};