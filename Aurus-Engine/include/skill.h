#pragma once
#include "types.h"

enum eSkillActivationType {
    SKILL_TYPE_PASSIVE,             //always active
    SKILL_TYPE_ACTIVE_PRE_BATTLE,   //activates Before battle begins
    SKILL_TYPE_ACTIVE_PHASE,        //activates During the character battle phase
    SKILL_TYPE_ACTIVE_POST_PHASE,   //activates During the enemy attack on the character
    SKILL_TYPE_ACTIVE_POST_BATTLE,  //activates when battle ends
    SKILL_TYPE_ACTIVE_MAP,          //activates on map
    SKILL_TYPE_ACTIVE_CHOICE,       //activates on map when player choses to - rally skills
};

//binion
struct gpSkillStruct {
    u16 uSkillID;                                   //skillID = Position in struct
    u64 uIconID;

    //text id
    u64 uNameTextID;                                //text id using enum label
    u64 uDescTextID;                                //text id using enum label

    u8 uSkillActivationType;                        //see eSkillActivationType for reference
    u8 uSkillElement;
    u32 uSkillEffectID;                             //skill effect ID, used as function argument (for active ones)
    s8 sActivationRate;                             //initial %chance to activate (is affected by luck). Ignored by SKILL_TYPE_ACTIVE_CHOICE
};