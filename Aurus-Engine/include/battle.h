/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
#include "character.h"
#include "item.h"
#include "chapter.h"
#include "types.h"
#include "rng.h"

#define BATTLE_TURN_ATTACKER true


enum eAttackHitType {
    ATTACK_HIT_MISS,
    ATTACK_HIT_NORMAL,
    ATTACK_HIT_CRITICAL
};

enum eBattleState {
    BATTLE_STATE_INITIALISED,
    BATTLE_STATE_ATTACKER_ATTACK_1,
    BATTLE_STATE_DEFENDER_ATTACK_1,
    BATTLE_STATE_ATTACKER_ATTACK_2,
    BATTLE_STATE_DEFENDER_ATTACK_2,
    BATTLE_STATE_ATTACKER_ATTACK_3,
    BATTLE_STATE_DEFENDER_ATTACK_3,
    BATTLE_STATE_SPECIAL,
    BATTLE_STATE_ENDING
};

struct gpBattleCharacter {
    struct gpCurrentCharacter *gCharacter;

    struct gpItemStruct gCharacterWeapon;
    u8  uCurrentHP;
    u8  uMaxHP;
    s8  sAttackDamage;
    s8  sBaseHitRate;   //wpn chance - enemy spd/end    
};

extern struct gpBattleCharacter gAttackerCharacter;
extern struct gpBattleCharacter gDefenderCharacter;

struct gpBattleState {
    u8 uBattleState;
    u32 uBattleBackground;
    u32 uBattleForeground;
    u16 uBattleWheather;
};

extern struct gpBattleState gBattle;

s8 USE_FASTCALL sGetCharacterEvasionStat(struct gpItemStruct gAttackerWeapon, struct gpBattleCharacter gTargetCharacter);
struct gpBattleCharacter USE_FASTCALL GetCurrentActiveBattleCharacter();

bool bGetCurrentBattleCharacter();
void vApplyPreBattleSkills();
void vApplyPostHitSkills();
void vApplyMidBattleSkills();
void USE_FASTCALL HOT_FUNC vBattleLoop(struct gpCurrentCharacter *gAttacker, struct gpCurrentCharacter *gDefender);
void USE_SSE_PARAM HOT_FUNC vInitialBattleCalc();
void USE_FASTCALL vInitialAttackAccuracy();
void USE_SSE_PARAM vFinalBattleCalc();
void vCalcHit(u8 uDidAttackHit);
