/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"
#include <time.h>
#include <stdlib.h>

bool USE_FASTCALL bIsNumberEven(u32 unumber);
u8 USE_FASTCALL uRoll2D100();
u8 USE_FASTCALL uRollD100();
u8 USE_FASTCALL uRollD20();
u8 USE_FASTCALL uRollD6();
u8 USE_FASTCALL uRollD4();
u8 USE_FASTCALL uRandom_u8_exclusive(u8 min, u8 max);
u8 USE_FASTCALL uRandom_u8_inclusive(u8 min, u8 max);