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

void SetTempFlagto(u8 Flag, u8 SetUnset)
{
    if((SetUnset != 0 ) && (SetUnset != 1) )
    {
        assert((SetUnset != 0 ) && ( SetUnset != 1) );
    };

    TempFlags[Flag] = SetUnset;
    return;
};

void AddGoldToTeam(u16 GoldAmount)
{
    if(&MainData == NULL)
    {
        return;
    }

    if((GoldAmount + MainData.CurrGold ) > MAX_GOLD_AMOUNT)
    {
        return;
    }
    MainData.CurrGold += GoldAmount;
    return;
};

void AddItemToCharacter(u16 ItemID){
    u16 i;

    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL)
    {
        return;
    }
    
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL)
    {
        return;
    }

    u8 CharID = SelectedUnit.DeploymentIndex;

    if(CharID > MAX_DEPLOYED_ALL_UNITS)
    {
        return;
    }

    for(i=0;i<5;i++)
    {
        if (CurrentCharacter[CharID].Inventory[i].ItemID == 0)
        {
            CurrentCharacter[CharID].Inventory[i].ItemID = ItemID;
            return;
        }
    }
    for(i=0;i <= CONVOY_MAX_SIZE;i++)
    {
        if(MainData.Convoy[i]->ItemID == 0)
        {
            u32 item = CurrentCharacter[CharID].Inventory[4].ItemID; //move last item in this to convoy in this case
            MainData.Convoy[i]->ItemID = item;
            item = ItemID;
            CurrentCharacter[CharID].Inventory[4].ItemID = ItemID;
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
    if(&MainData == NULL)
    {
        return;
    }

    u16 i;
    for(i=0;i<= CONVOY_MAX_SIZE;i++)
    {
        if(MainData.Convoy[i]->ItemID == 0)
        {
            MainData.Convoy[i]->ItemID = ItemID;
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

    struct CharacterData Character[UINT16_MAX];

    //sanity checks so we never access unalocated memory thus causing segfault
    //TODO: ADD fprintf to stderr
    if(&Character == NULL)
    {
        return;
    }

    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

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

