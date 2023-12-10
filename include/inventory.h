#include "../include/types.h"

struct InventoryData
{
    u16 ItemID;
    u8 ItemType;
    u8 AttackType;
    u8 AttackRange;
    u8 Attack;
    u8 Defense;
    
};

enum ItemType
{
    ITEM_TYPE_CONSUMABLE,
    ITEM_TYPE_QUEST, //IMPORTANT ITEM 0x0 IS SPECIAL HAND ITEM THAT IS USED IN BATTLE IF WEAPON BROKE OR WAS NOT EQUIPED
    ITEM_TYPE_WEAPON,
};