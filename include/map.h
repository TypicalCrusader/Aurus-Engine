#include "types.h"
#include "char.h"

struct SelectedUnit
{
    u16 DeploymentIndex;
    struct CharacterData Unit;
    struct ClassStruct Class;
    u8 level;
    u16 Inventory[0x5];
    s8 MaxHP;
    s8 CurrentHp;
    s8 CurrentAtk;
    s8 CurrentMag;
    s8 CurrentDef;
    s8 CurrentMagDef;
    s8 CurrentSpd;
    s8 CurrentLck;
    s8 CurrentDex;     
    u8 CurrentSwrd;
    u8 CurrentDgr;
    u8 CurrentSpr;
    u8 CurrentAxe;
    u8 CurrentThrow;
    u8 CurrentBow;
    u8 CurrentLight;
    u8 CurrentDark;
    u8 CurrentWind;
    u8 CurrentFire;
    u8 CurrentWater;
    u8 CurrentIce;
    u8 CurrentThunder;
    u8 CurrentEarth;
    u8 CurrentStaves;
    u8 CurrentStone;    
};