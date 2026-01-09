/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "battle.h"

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

//!TODO: i need to finalize idea of *how* the fuck to handle skills effects....
//!TODO: Idea, while loop? broken from via goto?
void vApplyMidBattleSkills() {
    


    return;
}

//character attacks
void vDoHit() {
    vApplyMidBattleSkills();

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

//!TODO: Add ability handling if you attacked using one
void USE_FASTCALL HOT_FUNC vBattleLoop(struct gpCurrentCharacter *gAttacker, struct gpCurrentCharacter *gDefender) {
    vCreateBattleStructs(gAttacker, gDefender);

    while(gBattle.uBattleState != BATTLE_STATE_ENDING)
    {
        vInitialBattleCalc();
        vInitialAttackAccuracy();
        //vApplyPreBattleSkills();
        vFinalBattleCalc();    
        vDoHit(); // -> calls vApplyMidBattleSkills and vCalcHit
        //vApplyPostHitSkills();
        //vChangeWeaponDurability();
        vMoveBattleState();    
    }

    //vApplyPostBattleSkills();

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
