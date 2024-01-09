#include <stdlib.h>
#include <time.h>

inline int DiceRollOnehundred () {
    srand(time(0));
    int OnedDHundred = (rand() % (100 - 1 + 1)) + 1;    
    return OnedDHundred;
};

inline int DiceRollOneSix () {
    srand(time(0));
    int OnedDSix = (rand() % (6 - 1 + 1)) + 1;    
    return OnedDSix;
};

struct MainDataStruct
{
    u8 CurrentChaptID; //current ChapterID
    u16 CurrGold; //Gold Team has
    u32 ConvoyData[UINT32_MAX]; //Inventory data in item indexes
    u16 TeamData[UINT16_MAX]; //CharIDs
    s8 PermaFlagData[INT8_MAX]; //max 127 perma flags here for sanity sake
};

struct MainDataStruct MainData;
