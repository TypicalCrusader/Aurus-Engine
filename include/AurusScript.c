#include "types.h"
#include "misc.h"
#include "char.h"
#include "inventory.h"
#include <stdlib.h>
#include <assert.h>

u8 PermaFlags[UINT8_MAX];

void SetPermaFlagTo(u8 Flag, u8 SetUnset )
{
    if((SetUnset != 0 ) && (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) && ( SetUnset != 1) );
    };

    PermaFlags[Flag] = SetUnset;
    return;
};

int CheckPermaFlag(u8 Flag)
{
    return PermaFlags[Flag];
};

u8 TempFlags[UINT8_MAX];

void SetTempFlagto(u8 Flag, u8 SetUnset)
{
    if((SetUnset != 0 ) && (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) && ( SetUnset != 1) );
    };

    TempFlags[Flag] = SetUnset;
    return;
};

int CheckTempFlag(u8 Flag)
{
    return TempFlags[Flag];
};

void AddGoldToTeam(u16 GoldAmount, MainData Data)
{
    if((GoldAmount + Data.CurrGold ) > MAX_GOLD_AMOUNT)
    {
        return;
    }
    Data.CurrGold += GoldAmount;
    return;
};

void AddItemToCharacter(u16 CharID, u16 ItemID, MainData Data, CurrChar Char){
    u16 i;
    for(i=0;i<5;i++)
    {
        if (Char[CharID].InventoryData[i] == 0)
        {
            Char[CharID].InventoryData[i] = ItemID;
            return;
        }
    }
    for(i=0;i <= CONVOY_MAX_SIZE;i++)
    {
        if(Data.Convoy[i].ItemID == 0)
        {
            u32 item = Char[CharID].InventoryData[4]; //move last item in this to convoy in this case
            Data.Convoy[i].ItemID = item;
            item = ItemID;
            Char[CharID].InventoryData[4] = ItemID;
            return;
        }
        if (i == CONVOY_MAX_SIZE)
        {
            return;
        }
    }; 

    return;
};

void AddItemToConvoy(u16 ItemID, MainData Data)
{
    u16 i;
    for(i=0;i<= CONVOY_MAX_SIZE;i++)
    {
        if(Data.Convoy[i].ItemID == 0)
        {
            Data.Convoy[i].ItemID = ItemID;
            return;
        }
        if (i == CONVOY_MAX_SIZE)
        {
            return;
        }
    };

    return;
};



