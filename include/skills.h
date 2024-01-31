#include "../include/types.h"

struct SkillStruct 
{
    u8 SkillID;
    u32 SkillName;
    u32 SkillDesc;
    u32 SkillEffect;
    u8 SkillActivation;
}Skills[UINT8_MAX];

enum SkillActivation
{
    SKILL_ACTIVATION_PRE_BATTLE,
    SKILL_ACTIVATION_BATTLE,
    SKILL_ACTIVATION_POST_BATTLE,
    SKILL_ACTIVATION_OUTSIDE_BATTLE
};