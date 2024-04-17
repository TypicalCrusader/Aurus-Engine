#pragma once

#include "types.h"

struct SkillStruct 
{
    u8 SkillID;
    char SkillName[50]; //this is just for yaml desc string
    char SkillDesc[50];
    char SkillEffect[50];
    u8 SkillActivation;
};

enum SkillActivation
{
    SKILL_ACTIVATION_PRE_BATTLE,
    SKILL_ACTIVATION_BATTLE,
    SKILL_ACTIVATION_POST_BATTLE,
    SKILL_ACTIVATION_OUTSIDE_BATTLE
};