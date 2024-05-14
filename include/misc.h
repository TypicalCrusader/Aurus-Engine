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
    `int DiceRollOneTwenty` - Roll 1d20 dice
    \returns `OneDTwenty`
    \since This Function is available since version 0.1 of Aurus Engine
*/
static inline u8 DiceRollOneTwenty() {
    srand(time(0));
    u8 OneDTwenty = (rand() % (20 - 1 + 1)) + 1;    
    return OneDTwenty;   
};

static inline u8 GetU8fromChar (char Convertee)
{
    u8 ReturnU8 = (u8) Convertee - '0';
    return ReturnU8;
};

static inline s8 GetS8fromChar (char Convertee)
{
    s8 ReturnS8 = (s8) Convertee - '0';
    return ReturnS8;
};

static inline u16 GetU16fromChar (char Convertee)
{
    u16 Returnu16 = (u16) Convertee - '0';
    return Returnu16;
};

static inline s16 GetS16fromChar (char Convertee)
{
    s16 Returns16 = (s16) Convertee - '0';
    return Returns16;
};

static inline u32 GetU32fromChar (char Convertee)
{
    u32 Returnu32 = Convertee - '0';
    return Returnu32;
};

static inline s32 GetS32fromChar (char Convertee)
{
    s32 Returns32 = Convertee - '0';
    return Returns32;
};

static inline u64 GetU64fromChar (char Convertee)
{
    u64 Returnu64 = Convertee - '0';
    return Returnu64;
};

static inline s64 GetS64fromChar (char Convertee)
{
    s64 Returns64 = Convertee - '0';
    return Returns64;
};

static inline f32 GetF32fromChar (char Convertee)
{
    f32 ReturnF32 = Convertee - '0';
    return ReturnF32;
};

static inline f64 GetF64fromChar (char Convertee)
{
    f64 ReturnF64 = Convertee - '0';
    return ReturnF64;
};

extern u16 MemSlot[16];

typedef struct ConvoyData
{
    u16 ItemID;
    u8  StackedItem;
}ConvoyData[CONVOY_MAX_SIZE];

struct MainDataStruct
{
    u8 CurrentChaptID; //current ChapterID
    u16 CurrGold; //Gold Team has
    u16 TeamData; //CharIDs
    s8 PermaFlagData; //max 127 perma flags here for sanity sake
    ConvoyData *Convoy;
};

extern struct MainDataStruct MainData; 

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
