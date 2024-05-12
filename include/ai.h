#pragma once
#include "types.h"


enum AITypes{ //4Bytes
    //1ST BYTE
    AI1_NEVER_MOVE          = (1<<0), //AI1 AND 2 TAKE 4 BITS EACH
    AI1_ALWAYS_MOVE         = (1<<1),
    AI1_MOVE_IN_RANGE       = (1<<2),
    AI1_MOVE_AGRESSIVE      = (1<<3),
    AI2_NO_AGRESSIVE        = (1<<4),
    AI2_ALWAYS_ATTACK       = (1<<5),
    AI2_ATTACK_NORMAL       = (1<<6),
    AI2_ATTACK_CAUTIOUS     = (1<<7),
    //2ND BYTE
    AI3_NEVER_USE_ITEMS     = (1<<8),
    AI3_ALWAYS_USE_ITEMS    = (1<<9),
    AI3_USE_ITEMS_PRAGMATIC = (1<<10),
    AI3_USE_ITEMS_AGRESSIVE = (1<<11),
    AI3_USE_ITEMS_DEFENSIVE = (1<<12),
    AI3_USE_ITEMS_NORMAL    = (1<<13),
    AI3_USE_ITEMS_LOW_HP    = (1<<14),
    AI3_USE_ITEMS_DEBUG     = (1<<15),
    //3RD BYTE
    AI4_DEFENSIVE_AI_NONE   = (1<<16),
    AI4_DEFENSIVE_AI_LITE   = (1<<17),
    AI4_DEFENSIVE_AI_FULL   = (1<<18),
    AI4_DEFENSIVE_SPECIAL   = (1<<19),
    AI5_AGRESSIVE_AI_NONE   = (1<<20),
    AI5_AGRESSIVE_AI_LITE   = (1<<21),
    AI5_AGRESSIVE_AI_FULL   = (1<<22),
    AI5_AGRESSIVE_SPECIAL   = (1<<23),
    //4TH BYTE
    AI6_AI_SPECIAL_INNATH   = (1<<24),
    AI6_AI_SPECIAL_BOSS     = (1<<25),
    AI6_AI_SPECIAL_ALLY     = (1<<26),
    AI6_AI_SPECIAL_NONE     = (1<<27),
    //REMAINING 4 BITS RN ARE UNUSED
};

//move right u32 param value in spawn unit by 4 to get to AI2 8 to get to AI3 16 to get to AI4 20 to get to AI5 24 to get to AI 6
struct AIData
{
    u8 AI1     : 4;
    u8 AI2     : 4;
    u8 AI3     : 8;
    u8 AI4     : 4;
    u8 AI5     : 4;
    u8 AI6     : 4;
    u8 Padding : 4;
};