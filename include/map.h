#pragma once

#include "types.h"
#include "char.h"
#include "battle.h"
#include <stdint.h>

#define MAX_MAP_SIZE                125
#define MAX_MAP_CHANGES             64
#define MAX_RECRUITABLE_PC_UNITS        50
#define MAX_POSSIBLE_RECRUITABLE_UNITS 100
#define MAX_DEPLOYED_PC_UNITS           16
#define MAX_DEPLOYED_ENEMY_UNITS        64
#define MAX_DEPLOYED_ALLY_UNITS         32
#define MAX_DEPLOYED_ALL_UNITS          MAX_DEPLOYED_PC_UNITS + MAX_DEPLOYED_ENEMY_UNITS + MAX_DEPLOYED_ALLY_UNITS

struct SelectedUnitData
{
    u8 DeploymentIndex;
    struct CharacterData *Unit;
    struct ClassStruct *Class;
    struct AIData *Ai;
    struct InventoryData *Inventory;
    u8 level;
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
    u8 MapX;
    u8 MapY;
};

extern struct SelectedUnitData SelectedUnit;
extern struct SelectedUnitData Actor;

typedef struct {
	u16 tile; 
    u8 TileType //just a type of tile
}MapTile;

typedef struct {
    u8 X;
    u8 Y;
    u8 sizeX;
    u8 sizeY;
    bool active;
}MapChange;

typedef struct
{
    u8 MapX;
    u8 MapY;
    MapTile *Tile[MAX_MAP_SIZE][MAX_MAP_SIZE]; //2d array why the fuck i havent realised this is good way to do it before i looked at fucking sdl2 tutorol....
    u8 UsedTileSet;
    u8 UsedPallete;
    MapChange *Mapchange[UINT8_MAX]; // offset list for map changes
}MapData;

struct CurrentMap
{
    u8 CurrentTurn; //256 max turns, here for redundancy, and the fact that some chapters are goin to have multiple maps
    u8 ChapterID; //Not Neccesarly needed but can be useful for script to distinguish which chapter events to run also additional redundancy
    MapData *Map;
    bool UseFOW;
    struct unitdata
    {
        u8 UnitID;
    }*EnemyUnit, *PlayerUnits, *AllyUnits;
    u8 MapEffect;
};

extern struct CurrentMap CurrMap;

enum TileType
{
    UNPASSABLE_MOUNTAIN, //also default one
    UNPASSABLE_DESERT_MOUNTAIN,
    UNPASSABLE_DESERT,
    UNPASSABLE_FOREST,
    UNPASSABLE_PLAIN,
    UNPASSABLE_RIVER,
    UNPASSABLE_WALL,
    UNPASSABLE_SEA,
    UNPASSABLE_BOG,
    UNPASSABLE_CITY,
    UNPASSABLE_VILLAGE,
    BREAKABLE_WALL,
    BREAKABLE_LOG,
    BREAKABLE_HILL, //TO CAUSE ROCK TUMBLING
    ENTERABLE_CITY,
    ENTERABLE_VILLAGE,
    ENTERABLE_HOME,    
    PASSABLE_PLAIN,
    PASSABLE_HILLS,
    PASSABLE_RIVER,
    PASSABLE_DESERT,
    PASSABLE_BOG,
    PASSABLE_HOME,
    SPECIAL_TYPE_THRONE,
    SPECIAL_TYPE_GUARD_POST,
    SPECIAL_TYPE_FORT,
    SPECIAL_TYPE_COLLUMN,
};

static inline void IncreaseTurnCounter()
{
    CurrMap.CurrentTurn += 1;
    return;
}
int InitialiseMap();
u8 MoveUnit(u8 MapX, u8 MapY);
inline u16 CheckTileType(u8 MapX, u8 MapY){
    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map->Tile[MapX][MapY] != NULL)
    {
        return CurrMap.Map->Tile[MapX][MapY]->tile;
    };
    return -1;
}
inline bool CheckMapChangeExists(u8 MapChange){
    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map->Mapchange[MapChange] != NULL)
    {
        return true;
    };
    return false;
}
inline void ChangeMapChange(u8 MapChange){
    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map->Mapchange[MapChange] != NULL)
    {
        CurrMap.Map->Mapchange[MapChange].active = true;
        return;
    };
    return;   
}
inline void ApplyMapEffect(u8 MapEffect)
{
    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    if(&CurrMap != NULL)
    {
        CurrMap.MapEffect = MapEffect;
        return;
    }
    return;
}
int ChangeMapMidChapter();
void ActivateMapSkill();
void AttackUnit(u16 EnemyUnitDevIndex);