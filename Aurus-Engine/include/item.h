/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#pragma once
#include "types.h"
#include "battle.h"
#include "rng.h"
#include "libBINion.h"

//defines
#define WEAPON_DAMAGE_NO_DAMAGE        0
#define WEAPON_DAMAGE_HALF_DAMAGE      0.5
#define WEAPON_DAMAGE_NORMAL_DAMAGE    1.0
#define WEAPON_DAMAGE_INCREASED_DAMAGE 1.2
#define WEAPON_DAMAGE_CRITICAL_DAMAGE  1.5

//enums
//dont change an order before swords
//add new entries under entry annotated with //(stat) V and before entry annotated with //^
enum eItemType {
    ITEM_TYPE_ITEM_USABLE,
    ITEM_TYPE_ITEM_UNUSABLE, 
    ITEM_TYPE_WEAPON_SWORD, //str v
    ITEM_TYPE_WEAPON_AXE, //^
    ITEM_TYPE_WEAPON_POLEARM, //agi v
    ITEM_TYPE_WEAPON_RANGED, //^
    ITEM_TYPE_WEAPON_MAGIC_FIRE, //mag v
    ITEM_TYPE_WEAPON_MAGIC_THUNDER,
    ITEM_TYPE_WEAPON_MAGIC_ICE,
    ITEM_TYPE_WEAPON_MAGIC_WIND,
    ITEM_TYPE_WEAPON_MAGIC_WATER,
    ITEM_TYPE_WEAPON_MAGIC_EARTH,
    ITEM_TYPE_WEAPON_MAGIC_DAWN,
    ITEM_TYPE_WEAPON_MAGIC_DUSK,
    ITEM_TYPE_WEAPON_MAGIC_DRAGON,
    ITEM_TYPE_WEAPON_MAGIC_MONSTER, //^
    ITEM_TYPE_WEAPON_STAVE,
};

enum eAtkAttribute {
    ATK_ATTRIBUTE_STR,
    ATK_ATTRIBUTE_AGI,
    ATK_ATTRIBUTE_MAG,
};

enum eWeaponEffect {
    ITEM_EFFECT_APPLY_POISON,
    ITEM_EFFECT_APPLY_SLOW,
    //TODO
};

enum eWeaponAtkType {
    WEAPON_TYPE_MELEE_AND_RANGED,
    WEAPON_TYPE_TOME,
    WEAPON_TYPE_DUSK_DAWN,
    WEAPON_TYPE_DRAGONSTONE,
    WEAPON_TYPE_STAVE,
};

enum eWeaponXPGrowth {
    WEAPON_XP_GROWTH_NONE = 0,
    WEAPON_XP_GROWTH_SMALL = 1,
    WEAPON_XP_GROWTH_NORMAL = 2,
    WEAPON_XP_GROWTH_FAST = 3,
};

enum eWpnReverseAtkMod {
    WEAPON_USES_NORMAL_ATK,
    WEAPON_USES_MAG_DESPITE_TYPE,
    WEAPON_USES_AGI_DESPITE_TYPE,
};

//structs

struct gpItemStruct {
    u32 uItemId;
    u32 uItemIcon;
    u64 uItemName;
    u64 uItemDesc;
    
    u8  uItemType;
    u8  uItemUses; //durability for Wpn, uses for item
    u8  uRequiredWpnLevel;
    u8  uAttachedSkill;
    u8  uWeaponEffect;
    
    struct gpWPNLockStruct *gpWpnLockTable;
    struct gpWPNCounterStruct *gpWpnCounterTable;
    struct gpWPNStatBoostStruct *gpWpnBoostTable;

    u8  uWpnBaseDamage;
    u8  uWpnAccuracy;
    u8  uWpnCriticalChance;
    u8  uWpnLevelGrowth;

    bool bIsWpnUnbreakable;
    u8 bWpnUsesReverseAtkMod; 
};

struct gpWeaponWeaknessStruct {
    f32 fBaseNeutralDamage; //see WEAPON_DAMAGE_NO_DAMAGE -> WEAPON_DAMAGE_INCREASED_DAMAGE
    u8  uStrongAgainst;
    u8  uWeakAgainst;
};

static const struct gpWeaponWeaknessStruct gWeaponWeakness[(ITEM_TYPE_WEAPON_STAVE + 1)];

//functions

struct gpItemStruct USE_FASTCALL uGetItemFromID(u32 uItemID);
u8 USE_FASTCALL uGetItemWpnATKAttributeMod(u32 uItemID);
u8 USE_FASTCALL uGetItemAtkType(u32 uItemID);

static inline void free_item_struct(struct gpItemStruct *gItem) {
    free(gItem);
};