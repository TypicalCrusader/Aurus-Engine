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

    //used for enemies and promotion
    u8  uStartHP    :3;
    u8  sStartStr   :3;
    u8  sStartChr   :2;
    u8  sStartMag   :3;
    u8  sStartAgi   :3;
    u8  sStartLck   :2;
    u8  sStartSpd   :3;
    u8  sStartPDef  :3;
    u8  sStartMov   :2;
    u8  sStartMDef  :3;
    u8  sStartMana  :3;
    u8  sStartEnd   :2;
    //this + class = growths for most
    //growths
    //at most +50
    u8  sHPGrowth               : 6;      //health of unit duh
    u8  uClassUsesSword         : 1;
    u8  uClassUsesPolearms      : 1;
    u8  sStrGrowth              : 6;     //axes, swords dmg
    u8  uClassUsesAxe           : 1;
    u8  uClassUsesRanged        : 1;
    u8  sMagGrowth              : 6;     //tomes, staves, dragonstones dmg 
    u8  uClassUsesMagicFire     : 1;
    u8  uClassUsesMagicIce      : 1;      
    u8  sAgiGrowth              : 6;     //polearms, ranged dmg
    u8  uClassUsesMagicThunder  : 1;    
    u8  uClassUsesMagicWind     : 1;    
    u8  sSpdGrowth              : 6;     //how many times you can shank enemy and the evasion of str based wpn and tomes
    u8  uClassUsesMagicDawn     : 1;
    u8  uClassUsesMagicDusk     : 1;   
    u8  sPDefGrowth             : 6;    //melee, ranged def
    u8  uClassUsesMagicDragon   : 1;   
    u8  uClassUsesMagicMonster  : 1;     
    u8  sMDefGrowth             : 6;    //tomes, staves, dragonstones def
    u8  uClassUsesStave         : 1;  
    u8  sManaGrowth             : 6;    //how many times you can use abilities and magic
    u8  sChrGrowth              : 6;     //related to how powerful rally skills will be (eg. 1-10 = +1 to stat increased by rally skill) also changes some dialogue and recruits
    u8  sLckGrowth              : 6;     //related to growths, skill activation, damage
    u8  sEndGrowth              : 6;     //related to chance to surive killing blow and evasion of agi based wpn and dragonstones
    u8  sMovGrowth              : 6;     //how many squares can you move 
};