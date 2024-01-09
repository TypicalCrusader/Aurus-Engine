#include "types.h"
#include "misc.h"
#include "char.h"
#include "inventory.h"
#include <stdlib.h>
#include <assert.h>

u8 PermaFlags[INT8_MAX];

int SetPermaFlagTo(s8 Flag, s8 SetUnset )
{
    if((SetUnset != 0 ) || (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) || ( SetUnset != 1) );
    };
    if(Flag < 0)
    {
        assert(Flag < 0);
    }

    PermaFlags[Flag] = SetUnset;
};

int CheckPermaFlag(s8 Flag)
{
    if(Flag < 0)
    {
        assert(Flag < 0);
    }
    return PermaFlags[Flag];
};

u8 TempFlags[UINT8_MAX];

int SetTempFlagto(u8 Flag, u8 SetUnset)
{
    if((SetUnset != 0 ) || (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) || ( SetUnset != 1) );
    };

    TempFlags[Flag] = SetUnset;
};

int CheckTempFlag(u8 Flag)
{
    return TempFlags[Flag];
};

void AddGoldToTeam(u16 GoldAmount)
{
    if((GoldAmount + MainData.CurrGold ) > UINT16_MAX)
    {
        assert((GoldAmount + MainData.CurrGold ) > UINT16_MAX);
    }
    MainData.CurrGold += GoldAmount;
    return;
};

void AddItemToCharacter(u16 CharID, u16 ItemID){
    u8 i;
    for(i=0,i<5,i++)
    {
        if(CurrChar[CharID].InventoryData[i] == 0)
        {
            CurrChar[CharID].InventoryData[i] = ItemID;
        }
    }

    return;
};

void AddItemToConvoy(u16 ItemID)
{
    

    return;
};