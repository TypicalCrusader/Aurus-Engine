#include "item.h"
#include "battle.h"
#include "rng.h"
#include "libBINion.h"


struct gpItemStruct uGetItemFromID(u32 uItemID) {
    struct gBINionEntryStruct gItemTable = gBINionEntryStruct(BINION_ENTRY_ITEM_TABLE);
    struct gpItemStruct gItem;
    u32 uTableSize = gItemTable.uEntrySize;
    u8 gBuffer = (u8) malloc(sizeof(gItem));
    if(sizeof())
    u8 gBuffer = memcpy(gBuffer,gItemTable.uEntryData[(sizeof(gItem) * uItemID)],sizeof(gItem));
    
    //gItemTable.uEntryData 
    /* 
        sizeof(gItem) * uItemID to get how many bytes to move
        memcpy(gBuffer,uTableSize[(sizeof(gItem) * uItemID)],sizeof(gItem))
        then copy memcpy appropriate values to members of struct
        the free gBuffer and return gItem
    */
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

    switch (Item.uItemType)
    {
    case ITEM_TYPE_WEAPON_SWORD:
        uAtkAttribute = ATK_ATTRIBUTE_STR;
        break;
    case ITEM_TYPE_WEAPON_AXE:
        uAtkAttribute = ATK_ATTRIBUTE_STR;
        break;
    case ITEM_TYPE_WEAPON_POLEARM:
        uAtkAttribute = ATK_ATTRIBUTE_AGI;
        break;        
    case ITEM_TYPE_WEAPON_RANGED:
        uAtkAttribute = ATK_ATTRIBUTE_AGI;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_FIRE:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_THUNDER:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_ICE:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_WIND:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_WATER:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_EARTH:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_DAWN:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;         
    case ITEM_TYPE_WEAPON_MAGIC_DUSK:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_DRAGON:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_MONSTER:
        uAtkAttribute = ATK_ATTRIBUTE_MAG;
        break; 
    default:
        break;
    };

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
        return 0xFF;    //max 100 stats (ever)
    };
    if(Item.uItemType == ITEM_TYPE_WEAPON_STAVE) {
        return 0;       //staves do no damage
    }

    switch (Item.uItemType)
    {
    case ITEM_TYPE_WEAPON_SWORD:
        uAtkAttribute = WEAPON_TYPE_MELEE_AND_RANGED;
        break;
    case ITEM_TYPE_WEAPON_AXE:
        uAtkAttribute = WEAPON_TYPE_MELEE_AND_RANGED;
        break;
    case ITEM_TYPE_WEAPON_POLEARM:
        uAtkAttribute = WEAPON_TYPE_MELEE_AND_RANGED;
        break;        
    case ITEM_TYPE_WEAPON_RANGED:
        uAtkAttribute = WEAPON_TYPE_MELEE_AND_RANGED;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_FIRE:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_THUNDER:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_ICE:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_WIND:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_WATER:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_EARTH:
        uAtkAttribute = WEAPON_TYPE_TOME;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_DAWN:
        uAtkAttribute = WEAPON_TYPE_DUSK_DAWN;
        break;         
    case ITEM_TYPE_WEAPON_MAGIC_DUSK:
        uAtkAttribute = WEAPON_TYPE_DUSK_DAWN;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_DRAGON:
        uAtkAttribute = WEAPON_TYPE_DRAGONSTONE;
        break;
    case ITEM_TYPE_WEAPON_MAGIC_MONSTER:
        uAtkAttribute = WEAPON_TYPE_DRAGONSTONE;
        break; 
    default:
        break;
    };
}
