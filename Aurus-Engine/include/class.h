/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"

enum eClassType {
    CLASS_TYPE_LIGHT,
    CLASS_TYPE_HEAVY,
    CLASS_TYPE_ARCHER,
    CLASS_TYPE_FLYER,
    CLASS_TYPE_CAVALRY,
    CLASS_TYPE_MONSTER,
    CLASS_TYPE_DRAGON,
    CLASS_TYPE_DARK_DRAGON,
    CLASS_TYPE_DEMON,
};

struct gpClassStruct {
    u16 uClassID;
    u64 uNameTextID;
    u64 uDescTextID;

    u32 uClassIconID;
    u32 uGenericEnemyIcon;

    u8 uClassType;

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
    
    //class weapons
    bool  bClassUsesSword;
    bool  bClassUsesPolearms;
    bool  bClassUsesAxe;
    bool  bClassUsesRanged;
    bool  bClassUsesMagicFire;
    bool  bClassUsesMagicIce;    
    bool  bClassUsesMagicThunder;    
    bool  bClassUsesMagicWind;
    bool  bClassUsesMagicDawn;
    bool  bClassUsesMagicDusk;
    bool  bClassUsesMagicDragon;   
    bool  bClassUsesMagicMonster; 
    bool  bClassUsesStave;  
};