/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>   

#define AURUS_MAP_MAX_SIZE  INT8_MAX //128 by 128
#define AURUS_MAP_TILE_SIZE 0xF //16x16

typedef enum { 
    TERRAIN_PLAIN       =  0,
    TERRAIN_FOREST      =  1,
    TERRAIN_MOUNTAIN    =  2,   // impassable to all but flyers
    TERRAIN_HILL        =  3,  
    TERRAIN_SEA         =  4,   // flyers and specific classes can move + people with skill
    TERRAIN_DESERT      =  5,
    TERRAIN_FORT        =  6,
    TERRAIN_WALL        =  7 ,  // impassable to all but flyers
    TERRAIN_VILLAGE     =  8 ,  
    TERRAIN_RIVER       =  9 ,  // flyers and specific classes can move + people with skill
    TERRAIN_FOREST_DEEP = 10,
    TERRAIN_TAIGA       = 11,

    TERRAIN_COUNT    
} eTerrainType;

typedef enum {
    MOVE_INFANTRY  = 0,    // normal
    MOVE_CAVALRY   = 1,    // horses
    MOVE_FLYING    = 2,    // pegasi, wyverns, dragons
    MOVE_ARMOR     = 3,    // heavy armor
    MOVE_OTHER     = 4,    // thieves/assassins 

    MOVE_COUNT
} eMovementType;

typedef enum {
    MOVE_IMPOSSIBLE = 0,
    MOVE_NORMAL     = 1,
    MOVE_COST_2     = 2,
    MOVE_COST_3     = 3,
    MOVE_COST_4     = 4,

    MOVE_COST_COUNT
} eMovementCost;


static const s32 terrain_costs[TERRAIN_COUNT][MOVE_COUNT] = {
    //           Infantry  Cavalry  Flying   Armor   Other
    /*Plain*/   { MOVE_NORMAL,        MOVE_NORMAL,       MOVE_NORMAL,       MOVE_NORMAL,      MOVE_NORMAL     },
    /*Forest*/  { MOVE_COST_2,        MOVE_COST_3,       MOVE_NORMAL,       MOVE_COST_4,      MOVE_NORMAL     },  
    /*Mountain*/{ MOVE_IMPOSSIBLE,        MOVE_IMPOSSIBLE,       MOVE_NORMAL,       MOVE_IMPOSSIBLE,      MOVE_IMPOSSIBLE     }, 
    /*Hill*/    { MOVE_COST_2,        MOVE_COST_3,       MOVE_NORMAL,        MOVE_COST_3,      MOVE_NORMAL     },
    /*Sea*/     { MOVE_IMPOSSIBLE,        MOVE_IMPOSSIBLE,       MOVE_NORMAL,       MOVE_IMPOSSIBLE,      MOVE_IMPOSSIBLE     },  
    /*Desert*/  { MOVE_COST_2,        MOVE_COST_4,       MOVE_NORMAL,       MOVE_COST_4,      MOVE_COST_2     },  
    /*Fort*/    { MOVE_COST_2,        MOVE_COST_2,       MOVE_NORMAL,       MOVE_COST_2,      MOVE_COST_2     },
    /*Wall*/    { MOVE_IMPOSSIBLE,        MOVE_IMPOSSIBLE,       MOVE_IMPOSSIBLE,       MOVE_IMPOSSIBLE,      MOVE_IMPOSSIBLE     }
};

struct gpTileData {
    u32 uTileGFX;
    u8 uTileType;
    u8 uMovCost;
};

struct gpMapStruct {
    struct gpTileData Tile[AURUS_MAP_MAX_SIZE][AURUS_MAP_MAX_SIZE];
    u8 uMapSizeX;
    u8 uMapSizeY;
    u32 uTileSet;
};

extern struct gpMapStruct Map;

static struct gpTileData gCurrentBattleTile;

typedef struct {
    s32 x, y;
} Point;

typedef struct {
    s32 g;          // cost from start
    s32 h;          // heuristic to goal
    s32 f;          // g + h
    Point parent;   // for path reconstruction
    bool closed;    // already processed
    bool in_open;   // optimization to avoid duplicates
} Node;

