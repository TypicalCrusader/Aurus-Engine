#include "item.h"

static struct gpWeaponWeaknessStruct gWeaponWeakness[(ITEM_TYPE_WEAPON_STAVE + 1)] = { 
    [ITEM_TYPE_ITEM_USABLE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NO_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE,
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE
    },
    [ITEM_TYPE_ITEM_UNUSABLE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NO_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE,
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE        
    },
    [ITEM_TYPE_WEAPON_SWORD] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_AXE,
        .uWeakAgainst = ITEM_TYPE_WEAPON_POLEARM        
    },
    [ITEM_TYPE_WEAPON_AXE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_POLEARM,
        .uWeakAgainst = ITEM_TYPE_WEAPON_SWORD        
    },
    [ITEM_TYPE_WEAPON_POLEARM] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_SWORD,
        .uWeakAgainst = ITEM_TYPE_WEAPON_AXE        
    },
    [ITEM_TYPE_WEAPON_RANGED] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE, //neutral
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE        
    },
    [ITEM_TYPE_WEAPON_MAGIC_FIRE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_WIND,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_WATER        
    },
    [ITEM_TYPE_WEAPON_MAGIC_THUNDER] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_WATER,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_EARTH        
    },
    [ITEM_TYPE_WEAPON_MAGIC_ICE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_EARTH,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_WIND        
    },
    [ITEM_TYPE_WEAPON_MAGIC_WIND] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_ICE,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_FIRE        
    },
    [ITEM_TYPE_WEAPON_MAGIC_WATER] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_HALF_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_FIRE,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_THUNDER        
    },
    [ITEM_TYPE_WEAPON_MAGIC_EARTH] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NORMAL_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_THUNDER,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_ICE        
    },
    [ITEM_TYPE_WEAPON_MAGIC_DAWN] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_INCREASED_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_DUSK,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_DUSK        
    },
    [ITEM_TYPE_WEAPON_MAGIC_DUSK] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_INCREASED_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_WEAPON_MAGIC_DAWN,
        .uWeakAgainst = ITEM_TYPE_WEAPON_MAGIC_DAWN        
    },
    [ITEM_TYPE_WEAPON_MAGIC_DRAGON] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_INCREASED_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE,//neutral
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE        
    },
    [ITEM_TYPE_WEAPON_MAGIC_MONSTER] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_INCREASED_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE,//neutral
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE        
    },
    [ITEM_TYPE_WEAPON_STAVE] = {
        .fBaseNeutralDamage = WEAPON_DAMAGE_NO_DAMAGE,
        .uStrongAgainst = ITEM_TYPE_ITEM_USABLE,
        .uWeakAgainst = ITEM_TYPE_ITEM_USABLE        
    }
};