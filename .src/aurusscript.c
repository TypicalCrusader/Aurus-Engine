#include "../include/aurusscript.h"

void SetPermaFlagTo(u8 Flag, u8 SetUnset)
{
    u8 PermaFlags[UINT8_MAX];

    if ((SetUnset != 0) && (SetUnset != 1))
    {
        assert((SetUnset != 0) && (SetUnset != 1));
    };

    PermaFlags[Flag] = SetUnset;
    return;
};

void SetTempFlagto(u8 Flag, u8 SetUnset)
{
    u8 TempFlags[UINT8_MAX];

    if ((SetUnset != 0) && (SetUnset != 1))
    {
        assert((SetUnset != 0) && (SetUnset != 1));
    };

    TempFlags[Flag] = SetUnset;
    return;
};

void AddGoldToTeam(u16 GoldAmount)
{
    struct MainDataStruct MainData; 

    if (&MainData == NULL)
    {
        return;
    }

    if ((GoldAmount + MainData.CurrGold) > MAX_GOLD_AMOUNT)
    {
        return;
    }
    MainData.CurrGold += GoldAmount;
    return;
};

void AddItemToCharacter(u16 ItemID)
{
    u16 i;

    struct MainDataStruct MainData; 

    if(&MainData == NULL)
    {
        return;
    }

    struct SelectedUnitData SelectedUnit;

    if (&SelectedUnit == NULL)
    {
        return;
    }

    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if (&CurrentCharacter == NULL)
    {
        return;
    }

    u8 CharID = SelectedUnit.DeploymentIndex;

    if (CharID > MAX_DEPLOYED_ALL_UNITS)
    {
        return;
    }

    for (i = 0; i < 5; i++)
    {
        if (CurrentCharacter[CharID].Inventory[i] -> ItemID == 0)
        {
            CurrentCharacter[CharID].Inventory[i] -> ItemID = ItemID;
            return;
        }
    }
    for (i = 0; i <= CONVOY_MAX_SIZE; i++)
    {
        if (MainData.Convoy[i]->ItemID == 0)
        {
            u32 item = CurrentCharacter[CharID].Inventory[4] -> ItemID; // move last item in this to convoy in this case
            MainData.Convoy[i]->ItemID = item;
            item = ItemID;
            CurrentCharacter[CharID].Inventory[4] -> ItemID = ItemID;
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
    struct MainDataStruct MainData; 

    if (&MainData == NULL)
    {
        return;
    }

    u16 i;
    for (i = 0; i <= CONVOY_MAX_SIZE; i++)
    {
        if (MainData.Convoy[i]->ItemID == 0)
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

u16 AddXLevelsToCharacter(u8 Levels, u16 CharDepIndex)
{
    struct CharacterData Character[UINT16_MAX];

    // sanity checks so we never access unalocated memory thus causing segfault
    // TODO: ADD fprintf to stderr
    if (&Character == NULL)
    {
        return -1;
    }

    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if (&CurrentCharacter == NULL)
    {
        return -1;
    }

    if (CharDepIndex > MAX_DEPLOYED_ALL_UNITS)
    {
        return -1;
    }

    u8 i;
    for (i = 0; Levels <= i; i++)
    {
        CurrentCharacter[CharDepIndex].CurrAtk += IncreaseStat(CurrentCharacter[CharDepIndex].CurrAtk, CurrentCharacter[CharDepIndex].CharData->AtkCharGrowth);
        CurrentCharacter[CharDepIndex].CurrMag += IncreaseStat(CurrentCharacter[CharDepIndex].CurrMag, CurrentCharacter[CharDepIndex].CharData->MagCharGrowth);
        CurrentCharacter[CharDepIndex].MaxHP += IncreaseStat(CurrentCharacter[CharDepIndex].CurrHp, CurrentCharacter[CharDepIndex].CharData->HpCharGrowth);
        CurrentCharacter[CharDepIndex].CurrDef += IncreaseStat(CurrentCharacter[CharDepIndex].CurrDef, CurrentCharacter[CharDepIndex].CharData->DefCharGrowth);
        CurrentCharacter[CharDepIndex].CurrMagDef += IncreaseStat(CurrentCharacter[CharDepIndex].CurrMagDef, CurrentCharacter[CharDepIndex].CharData->MagDefCharGrowth);
        CurrentCharacter[CharDepIndex].CurrSpd += IncreaseStat(CurrentCharacter[CharDepIndex].CurrSpd, CurrentCharacter[CharDepIndex].CharData->SpdCharGrowth);
        CurrentCharacter[CharDepIndex].CurrLck += IncreaseStat(CurrentCharacter[CharDepIndex].CurrLck, CurrentCharacter[CharDepIndex].CharData->LckCharGrowth);
        CurrentCharacter[CharDepIndex].CurrDex += IncreaseStat(CurrentCharacter[CharDepIndex].CurrDex, CurrentCharacter[CharDepIndex].CharData->DexCharGrowth);
        CurrentCharacter[CharDepIndex].CurrLvl += 1;
    }
    return 0;
}

void SpawnUnit(u16 CharID, u16 ClassID, u8 level, u8 Faction, u32 AI, u16 Inventory[0x5], u16 Skills[0x5], u8 MapX, u8 MapY, bool TakeDataFromSave)
{

    struct CharacterData Character[UINT16_MAX];

    // sanity checks so we never access unalocated memory thus causing segfault
    // TODO: ADD fprintf to stderr
    if (&Character == NULL)
    {
        return;
    }

    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if (&CurrentCharacter == NULL)
    {
        return;
    }
    if (&CurrentCharacter[0].UnitID == NULL) // somehow its unalocated thus something broke
    {
        return;
    }
    if (&CurrentCharacter[MAX_DEPLOYED_ALL_UNITS].UnitID == NULL)
    {
        return;
    }
    if (CurrentCharacter[MAX_DEPLOYED_ALL_UNITS].UnitID >= 0)
    {
        return;
    }

    struct ClassStruct Class[UINT16_MAX];

    if (&Class == NULL)
    {
        return;
    }

    struct RaceStruct Race[RACESAMOUNT];

    if (&Race == NULL)
    {
        return;
    }

    if (MapY > MAX_MAP_SIZE || MapY > MAX_MAP_SIZE)
    {
        return;
    }

    u8 i;

    for (i = 0; &CurrentCharacter[i].UnitID != NULL; i++)
    {
        // just a loop until first free character
        if(&CurrentCharacter[i].UnitID == NULL)
        {
            break;
        }
    }

    if (i >= MAX_DEPLOYED_ALL_UNITS && &CurrentCharacter[i].UnitID != NULL)
    {
        // todo insert warning that trying to add chars over limit thus ignoring
        return;
    }

    if (TakeDataFromSave == true && &CurrentCharacter[i].UnitID == NULL)
    {
        // todo take data from save
        return;
    }

    if (&CurrentCharacter[i] == NULL)
    {
        CurrentCharacter[i].DevelopmentIndex = i;
        CurrentCharacter[i].UnitID = Character[CharID].UnitID;
        CurrentCharacter[i].CharData = &Character[CharID];
        CurrentCharacter[i].ClassData = &Class[ClassID];
        CurrentCharacter[i].Race = &Race[Character[CharID].RaceID];
        CurrentCharacter[i].MiscData.gender = Character[CharID].CharGender;
        CurrentCharacter[i].MiscData.MapX = MapX;
        CurrentCharacter[i].MiscData.MapY = MapY;
        CurrentCharacter[i].MiscData.Faction = Faction;
        CurrentCharacter[i].MiscData.AI.AI1 = AI;
        CurrentCharacter[i].MiscData.AI.AI2 = AI << 4;
        CurrentCharacter[i].MiscData.AI.AI3 = AI << 8;
        CurrentCharacter[i].MiscData.AI.AI4 = AI << 16;
        CurrentCharacter[i].MiscData.AI.AI5 = AI << 20;
        CurrentCharacter[i].MiscData.AI.AI6 = AI << 24;
        CurrentCharacter[i].MiscData.AI.Padding = (u8)0xF;
        AddXLevelsToCharacter(level, i);
        CurrentCharacter[i].CurrHp =  CurrentCharacter[i].MaxHP;

    }

    return;
}

void KillCharacter(u16 CharID)
{
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL)
    {
        return;
    }

    if(CharID > MAX_DEPLOYED_ALL_UNITS)
    {
        return;
    }

    if (&CurrentCharacter[CharID] == NULL)
    {
        free(&CurrentCharacter[CharID].DevelopmentIndex);
        free(&CurrentCharacter[CharID].UnitID);
        free(&CurrentCharacter[CharID].CharData);
        free(&CurrentCharacter[CharID].ClassData);
        free(&CurrentCharacter[CharID].Inventory);
        free(&CurrentCharacter[CharID].Race);
        free(&CurrentCharacter[CharID].MiscData);
        free(&CurrentCharacter[CharID].CurrHp);
        free(&CurrentCharacter[CharID].CurrentSkills);
        free(&CurrentCharacter[CharID].MaxHP);
        free(&CurrentCharacter[CharID].CurrHp);
        free(&CurrentCharacter[CharID].CurrAtk);
        free(&CurrentCharacter[CharID].CurrMag);
        free(&CurrentCharacter[CharID].CurrDef);
        free(&CurrentCharacter[CharID].CurrMagDef);
        free(&CurrentCharacter[CharID].CurrSpd);
        free(&CurrentCharacter[CharID].CurrLck);
        free(&CurrentCharacter[CharID].CurrDex);
        free(&CurrentCharacter[CharID].CurrSwrd);
        free(&CurrentCharacter[CharID].CurrDgr);
        free(&CurrentCharacter[CharID].CurrSpr);
        free(&CurrentCharacter[CharID].CurrAxe);
        free(&CurrentCharacter[CharID].CurrThrow);
        free(&CurrentCharacter[CharID].CurrBow);
        free(&CurrentCharacter[CharID].CurrLight);
        free(&CurrentCharacter[CharID].CurrDark);
        free(&CurrentCharacter[CharID].CurrWind);
        free(&CurrentCharacter[CharID].CurrFire);
        free(&CurrentCharacter[CharID].CurrWater);
        free(&CurrentCharacter[CharID].CurrIce);
        free(&CurrentCharacter[CharID].CurrThunder);
        free(&CurrentCharacter[CharID].CurrEarth);
        free(&CurrentCharacter[CharID].CurrStaves);
        free(&CurrentCharacter[CharID].CurrStone);
        free(&CurrentCharacter[CharID].CurrLvl);
    }   

    return;
}

void ChangeClass(u8 DeploymentIndex, u16 ClassID)
{
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL)
    {
        return;
    }

    if(&CurrentCharacter[DeploymentIndex].UnitID == NULL )
    {
        return;
    }

    struct ClassStruct Class[UINT16_MAX];

    if(&Class == NULL)
    {
        return;
    }

    if(&Class[ClassID].ClassID == NULL)
    {
        return;
    }

    CurrentCharacter[DeploymentIndex].ClassData = &Class[ClassID];
}
void ChangeSide(u8 Side, u8 DeploymentIndex){
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL)
    {
        return;
    }

    if(&CurrentCharacter[DeploymentIndex].UnitID == NULL )
    {
        return;
    }

    CurrentCharacter[DeploymentIndex].MiscData.Faction = Side;

    return;
}

u8 MapEvent(u8 EventType, u8 MapX, u8 MapY, int(*FunctionPointer)(u8))
{
    /*
        NOTE FOR MYSELF

        TRY NOT TO USE HECKING FUNC POINT HERE

        WHAT I CAN DO IS DO GENERIC 4th ARG THAT STATES
        -ID of Dialogue
        -ID of MapChange    
        -AMOUNT OF HEALTH TO HEAL 
    */


    if(EventType > 6)
    {
        return -1
    }

    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    if(CurrMap.Map->MapX < MapX)
    {
        return -1;
    }    

    if(CurrMap.Map->MapY < MapY)
    {
        return -1;
    }

    switch (EventType)
    {
    case 0:

    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    default:
        return -1;
    }


    if(&FunctionPointer == NULL)
    {
        return -1;
    }


}