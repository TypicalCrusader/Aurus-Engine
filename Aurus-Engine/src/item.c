/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "item.h"
#include "battle.h"
#include "rng.h"
#include "libBINion.h"


struct gpItemStruct uGetItemFromID(u32 uItemID) {
    struct gBINionEntryStruct gItemTable = gBINionEntryStruct(BINION_ENTRY_ITEM_TABLE);
    struct gpItemStruct gItem;
    u32 uTableSize = gItemTable.uEntrySize;
    u8 gBuffer CLEANUP(free_buffer) = (u8) malloc(sizeof(gItem));
    if(sizeof(gItemTable.uEntryData[(sizeof(gItem) * uItemID)]>sizeof(gBuffer)))
    {
        //TODO!: Add error handling
        return;
    }
    else
    {
        //alocates our exact entry we need into memory
        gBuffer = memcpy(gBuffer,gItemTable.uEntryData[(sizeof(gItem) * uItemID)],sizeof(gItem));
        *gItem = *gBuffer
    }
    
    return gItem;
};

u8 USE_FASTCALL uGetItemWpnATKAttributeMod(u32 uItemID) {
    struct gpItemStruct Item = uGetItemFromID(uItemID);
    
    u8 uAtkAttribute;
    
    if(Item.uItemType < ITEM_TYPE_WEAPON_SWORD ){
        return 0xFF;    //max 100 stats (ever)
    };
    if(Item.uItemType == ITEM_TYPE_WEAPON_STAVE) {
        return 0;       //staves do no damage
    }

    if(Item.uItemType <= ITEM_TYPE_WEAPON_AXE)
    {
        uAtkAttribute = ATK_ATTRIBUTE_STR;
    }
    if(Item.uItemType <= ITEM_TYPE_WEAPON_RANGED && Item.uItemType > ITEM_TYPE_WEAPON_AXE)
    {
        uAtkAttribute = ATK_ATTRIBUTE_AGI;
    }
    else
    {
       uAtkAttribute = ATK_ATTRIBUTE_MAG; 
    }

    if(Item.bWpnUsesReverseAtkMod == WEAPON_USES_MAG_DESPITE_TYPE) {
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
    };
    if(Item.bWpnUsesReverseAtkMod == WEAPON_USES_AGI_DESPITE_TYPE) {
        uAtkAttribute = ATK_ATTRIBUTE_AGI;
    }; 

    switch (uAtkAttribute)
    {
        case ATK_ATTRIBUTE_STR:
            return GetCurrentActiveBattleCharacter().gCharacter->sCurrentStr;
        break;
        case ATK_ATTRIBUTE_AGI:
            return GetCurrentActiveBattleCharacter().gCharacter->sCurrentAgi;
        break;
        case ATK_ATTRIBUTE_MAG:
            return GetCurrentActiveBattleCharacter().gCharacter->sCurrentMag;
        break;                    
        default:
            break;
    }
};

u8 USE_FASTCALL uGetItemAtkType(u32 uItemID) {
    struct gpItemStruct Item = uGetItemFromID(uItemID);
    
    u8 uAtkAttribute;
    
    if(Item.uItemType < ITEM_TYPE_WEAPON_SWORD ){
        return 0xFF;    //this is always treat it as error
    };
    if(Item.uItemType == ITEM_TYPE_WEAPON_STAVE) {
        return 0;       //staves do no damage
    }

    if(Item.uItemType <= ITEM_TYPE_WEAPON_RANGED)
    {
        uAtkAttribute = WEAPON_TYPE_MELEE_AND_RANGED;
    }
    if(Item.uItemType <= ITEM_TYPE_WEAPON_MAGIC_EARTH && Item.uItemType > ITEM_TYPE_WEAPON_RANGED)
    {
        uAtkAttribute = WEAPON_TYPE_TOME;
    }
    if(Item.uItemType <= ITEM_TYPE_WEAPON_MAGIC_DUSK && Item.uItemType > ITEM_TYPE_WEAPON_MAGIC_EARTH)
    {
        uAtkAttribute = WEAPON_TYPE_TOME;
    }    
    if(Item.uItemType <= ITEM_TYPE_WEAPON_MAGIC_MONSTER && Item.uItemType > ITEM_TYPE_WEAPON_MAGIC_DUSK)
    {
        uAtkAttribute = WEAPON_TYPE_DRAGONSTONE;
    }    
}
