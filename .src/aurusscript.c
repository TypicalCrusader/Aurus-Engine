#include "../include/aurusscript.h"

inline void SetPermaFlagTo(u8 Flag, u8 SetUnset)
{
    if ((SetUnset != 0) && (SetUnset != 1))
    {
        assert((SetUnset != 0) && (SetUnset != 1));
    };

    PermaFlags[Flag] = SetUnset;
    return;
};

void SetTempFlagto(u8 Flag, u8 SetUnset)
{
    if ((SetUnset != 0) && (SetUnset != 1))
    {
        assert((SetUnset != 0) && (SetUnset != 1));
    };

    TempFlags[Flag] = SetUnset;
    return;
};

void AddGoldToTeam(u16 GoldAmount)
{
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
        if (CurrentCharacter[CharID].Inventory[i].ItemID == 0)
        {
            CurrentCharacter[CharID].Inventory[i].ItemID = ItemID;
            return;
        }
    }
    for (i = 0; i <= CONVOY_MAX_SIZE; i++)
    {
        if (MainData.Convoy[i]->ItemID == 0)
        {
            u32 item = CurrentCharacter[CharID].Inventory[4].ItemID; // move last item in this to convoy in this case
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
        CurrentCharacter[i].MiscData.AI.AI1 = (u8)AI;
        CurrentCharacter[i].MiscData.AI.AI2 = (u8)AI << 4;
        CurrentCharacter[i].MiscData.AI.AI3 = (u8)AI << 8;
        CurrentCharacter[i].MiscData.AI.AI4 = (u8)AI << 16;
        CurrentCharacter[i].MiscData.AI.AI5 = (u8)AI << 20;
        CurrentCharacter[i].MiscData.AI.AI6 = (u8)AI << 24;
        CurrentCharacter[i].MiscData.AI.Padding = (u8)0xF;
        AddXLevelsToCharacter(level, i);
        CurrentCharacter[i].CurrHp =  CurrentCharacter[i].MaxHP;

    }

    return;
}

void KillCharacter(u16 CharID)
{
    if (&CurrentCharacter[CharID] == NULL)
    {
        &CurrentCharacter[CharID].DevelopmentIndex = NULL;
        &CurrentCharacter[CharID].UnitID = NULL;
        &CurrentCharacter[CharID].CharData = NULL;
        &CurrentCharacter[CharID].ClassData = NULL;
        &CurrentCharacter[CharID].Inventory = NULL;
        &CurrentCharacter[CharID].Race = NULL;
        &CurrentCharacter[CharID].MiscData = NULL
        &CurrentCharacter[CharID].CurrHp = NULL;
        &CurrentCharacter[CharID].CurrentSkills = NULL;
        &CurrentCharacter[CharID].MaxHP = NULL;
        &CurrentCharacter[CharID].CurrHp = NULL;
        &CurrentCharacter[CharID].CurrAtk = NULL;
        &CurrentCharacter[CharID].CurrMag = NULL;
        &CurrentCharacter[CharID].CurrDef = NULL;
        &CurrentCharacter[CharID].CurrMagDef = NULL;
        &CurrentCharacter[CharID].CurrSpd = NULL;
        &CurrentCharacter[CharID].CurrLck = NULL;
        &CurrentCharacter[CharID].CurrDex = NULL;
        &CurrentCharacter[CharID].CurrSwrd = NULL;
        &CurrentCharacter[CharID].CurrDgr = NULL;
        &CurrentCharacter[CharID].CurrSpr = NULL;
        &CurrentCharacter[CharID].CurrAxe = NULL;
        &CurrentCharacter[CharID].CurrThrow = NULL;
        &CurrentCharacter[CharID].CurrBow = NULL;
        &CurrentCharacter[CharID].CurrLight = NULL;
        &CurrentCharacter[CharID].CurrDark = NULL;
        &CurrentCharacter[CharID].CurrWind = NULL;
        &CurrentCharacter[CharID].CurrFire = NULL;
        &CurrentCharacter[CharID].CurrWater = NULL;
        &CurrentCharacter[CharID].CurrIce = NULL;
        &CurrentCharacter[CharID].CurrThunder = NULL;
        &CurrentCharacter[CharID].CurrEarth = NULL;
        &CurrentCharacter[CharID].CurrStaves = NULL;
        &CurrentCharacter[CharID].CurrStone = NULL;
        &CurrentCharacter[CharID].CurrLvl = NULL;
    }   

    return;
}