#include "../include/aurusscript.h"

inline void SetPermaFlagTo(u8 Flag, u8 SetUnset )
{
    if((SetUnset != 0 ) && (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) && ( SetUnset != 1) );
    };

    PermaFlags[Flag] = SetUnset;
    return;
};

inline u8 CheckPermaFlag(u8 Flag)
{
    return PermaFlags[Flag];
};


inline void SetTempFlagto(u8 Flag, u8 SetUnset)
{
    if((SetUnset != 0 ) && (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) && ( SetUnset != 1) );
    };

    TempFlags[Flag] = SetUnset;
    return;
};

inline u8 CheckTempFlag(u8 Flag)
{
    return TempFlags[Flag];
};

void AddGoldToTeam(u16 GoldAmount)
{
    MainData Data;
    if((GoldAmount + Data.CurrGold ) > MAX_GOLD_AMOUNT)
    {
        return;
    }
    Data.CurrGold += GoldAmount;
    return;
};

void AddItemToCharacter(u16 CharID, u16 ItemID){
    u16 i;
    CurrCharData *Char;
    MainData Data;
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

void AddItemToConvoy(u16 ItemID)
{
    MainData Data;
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

void SpawnUnit(u16 CharID, u8 Faction, u32 AI, u16 Inventory[0x5], u16 Skills[0x5], u8 MapX, u8 MapY, bool TakeDataFromSave)
{

    //sanity checks so we never access unalocated memory thus causing segfault
    //TODO: ADD fprintf to stderr
    if(&Character == NULL)
    {
        return;
    }
    if(&CurrentCharacter == NULL)
    {
        return;
    }
    if(&CurrentCharacter[0] == NULL ) //somehow its unalocated thus something broke
    {
        return;
    }
    if(&CurrentCharacter[MAX_DEPLOYED_ALL_UNITS] == NULL)
    {
        return;
    }
    if(CurrentCharacter[MAX_DEPLOYED_ALL_UNITS].UnitID >= 0)
    {
        return;
    }
    if(MapY > MAX_MAP_SIZE || MapY > MAX_MAP_SIZE)
    {
        return;
    }

    return;
}

