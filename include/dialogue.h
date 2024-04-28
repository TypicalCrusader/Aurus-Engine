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
    ENUM_SPECIAL_END_NARROW,
    ENUM_SPECIAL_DISPLAY_CHARACTER,
    ENUM_SPECIAL_DISPLAY_CHARACTER_LOCATION,
    ENUM_SPECIAL_START_BOLD,
    ENUM_SPECIAL_END_BOLD,
    ENUM_SPECIAL_START_ITALIC,
    ENUM_SPECIAL_END_ITALIC,
    ENUM_SPECIAL_DISPLAY_CHAR_NAME,
};

const char *SpecialCharacters[] //aka how engine interepretes [COMMAND]
{
    [ENUM_SPECIAL_NEW_LINE]                     = "[NL]",
    [ENUM_SPECIAL_END_ENTRY]                    = "[EE]",
    [ENUM_SPECIAL_MID_ENTRY_EVENT]              = "[ME]",
    [ENUM_SPECIAL_CHANGE_COLOR]                 = "[CC]",
    [ENUM_SPECIAL_DISPLAY_VALUE]                = "[DV]", 
    [ENUM_SPECIAL_DISPLAY_GOLD]                 = "[DG]",
    [ENUM_SPECIAL_BEGIN_NARROW]                 = "[BN]",
    [ENUM_SPECIAL_END_NARROW]                   = "[EN]",
    [ENUM_SPECIAL_DISPLAY_CHARACTER]            = "[DC]",
    [ENUM_SPECIAL_DISPLAY_CHARACTER_LOCATION]   = "[CL]",
    [ENUM_SPECIAL_START_BOLD]                   = "[SB]",
    [ENUM_SPECIAL_END_BOLD]                     = "[EB]",
    [ENUM_SPECIAL_START_ITALIC]                 = "[SI]",
    [ENUM_SPECIAL_END_ITALIC]                   = "[EI]",
    [ENUM_SPECIAL_DISPLAY_CHAR_NAME]            = "[DC]"
};