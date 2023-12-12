#include "../include/types.h"

struct InventoryData
{
    u16 ItemID;
    u8 ItemType;
    u8 AttackType;
    u8 AttackRange;
    u8 Attack;
    u8 Defense;
    u8 Weight;
    u8 Accuracy;
    u8 CritRate;
    u8 AffinityRes;
    u8 AffinityNul;
    u8 AffinityAbs;
};

extern struct InventoryData CharInventory[UINT16_MAX];

enum ItemType
{
    ITEM_TYPE_CONSUMABLE,
    ITEM_TYPE_QUEST, //IMPORTANT ITEM 0x0 IS SPECIAL HAND ITEM THAT IS USED IN BATTLE IF WEAPON BROKE OR WAS NOT EQUIPED
    ITEM_TYPE_WEAPON,
};