/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"

#define AURUS_MAP_MAX_SIZE = INT8_MAX //128 by 128
#define AURUS_MAP_TILE_SIZE = 0xF //16x16

struct gpTileData {
    u32 uTileGFX;
    u8 uTileType;
};

struct gpMapStruct {
    struct gpTileData Tile[INT8_MAX][INT8_MAX];
    u8 uMapSizeX;
    u8 uMapSizeY;
    u32 uTileSet;
};

extern struct gpMapStruct Map;

static struct gpTileData gCurrentBattleTile;