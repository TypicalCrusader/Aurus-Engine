/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"
#include "skill.h"
#include "class.h"


#define MAX_SUPPORT_AMOUNT 10
#define MAX_CHARACTER_SKILLS 5
#define MAX_CHARACTER_ABILITIES 8
#define MAX_CHARACTER_INVENTORY_SLOTS 0x4 //5 slots including 0 which is active slot

enum eSupportLevel {
    SUPPORT_LEVEL_D,
    SUPPORT_LEVEL_D_PLUS,
    SUPPORT_LEVEL_C,
    SUPPORT_LEVEL_C_PLUS,
    SUPPORT_LEVEL_B,
    SUPPORT_LEVEL_B_PLUS,
    SUPPORT_LEVEL_A,
    SUPPORT_LEVEL_A_PLUS,
    SUPPORT_LEVEL_S
};

#define MAX_SUPPORT_LEVEL SUPPORT_LEVEL_S

enum eRace {
    RACE_HUMAN,
    RACE_ASCENDED,
    RACE_DEMI_HUMAN_FOX,
    RACE_DEMI_HUMAN_CAT,
    RACE_DEMI_HUMAN_WOLF,
    RACE_DRAGON_DAWN,
    RACE_DRAGON_DUSK,
    RACE_DRAGON_ELEMENTAL,
    RACE_DRAGON_INNATH,
    RACE_DRAGON_MALICE
};

struct gpSupportStruct {
    u32 uDialogueID[SUPPORT_LEVEL_S];
    u8 uCurrentSupportLevel;
};

struct gpSkillGainStruct {
    u16     uSkillID;
    u8      uLevel;
    bool    bUseGainChance;
    s8      sGainChance;
};

struct gpCharacterStruct {
    u16 uCharacterIndex; //0 00-02
    u64 uCharacterName;  //1
    u64 uCharacterDesc;  //2
    u16 uBaseClass;      //3
    u32 uCharacterPortraitID; //4
    u16 uMapSprite;           //5
    u16 uCharacterSkills[4]; //mainly for enemies, characters use other growth table 6
    u8  uRace;  //7
    bool  bUseCombinedGrowths; //Use Character + Class growth instead of just Character growths
    u8  uStartHP;
    s8  sStartStr;
    s8  sStartMag;
    s8  sStartAgi;
    s8  sStartSpd;
    s8  sStartPDef;
    s8  sStartMDef;
    s8  sStartMana;
    s8  sStartChr;
    s8  sStartLck;
    s8  sStartEnd;
    s8  sStartMov;
    //growths
    s8  sHPGrowth;      //health of unit duh
    s8  sStrGrowth;     //axes, swords dmg
    s8  sMagGrowth;     //tomes, staves, dragonstones dmg 
    s8  sAgiGrowth;     //polearms, ranged dmg
    s8  sSpdGrowth;     //how many times you can shank enemy and the evasion of str based wpn and tomes
    s8  sPDefGrowth;    //melee, ranged def
    s8  sMDefGrowth;    //tomes, staves, dragonstones def
    s8  sManaGrowth;    //how many times you can use abilities and magic
    s8  sChrGrowth;     //related to how powerful rally skills will be (eg. 1-10 = +1 to stat increased by rally skill) also changes some dialogue and recruits
    s8  sLckGrowth;     //related to growths, skill activation, damage
    s8  sEndGrowth;     //related to chance to surive killing blow and evasion of agi based wpn and dragonstones
    s8  sMovGrowth;     //how many squares can you move 

    //weapons
    u8  uStartingSwordLv;
    u8  uStartingPolearmsLv;
    u8  uStartingAxeLv;
    u8  uStartingRangedLv;
    u8  uStartingMagicFireLv;
    u8  uStartingMagicIceLv;    
    u8  uStartingMagicThunderLv;    
    u8  uStartingMagicWindLv;
    u8  uStartingMagicDawnLv;
    u8  uStartingMagicDuskLv;
    u8  uStartingMagicDragonLv;   
    u8  uStartingMagicMonsterLv; 
    u8  uStartingStaveLv;   
};

struct gpCurrentCharacter {
    struct gpCharacterStruct *gCharacter;
    struct gpClassStruct *gClass;
    struct gpItemStruct gCharacterInventory[MAX_CHARACTER_INVENTORY_SLOTS];

    u8  uCurrentHP;
    u8  uMaxHP;
    s8  sCurrentStr;
    s8  sCurrentMag;
    s8  sCurrentAgi;
    s8  sCurrentSpd;
    s8  sCurrentPDef;
    s8  sCurrentMDef;
    s8  sCurrentMana;
    s8  sCurrentChr;
    s8  sCurrentLck;
    s8  sCurrentEnd;   
    s8  sCurrentMov;

    u16 uCharacterSkills[MAX_CHARACTER_SKILLS];    
    u16 uCharacterAbilities[MAX_CHARACTER_ABILITIES];
};