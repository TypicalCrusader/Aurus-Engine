#pragma once

#include "types.h"
#include "ai.h"
#include "map.h"

#define RACESAMOUNT 15


struct ClassStruct
{
    u8 ClassID;
    char* ClassName; //this is just for yaml desc string
    char* ClassDesc;
    u8 ClassType;
    u8 ClassGenderLock;
    u8 ClassSkill;
    u8 ClassPromoBranch[0x2];
    s8 BaseHp;
    s8 BaseAtk;
    s8 BaseMag;
    s8 BaseDef;
    s8 BaseMagDef;
    s8 BaseSpd;
    s8 BaseLck;
    s8 BaseDex;
    s8 HpCharGrowth;
    s8 AtkCharGrowth;
    s8 MagCharGrowth;
    s8 DefCharGrowth;
    s8 MagDefCharGrowth;
    s8 SpdCharGrowth;
    s8 LckCharGrowth;
    s8 DexCharGrowth;
    bool ClassUsesSwrd;
    bool ClassUsesDgr;
    bool ClassUsesSpr;
    bool ClassUsesAxe;
    bool ClassUsesThrow;
    bool ClassUsesBow;
    bool ClassUsesLight;
    bool ClassUsesDark;
    bool ClassUsesWind;
    bool ClassUsesFire;
    bool ClassUsesWater;
    bool ClassUsesIce;
    bool ClassUsesThunder;
    bool ClassUsesEarth;
    bool ClassUsesStaves;
    bool ClassUsesStone;
};


struct CharacterData
{
    u16 UnitID;
    char CharName[50]; //this is just for yaml desc string
    char CharDesc[50];
    u8 RaceID;
    u8 CharGender;
    u8 alignment;
    u16 BaseClass;
    u32 CharSkills[0x4];
    s8 BaseHp;
    s8 BaseAtk;
    s8 BaseMag;
    s8 BaseDef;
    s8 BaseMagDef;
    s8 BaseSpd;
    s8 BaseLck;
    s8 BaseDex;
    s8 HpCharGrowth;
    s8 AtkCharGrowth;
    s8 MagCharGrowth;
    s8 DefCharGrowth;
    s8 MagDefCharGrowth;
    s8 SpdCharGrowth;
    s8 LckCharGrowth;
    s8 DexCharGrowth;
    u8 BaseSwrd;
    u8 BaseDgr;
    u8 BaseSpr;
    u8 BaseAxe;
    u8 BaseThrow;
    u8 BaseBow;
    u8 BaseLight;
    u8 BaseDark;
    u8 BaseWind;
    u8 BaseFire;
    u8 BaseWater;
    u8 BaseIce;
    u8 BaseThunder;
    u8 BaseEarth;
    u8 BaseStaves;
    u8 BaseStone;
};

extern struct CharacterData Character[UINT16_MAX];

struct MiscCharDataStruct
{
    u8 gender;
    u8 MapX;
    u8 MapY;
    u8 Faction;
    struct AIData *AI;
};

struct CurrCharData
{
    u8 DevelopmentIndex;
    u16 UnitID;
    struct CharacterData *CharData;
    struct ClassStruct *ClassData;
    struct RaceStruct *Race;
    struct MiscCharDataStruct *MiscCharData;
    struct InventoryData *Inventory;
    u16 CurrentSkills[5];
    s8 MaxHP;
    s8 CurrHp;
    s8 CurrAtk;
    s8 CurrMag;
    s8 CurrDef;
    s8 CurrMagDef;
    s8 CurrSpd;
    s8 CurrLck;
    s8 CurrDex;
    u8 CurrSwrd;
    u8 CurrDgr;
    u8 CurrSpr;
    u8 CurrAxe;
    u8 CurrThrow;
    u8 CurrBow;
    u8 CurrLight;
    u8 CurrDark;
    u8 CurrWind;
    u8 CurrFire;
    u8 CurrWater;
    u8 CurrIce;
    u8 CurrThunder;
    u8 CurrEarth;
    u8 CurrStaves;
    u8 CurrStone;
    u8 CurrLvl;
};

extern struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

enum gender {
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_NONE
};

enum alignment
{
    ALIGNMENT_NONE,
    ALIGNMENT_LIGHT,
    ALIGNMENT_DARK,
    ALIGNMENT_WIND,
    ALIGNMENT_FIRE,
    ALIGNMENT_THUNDER,
    ALIGNMENT_WATER,
    ALIGNMENT_EARTH,
    ALIGNMENT_ICE,
    ALIGNMENT_ANIMA
};

struct RaceBoostStruct 
{
    s8 HPBon;
    s8 POWBon;
    s8 SKLBon;
    s8 SPDBon;
    s8 DEFBon;
    s8 RESBon;
    s8 LCKBon;
};

struct RaceSMTLikeRes
{
    u16 NulllignmentDmg [0xa];
    u16 ResAlignmentDmg [0xa];
    u16 ReverseAlignmentDmg [0xa];
    u16 SpecialWeaponNullDmg [0xa];
};

struct RaceStruct
{
    u8 RaceID;
    u8 RaceSkill;
    char RaceName[50]; //this is just for yaml desc string
    char RaceDesc[50]; 
    struct RaceSMTLikeRes SMTRes;
    struct RaceBoostStruct Raceboost;
    bool RaceSMTShouldNullAtk;    
};

extern struct RaceStruct Race[RACESAMOUNT];

enum ClassType
{
    TYPE_INFANTRY,
    TYPE_CAVALERY,
    TYPE_ARMORED,
    TYPE_LIGHT,
    TYPE_FLYER,
    TYPE_MAGICAL,
    TYPE_MONSTER,
};

static void ExchangeInvSlotInfo(u8 SlotFrom, u8 SlotInto)
{
    if(&Character != NULL) //sanity check so we dont access unalocated memory
    {

    }
    return;
};
inline void ChangeGender(u8 Gender) //fuckin dragons are putting magic into the water that turns the heckin humans gae
{
    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return;
    }
    if(Gender > GENDER_NONE) //3 defined
    {
        return;
    }

    CurrentCharacter->MiscCharData->gender = Gender;

    return;
}
inline void ChangeAlignment(u8 Alignment)
{
    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return;
    }
    if(Alignment > ALIGNMENT_ANIMA) 
    {
        return;
    }
    CurrentCharacter->CharData->alignment = Alignment;

    return;
}
//0-23 follows the CurrCharData order
inline u8 GetStatSkill(u8 Stat){
    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return;
    }
    if(Stat > 23) 
    {
        return;
    }
    if(&CurrentCharacter + (39+Stat) == NULL)
    {
        return;
    }
    if(&SelectedUnit == NULL){
        return;
    }
    #if UINTPTR_MAX != UINT32_MAX
        u8 *StatVal = &CurrentCharacter[SelectedUnit.DeploymentIndex] + (39+Stat);
    #elif UINTPTR_MAX == UINT32_MAX
        u8 *StatVal = &CurrentCharacter[SelectedUnit.DeploymentIndex] + (23+Stat);
    #else
        //something is severly fucked
        //TODO ADD ERROR HERE
        return -1;
    #endif
    return StatVal;
};
inline u16 GetCharID(){
    if(&SelectedUnit == NULL)
    {
        return -1;
    }
    if(&SelectedUnit.Unit == NULL)
    {
        return -1;
    }    
    return SelectedUnit.Unit->UnitID;
};
inline u8 GetRace(){
    if(&SelectedUnit == NULL)
    {
        return -1;
    }
    if(&SelectedUnit.Unit == NULL)
    {
        return -1;
    }
    return SelectedUnit.Unit->RaceID;
};