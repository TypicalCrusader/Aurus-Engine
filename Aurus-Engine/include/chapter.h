/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "types.h"
#include "map.h"
#include "gaurusscript.h"

//taken from BINion
struct gpChapterData {
    u16 uChapterID;
    u16 uChapterNumber[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B    
    u32 uChapterName[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u32 uChapterDesc[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u32 uChapterObjectiveDisplay[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B        
    u8  uChapterWheather[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u8  uChapterUsesFOW[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u16 uMapIDs[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u16 uMapEventID[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B
    u16 uLeaderCharacterID[0x2];
        //00 - Base Path
        //01 - Path A
        //02 - Path B   
    u16 EventTable[0x2];
        /*this holds indexes of the event tables for this chapter
          this allows me to place this whole fucking table in binion
          rather than to bake it inside of exe
        */
};

static struct gpChapterData gCurrentChapter;