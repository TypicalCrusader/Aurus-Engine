#pragma once

#include "types.h"

struct DialogueDataEntry
{
    char DialogueData[50]; //Yaml Entry 
};

enum SpecialChars
{
    ENUM_SPECIAL_NEW_LINE,
    ENUM_SPECIAL_END_ENTRY,
    ENUM_SPECIAL_MID_ENTRY_EVENT,
    ENUM_SPECIAL_CHANGE_COLOR,
    ENUM_SPECIAL_DISPLAY_VALUE,
    ENUM_SPECIAL_DISPLAY_GOLD,
    ENUM_SPECIAL_BEGIN_NARROW,
    ENUM_SPECIAL_END_NARROW
};

const char *SpecialCharacters[] //aka how engine interepretes [COMMAND]
{
    [ENUM_SPECIAL_NEW_LINE]         = "[N]",
    [ENUM_SPECIAL_END_ENTRY]        = "[EE]",
    [ENUM_SPECIAL_MID_ENTRY_EVENT]  = "[ME]",
    [ENUM_SPECIAL_CHANGE_COLOR]     = "[CC]",
    [ENUM_SPECIAL_DISPLAY_VALUE]    = "[DV]", 
    [ENUM_SPECIAL_DISPLAY_GOLD]     = "[DG]",
    [ENUM_SPECIAL_BEGIN_NARROW]     = "[BN]",
    [ENUM_SPECIAL_END_NARROW]       = "[EN]"
};