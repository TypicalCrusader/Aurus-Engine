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
    if((GoldAmount + Data.CurrGold ) > UINT16_MAX)
    {
        assert((GoldAmount + Data.CurrGold ) > UINT16_MAX);
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
    for(i=0;i<=UINT16_MAX;i++)
    {
        if(Data.Convoy[i]->ItemID == 0)
        {
            Data.Convoy[i]->ItemID = Char[CharID].InventoryData[0x5]; //move last item in this to convoy in this case
            Char[CharID].InventoryData[0x5] = ItemID;
            return;
        }
        if (i == UINT16_MAX)
        {
            return;
        }
    }; 

    return;
};

void AddItemToConvoy(u16 ItemID, MainData Data)
{
    u16 i;
    for(i=0;i<=UINT16_MAX;i++)
    {
        if(Data.Convoy[i]->ItemID == 0)
        {
            Data.Convoy[i]->ItemID = ItemID;
            return;
        }
        if (i == UINT16_MAX)
        {
            return;
        }
    };

    return;
};



