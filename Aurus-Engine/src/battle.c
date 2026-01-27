/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "battle.h"
#include "character.h"
#include "rng.h"
#include "skill.h"

struct gpBattleCharacter gAttackerCharacter;
struct gpBattleCharacter gDefenderCharacter;
struct gpBattleState gBattle;

void vCreateBattleStructs(struct gpCurrentCharacter *gAttacker, struct gpCurrentCharacter *gDefender) {
    struct gpBattleCharacter gAttackerCharacter = {
        .gCharacter = gAttacker,
        .gCharacterWeapon = gAttacker -> gCharacterInventory[0],
        .uCurrentHP = gAttacker -> uCurrentHP,
        .uMaxHP = gAttacker -> uMaxHP,
        .sAttackDamage = gAttacker -> gCharacterInventory[0].uWpnBaseDamage,
        .sBaseHitRate = gAttacker -> gCharacterInventory[0].uWpnAccuracy,
    };
    struct gpBattleCharacter gDefenderCharacter = {
        .gCharacter = gDefender,
        .gCharacterWeapon = gDefender -> gCharacterInventory[0],
        .uCurrentHP = gDefender -> uCurrentHP,
        .uMaxHP = gDefender -> uMaxHP,
        .sAttackDamage = gDefender -> gCharacterInventory[0].uWpnBaseDamage,
        .sBaseHitRate = gDefender -> gCharacterInventory[0].uWpnAccuracy,
    };
    struct gpBattleState gBattle = {
        .uBattleState = BATTLE_STATE_INITIALISED,
        .uBattleBackground = 0, //uGetBattleBackgroundFromTileGFX(gCurrentBattleTile), //!TODO: Replace with func getting it from map tile -> based on tiles of both sides
        .uBattleForeground = 0, //uGetBattleForegroundFromTileGFX(gCurrentBattleTile), //!TODO: -||- -> based on tiles of both sides
        .uBattleWheather = 0 //gCurrentChapter.uChapterWheather[uGetCurrentPath()],           //!TODO: -||- -> based on chapter data
    };
};

// damage before any skills/effects and defense beside effectiveness
void __attribute__ ((sseregparm)) __attribute__((hot)) vInitialBattleCalc(){
    //formula is:
    // Melee and Ranged  Wpns - (Wpn DMG * ([0.2 * STR/AGI/MAG (if above 10)]) OR Wpn DMG * (0.5 * STR/AGI/MAG)) - 0.5 P/MDef
    // Most Tomes - Wpn DMG * ((0.5 * Mag)- [uRollD100(0-50) + (0.5 Lck)= result * -0.01] else [result * 0.01] )
    // Dawn/Dusk Tomes - Wpn DMG - [uRollD6(0-2) = lck * -0.5] or + [lck * 0.5]
    // Dragon stones - Wpn DMG + (0.8 * Mag)
    // Staves = flat 0
    //After that subtract P/Mdef * 0.5/1 (depending on d20 roll)

    struct gpBattleCharacter gCurrentTurnAttacker = GetCurrentActiveBattleCharacter();
    struct gpBattleCharacter gCurrentTurnDefender;

    if(gCurrentTurnAttacker.gCharacter->gCharacter->uCharacterIndex == gAttackerCharacter.gCharacter->gCharacter->uCharacterIndex)
    {
        gCurrentTurnDefender = gDefenderCharacter;
    }
    else 
    {
        gCurrentTurnDefender = gAttackerCharacter;        
    }

    u8 uRNGRoll;

    //then return stat number
    u8 uCharacterAtkStat = uGetItemWpnATKAttributeMod(gCurrentTurnAttacker.gCharacterWeapon.uItemId);
    //get item type
    u8 uCharacterWeaponAtkType = uGetItemAtkType(gCurrentTurnAttacker.gCharacterWeapon.uItemId);

    switch (uCharacterWeaponAtkType)
    {
        case WEAPON_TYPE_MELEE_AND_RANGED:
            //Wpn DMG * ([0.2 * STR/AGI/MAG (if above 10)]) OR Wpn DMG * (0.5 * STR/AGI/MAG)) - 0.5 P/MDef
            if(uCharacterAtkStat <= 10)
            {
                gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + (uCharacterAtkStat * 0.2);
                break;                
            }
            else{
                gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + (uCharacterAtkStat * 0.5);
                break;  
            };
            break;
        case WEAPON_TYPE_TOME:
            //Wpn DMG * ((0.5 * Mag)- [uRollD100(0-50) + (0.5 Lck)= result * -0.01] else [result * 0.01] )
            if(uRollD100() <= 50)
            {
                gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + ((uCharacterAtkStat * 0.5) + (0.5 * gCurrentTurnDefender.gCharacter->sCurrentLck));
                break;                
            }
            gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + ((uCharacterAtkStat * 0.5) * (0.01 * gCurrentTurnDefender.gCharacter->sCurrentLck));            
            break;
        case WEAPON_TYPE_DUSK_DAWN:
            //Wpn DMG + (0.8 MAG -[uRollD6(0-2) = lck * -0.5] or +[lck * 0.5])
            if(uRollD6() <= 3)
            {
                gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + ((uCharacterAtkStat * 0.8) - (0.5 * gCurrentTurnDefender.gCharacter->sCurrentLck));
                break;                
            }
            gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + ((uCharacterAtkStat * 0.8) + (0.5 * gCurrentTurnDefender.gCharacter->sCurrentLck));     
            break;
        case WEAPON_TYPE_DRAGONSTONE:
            // Dragon stones - Wpn DMG + (0.8 * Mag)
            gCurrentTurnAttacker.sAttackDamage = gCurrentTurnDefender.sAttackDamage + (uCharacterAtkStat * 0.8);                        
            break;
        case WEAPON_TYPE_STAVE:
            //0
            gCurrentTurnAttacker.sAttackDamage = 0;                                    
            break;                                            
        default:
            break;
    }

    if(bGetCurrentBattleCharacter() == BATTLE_TURN_ATTACKER){
        gAttackerCharacter.sAttackDamage = gCurrentTurnAttacker.sAttackDamage;
    }
    else {
        gDefenderCharacter.sAttackDamage = gCurrentTurnAttacker.sAttackDamage;       
    }
    return;
};

void USE_FASTCALL vInitialAttackAccuracy() {
    struct gpBattleCharacter gCurrentTurnAttacker = GetCurrentActiveBattleCharacter();
    u8 uRNGRoll;

    //check if attacker item is not weapon or stave
    if(gCurrentTurnAttacker.gCharacterWeapon.uItemType < ITEM_TYPE_WEAPON_SWORD)
    {
        if(bGetCurrentBattleCharacter() == BATTLE_TURN_ATTACKER){
            gAttackerCharacter.sBaseHitRate = 0;
            return;
        }
        gDefenderCharacter.sBaseHitRate = 0;       
    
        return;
    }
    if(bGetCurrentBattleCharacter() == BATTLE_TURN_ATTACKER){
        gAttackerCharacter.sBaseHitRate = gCurrentTurnAttacker.gCharacterWeapon.uWpnAccuracy - sGetCharacterEvasionStat(gCurrentTurnAttacker.gCharacterWeapon,gDefenderCharacter);
        return;
    }
    gDefenderCharacter.sBaseHitRate = gCurrentTurnAttacker.gCharacterWeapon.uWpnAccuracy - sGetCharacterEvasionStat(gCurrentTurnAttacker.gCharacterWeapon,gAttackerCharacter);       
    return;
};

// damage + weakness table
void __attribute__ ((sseregparm)) vFinalBattleCalc(){

    struct gpBattleCharacter gCurrentTurnAttacker = GetCurrentActiveBattleCharacter();
    struct gpBattleCharacter gCurrentTurnDefender;

    if(gCurrentTurnAttacker.gCharacter->gCharacter->uCharacterIndex == gAttackerCharacter.gCharacter->gCharacter->uCharacterIndex)
    {
        gCurrentTurnDefender = gDefenderCharacter;
    }
    else 
    {
        gCurrentTurnDefender = gAttackerCharacter;        
    }

    if(gWeaponWeakness[gCurrentTurnAttacker.gCharacterWeapon.uItemType].uStrongAgainst == gCurrentTurnDefender.gCharacterWeapon.uItemType)
    {
        gCurrentTurnAttacker.sAttackDamage = gCurrentTurnAttacker.sAttackDamage * gWeaponWeakness[gCurrentTurnAttacker.gCharacterWeapon.uItemType].fBaseNeutralDamage;
    }
    else if(gWeaponWeakness[gCurrentTurnAttacker.gCharacterWeapon.uItemType].uWeakAgainst == gCurrentTurnDefender.gCharacterWeapon.uItemType)
    {
        gCurrentTurnAttacker.sAttackDamage = gCurrentTurnAttacker.sAttackDamage * WEAPON_DAMAGE_HALF_DAMAGE;
    }

    if(bGetCurrentBattleCharacter() == BATTLE_TURN_ATTACKER){
        gAttackerCharacter.sAttackDamage = gCurrentTurnAttacker.sAttackDamage;
    }
    else {
        gDefenderCharacter.sAttackDamage = gCurrentTurnAttacker.sAttackDamage;       
    }

    return;
};

//function name is taken from skill name
//skill to binion parser stores the skill name from gpSkillStruct.cInternalName
void vApplyMidBattleSkills(u16 uSkillID,u16 uSkillEffectID) {
    


    return;
}

//character attacks
void vDoHit() {

    if(uRollD100()<= GetCurrentActiveBattleCharacter().sBaseHitRate) //hit
    {
        //check crit
        if(uRollD100() <= GetCurrentActiveBattleCharacter().gCharacterWeapon.uWpnCriticalChance)
        {
            vCalcHit(ATTACK_HIT_CRITICAL);
            return;
        }
        vCalcHit(ATTACK_HIT_NORMAL);
        return;
    }
    else { //miss
        vCalcHit(ATTACK_HIT_MISS);
        return;
    }
    return;
}

//character does or does not damage
//!TODO: Display Animation and text *beside stubs*
void vCalcHit(u8 uDidAttackHit) {
    switch (uDidAttackHit)
    {
    case ATTACK_HIT_MISS:
        //vPlayAnimation(); 
        //vDisplayGFX();

        break;
    case ATTACK_HIT_NORMAL:
        //vPlayAnimation(); // <- will have anim name plopped here when first BINION + AAM build will be done
        //vDisplayGFX();

        if(bGetCurrentBattleCharacter() == true) {
            gDefenderCharacter.uCurrentHP -= gAttackerCharacter.sAttackDamage;
        }  
        else {
            gAttackerCharacter.uCurrentHP -= gDefenderCharacter.sAttackDamage;            
        }              
        break;
    case ATTACK_HIT_CRITICAL:
        //vPlayAnimation(); 
        //vDisplayGFX();

        if(bGetCurrentBattleCharacter() == true) {
            gDefenderCharacter.uCurrentHP -= (WEAPON_DAMAGE_CRITICAL_DAMAGE * gAttackerCharacter.sAttackDamage);
        }                
        else {
            gAttackerCharacter.uCurrentHP -= (WEAPON_DAMAGE_CRITICAL_DAMAGE * gDefenderCharacter.sAttackDamage);            
        }
        break;            
    default:
        break;
    }
    return;
}

void vMoveBattleState() {
    if (gBattle.uBattleState == BATTLE_STATE_ENDING) {
        return;
    }
    gBattle.uBattleState = gBattle.uBattleState += 1;
    return;
}

void vApplyPostBattleSkills(u16 uSkillID,u16 uSkillEffectID) {
    if(uSkillID == 0xFFFF)
    {
        exit(-1);
    }
    if(uSkillEffectID == 0xFFFF)
    {
        exit(-1);
    }

    gSkillFunc func = gSkillJumpTable[uSkillEffectID];

    if(func== NULL)
    {
        exit(-1);
    }

    func(uSkillID);

    return;
}

void vApplyPreBattleSkills(u16 uSkillID,u16 uSkillEffectID) {
    if(uSkillID == 0xFFFF)
    {
        exit(-1);
    }
    if(uSkillEffectID == 0xFFFF)
    {
        exit(-1);
    }

    gSkillFunc func = gSkillJumpTable[uSkillEffectID];

    if(func== NULL)
    {
        exit(-1);
    }

    func(uSkillID);

    return;    
}

void vApplyPostHitSkills(u16 uSkillID,u16 uSkillEffectID) {
    if(uSkillID == 0xFFFF)
    {
        exit(-1);
    }
    if(uSkillEffectID == 0xFFFF)
    {
        exit(-1);
    }

    gSkillFunc func = gSkillJumpTable[uSkillEffectID];

    if(func== NULL)
    {
        exit(-1);
    }

    func(uSkillID);

    return;    
}

void vApplyOnHitSkills(u16 uSkillID,u16 uSkillEffectID) {
    if(uSkillID == 0xFFFF)
    {
        exit(-1);
    }
    if(uSkillEffectID == 0xFFFF)
    {
        exit(-1);
    }

    gSkillFunc func = gSkillJumpTable[uSkillEffectID];

    if(func== NULL)
    {
        exit(-1);
    }

    func(uSkillID);

    return;    
}

u8 uReturnSkillAmountOnCharacterPerType(struct gpBattleCharacter gBattleCharacter, u8 uSkillActivationType, struct gBINionEntryStruct gSkillTable) {
    u8 uAmount;
    if(gBattleCharacter.gCharacter->uCharacterSkills[0] == CHARACTER_HAS_NO_SKILLS)
    {
        return 1;
    }
    u8 i;

    struct gpSkillStruct CLEANUP(free_skill_struct) *gSkill = malloc(sizeof(*gSkill));
    u8 CLEANUP(free_number) *gBuffer = malloc(sizeof(*gSkill));

    for(i = 0; i < MAX_CHARACTER_SKILLS;i++)
    {
        memcpy(gBuffer,&gSkillTable.uEntryData[(sizeof(*gSkill) * gBattleCharacter.gCharacter->uCharacterSkills[i])],sizeof(*gSkill));
        memcpy(gSkill,&gBuffer,sizeof(*gSkill));        
        if(gBattleCharacter.gCharacter->uCharacterSkills[i] == CHARACTER_HAS_NO_SKILLS)
        {
            break;
        }    

        if(gSkill->uSkillActivationType == uSkillActivationType ) {             
            uAmount++;
        }
    }
    return uAmount;
}

struct gpSkillStruct gReturnSkillStructsDependantOnPhase(struct gpBattleCharacter gBattleCharacter, u8 uSkillActivationType, u32 uSizeOfStruct, struct gBINionEntryStruct gSkillTable) {
    struct gpSkillStruct CLEANUP(free_skill_struct) *gTempSkillStruct = malloc(uSizeOfStruct);
    if(gBattleCharacter.gCharacter->uCharacterSkills[0] == CHARACTER_HAS_NO_SKILLS)
    {
        exit(-1);
    }
    u8 i = 0;
    u8 x = 0;

    struct gpSkillStruct CLEANUP(free_skill_struct) *gSkill = malloc(sizeof(*gSkill));
    u8 CLEANUP(free_number) *gBuffer = malloc(sizeof(*gSkill));    

    while(i<=uSizeOfStruct)
    {
        if(x>uSizeOfStruct)
        {
            break;
        }
        memcpy(gBuffer,&gSkillTable.uEntryData[(sizeof(*gSkill) * gBattleCharacter.gCharacter->uCharacterSkills[x])],sizeof(*gSkill));
        memcpy(gSkill,&gBuffer,sizeof(*gSkill));          
        if(gSkill->uSkillActivationType == uSkillActivationType)
        {
            gTempSkillStruct[i] = *gSkill;
            i++;
        }
        x++;
    }
    return *gTempSkillStruct;
}


//!TODO: Add ability handling if you attacked using one
void USE_FASTCALL HOT_FUNC vBattleLoop(struct gpCurrentCharacter *gAttacker, struct gpCurrentCharacter *gDefender) {
    vCreateBattleStructs(gAttacker, gDefender);

    struct gBINionEntryStruct gSkillTable = gGetBINionEntryStruct(DATA_BINION_SKILL);

    //this allocates between 512 and 2560 bytes (the latter case will never happen as you can only have at most 5 skills)
    //this whole code block is abomination btw
    u8 uSkillAmountPreBattleAtk =  uReturnSkillAmountOnCharacterPerType(gAttackerCharacter,SKILL_TYPE_ACTIVE_PRE_BATTLE,gSkillTable);
    u8 uSkillAmountActiveAtk = uReturnSkillAmountOnCharacterPerType(gAttackerCharacter,SKILL_TYPE_ACTIVE_PHASE,gSkillTable);
    u8 uSkillAmountPostActiveAtk = uReturnSkillAmountOnCharacterPerType(gAttackerCharacter,SKILL_TYPE_ACTIVE_POST_PHASE,gSkillTable);
    u8 uSkillAmountPostBattleAtk = uReturnSkillAmountOnCharacterPerType(gAttackerCharacter,SKILL_TYPE_ACTIVE_POST_BATTLE,gSkillTable);

    u8 uSkillAmountPreBattleDef =  uReturnSkillAmountOnCharacterPerType(gDefenderCharacter,SKILL_TYPE_ACTIVE_PRE_BATTLE,gSkillTable);
    u8 uSkillAmountActiveDef = uReturnSkillAmountOnCharacterPerType(gDefenderCharacter,SKILL_TYPE_ACTIVE_PHASE,gSkillTable);
    u8 uSkillAmountPostActiveDef= uReturnSkillAmountOnCharacterPerType(gDefenderCharacter,SKILL_TYPE_ACTIVE_POST_PHASE,gSkillTable);
    u8 uSkillAmountPostBattleDef =  uReturnSkillAmountOnCharacterPerType(gDefenderCharacter,SKILL_TYPE_ACTIVE_POST_BATTLE,gSkillTable);

    struct gpSkillStruct *gAttackerSkillsPreBattle = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPreBattleAtk);
    struct gpSkillStruct *gAttackerSkillsActivePhase = malloc(sizeof(struct gpSkillStruct)*uSkillAmountActiveAtk);
    struct gpSkillStruct *gAttackerSkillsPostPhase  = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPostActiveAtk);
    struct gpSkillStruct *gAttackerSkillsPostBattle  = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPostBattleAtk);

    struct gpSkillStruct *gDefenderSkillsPreBattle  = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPreBattleDef);
    struct gpSkillStruct *gDefenderSkillsActivePhase = malloc(sizeof(struct gpSkillStruct)*uSkillAmountActiveDef);
    struct gpSkillStruct *gDefenderSkillsPostPhase  = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPostActiveDef);
    struct gpSkillStruct *gDefenderSkillsPostBattle  = malloc(sizeof(struct gpSkillStruct)*uSkillAmountPostBattleDef);

    *gAttackerSkillsPreBattle = gReturnSkillStructsDependantOnPhase(gAttackerCharacter,SKILL_TYPE_ACTIVE_PRE_BATTLE,uSkillAmountPreBattleAtk,gSkillTable);
    *gAttackerSkillsActivePhase = gReturnSkillStructsDependantOnPhase(gAttackerCharacter,SKILL_TYPE_ACTIVE_PHASE,uSkillAmountActiveAtk,gSkillTable);
    *gAttackerSkillsPostPhase = gReturnSkillStructsDependantOnPhase(gAttackerCharacter,SKILL_TYPE_ACTIVE_POST_PHASE,uSkillAmountPostActiveAtk,gSkillTable);
    *gAttackerSkillsPostBattle = gReturnSkillStructsDependantOnPhase(gAttackerCharacter,SKILL_TYPE_ACTIVE_POST_BATTLE,uSkillAmountPostBattleAtk,gSkillTable);
    
    *gDefenderSkillsPreBattle = gReturnSkillStructsDependantOnPhase(gDefenderCharacter,SKILL_TYPE_ACTIVE_PRE_BATTLE,uSkillAmountPreBattleDef,gSkillTable);
    *gDefenderSkillsActivePhase = gReturnSkillStructsDependantOnPhase(gDefenderCharacter,SKILL_TYPE_ACTIVE_PHASE,uSkillAmountActiveDef,gSkillTable);
    *gDefenderSkillsPostPhase = gReturnSkillStructsDependantOnPhase(gDefenderCharacter,SKILL_TYPE_ACTIVE_POST_PHASE,uSkillAmountPostActiveDef,gSkillTable);
    *gDefenderSkillsPostBattle = gReturnSkillStructsDependantOnPhase(gDefenderCharacter,SKILL_TYPE_ACTIVE_POST_BATTLE,uSkillAmountPostBattleDef,gSkillTable);
    
    struct gpSkillStruct gSkillToApply;

    u8 uRoll;

    while(gBattle.uBattleState != BATTLE_STATE_ENDING)
    {
        vInitialBattleCalc();
        vInitialAttackAccuracy();

        //TODO!: do something to make skills activation random
        //or not and dump it to skill func ¯\_(ツ)_/¯
        uRoll = uRollD100();
        if(uRoll<50)
        {
            gSkillToApply = gAttackerSkillsPreBattle[uRandom_u8_inclusive(0, uSkillAmountPreBattleAtk)];
        }
        if(uRoll>50)
        {
            gSkillToApply = gDefenderSkillsPreBattle[uRandom_u8_inclusive(0, uSkillAmountPreBattleDef)];
        }        
        if(uRoll==50)
        {
            if(uRandom_u8_inclusive(0,1)==0){
                gSkillToApply = gAttackerSkillsPreBattle[uRandom_u8_inclusive(0, uSkillAmountPreBattleAtk)];;
            }
            else {
                gSkillToApply = gDefenderSkillsPreBattle[uRandom_u8_inclusive(0, uSkillAmountPreBattleDef)];
            }
        }      
        vApplyPreBattleSkills(gSkillToApply.uSkillID,gSkillToApply.uSkillEffectID);
        vFinalBattleCalc();   
        uRoll = uRollD100();
        if(uRoll<50)
        {
            gSkillToApply = gAttackerSkillsActivePhase[uRandom_u8_inclusive(0, uSkillAmountActiveAtk)];
        }
        if(uRoll>50)
        {
            gSkillToApply = gDefenderSkillsActivePhase[uRandom_u8_inclusive(0, uSkillAmountActiveDef)];
        }        
        if(uRoll==50)
        {
            if(uRandom_u8_inclusive(0,1)==0){
                gSkillToApply = gAttackerSkillsActivePhase[uRandom_u8_inclusive(0, uSkillAmountActiveAtk)];;
            }
            else {
                gSkillToApply = gDefenderSkillsActivePhase[uRandom_u8_inclusive(0, uSkillAmountActiveDef)];
            }
        }               
        vApplyOnHitSkills(gSkillToApply.uSkillID,gSkillToApply.uSkillEffectID);
        vDoHit(); // -> calls vApplyMidBattleSkills and vCalcHit
        uRoll = uRollD100();
        if(uRoll<50)
        {
            gSkillToApply = gAttackerSkillsPostPhase[uRandom_u8_inclusive(0, uSkillAmountPostActiveAtk)];
        }
        if(uRoll>50)
        {
            gSkillToApply = gDefenderSkillsPostPhase[uRandom_u8_inclusive(0, uSkillAmountPostActiveDef)];
        }        
        if(uRoll==50)
        {
            if(uRandom_u8_inclusive(0,1)==0){
                gSkillToApply = gAttackerSkillsPostPhase[uRandom_u8_inclusive(0, uSkillAmountPostActiveAtk)];;
            }
            else {
                gSkillToApply = gDefenderSkillsPostPhase[uRandom_u8_inclusive(0, uSkillAmountPostActiveDef)];
            }
        }       
        vApplyPostHitSkills(gSkillToApply.uSkillID,gSkillToApply.uSkillEffectID);
        uRoll = uRollD100();  
        //vChangeWeaponDurability();
        vMoveBattleState();    
    }
    uRoll = uRollD100();
    if(uRoll<50)
    {
        gSkillToApply = gAttackerSkillsPostBattle[uRandom_u8_inclusive(0, uSkillAmountPostBattleAtk)];
    }
    if(uRoll>50)
    {
        gSkillToApply = gDefenderSkillsPostBattle[uRandom_u8_inclusive(0, uSkillAmountPostBattleDef)];
    }        
    if(uRoll==50)
    {
        if(uRandom_u8_inclusive(0,1)==0){
            gSkillToApply = gAttackerSkillsPostBattle[uRandom_u8_inclusive(0, uSkillAmountPostBattleAtk)];;
        }
        else {
            gSkillToApply = gDefenderSkillsPostBattle[uRandom_u8_inclusive(0, uSkillAmountPostBattleDef)];
        }
    }
    free(gAttackerSkillsPreBattle);
    free(gDefenderSkillsPreBattle);      
    free(gAttackerSkillsActivePhase);
    free(gDefenderSkillsActivePhase);     
    free(gAttackerSkillsPostPhase);
    free(gDefenderSkillsPostPhase);      
    free(gAttackerSkillsPostBattle);
    free(gDefenderSkillsPostBattle);
    vApplyPostBattleSkills(gSkillToApply.uSkillID,gSkillToApply.uSkillEffectID);

    return;
};

//returns struct with same values but not the same struct, not really useful most of times
struct gpBattleCharacter USE_FASTCALL GetCurrentActiveBattleCharacter() {
    if(bIsNumberEven(gBattle.uBattleState) != true) {
        return gAttackerCharacter;
    }
    else {
        return gDefenderCharacter;
    };
};

//returns true if attacker, false if defender
bool bGetCurrentBattleCharacter() {
    if(bIsNumberEven(gBattle.uBattleState) == true) //odd phases are attacker, even are defender
    {
        return true; //person initializing attack is current turn atacker
    }
    else{
        return false;
    };
} 

//returns value of character stat
s8 USE_FASTCALL sGetCharacterEvasionStat(struct gpItemStruct gAttackerWeapon, struct gpBattleCharacter gTargetCharacter) {
    if(gAttackerWeapon.uItemType == 2 || gAttackerWeapon.uItemType == 3 || gAttackerWeapon.uItemType == 16) //swords, axes, staves - SPD
    {
        return gTargetCharacter.gCharacter->sCurrentSpd;
    }
    else { //everything else AGI
        return gTargetCharacter.gCharacter->sCurrentAgi;
    };
};
