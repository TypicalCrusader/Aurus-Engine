#include <stdlib.h>
#include <time.h>

#define CONVOY_MAX_SIZE     1500
#define MAX_GOLD_AMOUNT     9999

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

typedef struct
{
    u16 ItemID;
    u8  StackedItem;
}ConvoyData[CONVOY_MAX_SIZE];

typedef struct 
{
    u8 CurrentChaptID; //current ChapterID
    u16 CurrGold; //Gold Team has
    u16 TeamData[INT8_MAX]; //CharIDs
    s8 PermaFlagData[INT8_MAX]; //max 127 perma flags here for sanity sake
    ConvoyData Convoy;
}MainData;

struct ChapterData
{
    u8 ChapterID;
    u16 ChapterName;
    u16 ChapterDesc;
    u8 ChapterType;
};

enum ChapterType
{
    CHAPTER_TYPE_ROUT,
    CHAPTER_TYPE_ESCAPE,
    CHAPTER_TYPE_DEFEND,
    CHAPTER_TYPE_PROTECT,
    CHAPTER_TYPE_KILL_BOSS,
    CHAPTER_TYPE_SPECIAL,
};
