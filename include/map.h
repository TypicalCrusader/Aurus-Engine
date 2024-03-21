#include "types.h"
#include "char.h"
#include <stdint.h>

#define MAX_MAP_SIZE                125
#define MAX_MAP_CHANGES             64

#define MAX_DEPLOYED_PC_UNITS       16
#define MAX_DEPLOYED_ENEMY_UNITS    64
#define MAX_DEPLOYED_ALLY_UNITS     32

typedef struct
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
}SelectedUnit;

typedef struct {
	u16 tile; //just a type of tile
}MapTile;

typedef struct {
    u8 X;
    u8 Y;
    u8 sizeX;
    u8 sizeY;
}MapChange;

typedef struct
{
    u8 MapX;
    u8 MapY;
    MapTile *Tile[MAX_MAP_SIZE][MAX_MAP_SIZE]; //2d array why the fuck i havent realised this is good way to do it before i looked at fucking sdl2 tutorol....
    u8 UsedTileSet;
    u8 UsedPallete;
    MapChange *Mapchange[MAX_MAP_CHANGES]; // offset list for map changes
}MapData;

typedef struct
{
    u8 CurrentTurn; //256 max turns, here for redundancy
    u8 ChapterID; //Not Neccesarly needed but can be useful for script to distinguish which chapter events to run also additional redundancy
    MapData *Map;
    bool UseFOW;
    struct
    {
        u8 UnitID;
    }*EnemyUnit[MAX_DEPLOYED_ENEMY_UNITS], *PlayerUnits[MAX_DEPLOYED_PC_UNITS], *AllyUnits[MAX_DEPLOYED_ALLY_UNITS];
    struct 
    {
        u8 X;
        u8 Y;
    }*SelectedTile;
}CurrentMap;

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
    PASSABLE_PLAIN,
    PASSABLE_HILLS,
    PASSABLE_RIVER,
    PASSABLE_DESERT,
    PASSABLE_BOG,
    PASSABLE_HOME,
    BREAKABLE_WALL,
    BREAKABLE_LOG,
    BREAKABLE_HILL, //TO CAUSE ROCK TUMBLING
    ENTERABLE_CITY,
    ENTERABLE_VILLAGE,
    ENTERABLE_HOME,
    SPECIAL_TYPE_THRONE,
    SPECIAL_TYPE_GUARD_POST,
    SPECIAL_TYPE_FORT,
    SPECIAL_TYPE_COLLUMN
};