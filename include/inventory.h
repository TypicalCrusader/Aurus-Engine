#pragma once

#include "types.h"

struct InventoryData
{
    u16 ItemID;
    char ItemName[50]; //this is just for yaml desc string
    char ItemDesc[50];
    u8 ItemType;
    u8 AttackType;
    u8 AttackRange;
    u8 Attack;
    u8 Defense;
    u8 Weight;
    u8 Accuracy;
    u8 CritRate;
    bool UseMAG;
    u8 AffinityRes;
    u8 AffinityNul;
    u8 AffinityAbs;
    u8 WeaponType;
    u8 WeaponSubType;
};

extern struct InventoryData CharInventory[5];

struct weaponTypeStruct
{
    u8 WeaponTypeEff;
};
struct WeaponSubTypeStruct
{
    u8 WeaponSubTypeEff;
    u8 WeaponEffAgainstType;
};

extern struct weaponTypeStruct weaponType[8];
extern struct WeaponSubTypeStruct WeaponSubType[34];

enum ItemType
{
    ITEM_TYPE_CONSUMABLE,
    ITEM_TYPE_QUEST, //IMPORTANT ITEM 0x0 IS SPECIAL HAND ITEM THAT IS USED IN BATTLE IF WEAPON BROKE OR WAS NOT EQUIPED
    ITEM_TYPE_WEAPON,
};

enum WeaponType
{
    WEAPON_TYPE_NONE,
    WEAPON_TYPE_BLADE,
    WEAPON_TYPE_AXE,
    WEAPON_TYPE_POLEARMS,
    WEAPON_TYPE_THROWABLE,
    WEAPON_TYPE_MAGIC_ELEMENTAL,
    WEAPON_TYPE_MAGIC_DAWN_DUSK,
    WEAPON_TYPE_MAGIC_DRAGON_SYGIL,
};

enum WeaponSubType
{
    WEAPON_SUB_TYPE_NONE,
    WEAPON_SUB_TYPE_DAGGER,
    WEAPON_SUB_TYPE_ZWEIHANDER,
    WEAPON_SUB_TYPE_ESTOC,
    WEAPON_SUB_TYPE_LONGSWORD,
    WEAPON_SUB_TYPE_SWORDSTAFF,
    WEAPON_SUB_TYPE_GLAIVE,
    WEAPON_SUB_TYPE_SPEAR,
    WEAPON_SUB_TYPE_HAMMER,
    WEAPON_SUB_TYPE_MACE,
    WEAPON_SUB_TYPE_AXE,
    WEAPON_SUB_TYPE_PRIMITIVE,
    WEAPON_SUB_TYPE_BOW,
    WEAPON_SUB_TYPE_CROSSBOW,
    WEAPON_SUB_TYPE_JAVELIN,
    WEAPON_SUB_TYPE_THROW_AXE,
    WEAPON_SUB_TYPE_MAGIC_FIRE,
    WEAPON_SUB_TYPE_MAGIC_WATER,
    WEAPON_SUB_TYPE_MAGIC_WIND,
    WEAPON_SUB_TYPE_MAGIC_LIGHTNING,
    WEAPON_SUB_TYPE_MAGIC_EARTH,
    WEAPON_SUB_TYPE_MAGIC_ANIMA,
    WEAPON_SUB_TYPE_MAGIC_DAWN,
    WEAPON_SUB_TYPE_MAGIC_DUSK,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_FIRE,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_WATER,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_WIND,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_LIGHTNING,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_EARTH,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_ANIMA,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_DAWN,
    WEAPON_SUB_TYPE_SYGIL_ELEMENTAL_DUSK,
    WEAPON_SUB_TYPE_SYGIL_DECADENT,
    WEAPON_SUB_TYPE_SYGIL_MAN,
};