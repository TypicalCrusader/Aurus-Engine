#pragma once

#include <stdlib.h>
#include <time.h>
#include "types.h"

#define CONVOY_MAX_SIZE     1500
#define MAX_GOLD_AMOUNT     9999
/*
    `int DiceRollOnehundred` - Roll 1d100 dice
    \returns `OnedDHundred`
    \since This Function is available since version 0.1 of Aurus Engine
*/
static inline u8 DiceRollOnehundred() {
    srand(time(0));
    u8 OnedDHundred = (rand() % (100 - 1 + 1)) + 1;    
    return OnedDHundred;
};
/*
    `int DiceRollOneSix` - Roll 1d6 dice
    \returns `OnedDSix`
    \since This Function is available since version 0.1 of Aurus Engine
*/
static inline u8 DiceRollOneSix() {
    srand(time(0));
    u8 OnedDSix = (rand() % (6 - 1 + 1)) + 1;    
    return OnedDSix;
};
/*
    `int DiceRollOneTwenty` - - Roll 1d20 dice
    \returns `OneDTwenty`
    \since This Function is available since version 0.1 of Aurus Engine
*/
static inline u8 DiceRollOneTwenty() {
    srand(time(0));
    u8 OneDTwenty = (rand() % (20 - 1 + 1)) + 1;    
    return OneDTwenty;   
};

u8 GetU8fromChar(char Convertee);
s8 GetS8fromChar(char Convertee);
u16 GetU16fromChar(char Convertee);
s16 GetS16fromChar(char Convertee);
u32 GetU32fromChar(char Convertee);
s32 GetS32fromChar(char Convertee);
u64 GetU64fromChar(char Convertee);
s64 GetS64fromChar(char Convertee);

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
