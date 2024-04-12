#pragma once
#ifndef _MYHEADER_H_
#define _MYHEADER_H_
#endif
#include "map.h"

typedef struct 
{
    SelectedUnit Unitinfo;
    u16 EquippedWeapon;
    s8 MaxHP;
    s8 CurrentHp;
    s8 CurrentAtk;
    s8 CurrentMag;
    s8 CurrentDef;
    s8 CurrentMagDef;
    s8 CurrentSpd;
    s8 CurrentLck;
    s8 CurrentDex;     
    s16 UnitDamage;    
}BattleUnit;

BattleUnit Actor;
BattleUnit Recipient;

typedef struct
{
    u8 BattleStatus;
    u8 BattleAttackType;
    u8 BattleRange;
}BattleState;

BattleState Battle;

enum BattleStatus
{
    BATTLE_STATUS_STARTED,
    BATTLE_STATUS_RECIPIENT,
    BATTLE_STATUS_FOLLOWUP,
    BATTLE_STATUS_RECIPIENT_FOLLOWUP,
    BATTLE_STATUS_THIRD_ATTACK,
    BATTLE_STATUS_END
};

enum BattleAttackType
{
    BATTLE_ATTACK_TYPE_NONE,
    BATTLE_ATTACK_TYPE_NORMAL,
    BATTLE_ATTACK_TYPE_CRITICAL,
    BATTLE_ATTACK_TYPE_MISS,
    BATTLE_ATTACK_TYPE_NORMAL_REVERSE,
    BATTLE_ATTACK_TYPE_CRITICAL_REVSERSE,
    BATTLE_ATTACK_TYPE_HEAL
};

enum BattleRange
{
    BATTLE_RANGE_0_ITEM,
    BATTLE_RANGE_1_MELEE,
    BATTLE_RANGE_2_MELEE,
    BATTLE_RANGE_3_MELEE_SPECIAL, //Tyrfang of Revolution
    BATTLE_RANGE_2_THROWABLE,
    BATTLE_RANGE_3_THROWABLE,
    BATTLE_RANGE_1_MAGIC,
    BATTLE_RANGE_2_MAGIC,
    BATTLE_RANGE_3_MAGIC
};

int GenerateBattleStruct ( SelectedUnit , BattleUnit );
int Initiate_PreBattleSkills( BattleUnit );
int BattleLoop();
void AttackFunc();
void Initiate_Battle();
void CalcAttack( BattleUnit );
void MoveBattleState( BattleUnit , BattleUnit );
void ApplyPreBattleSkills(u8 ,  BattleUnit );
void SMTLikeRes( BattleUnit ,  BattleUnit );
void CalcHit( BattleUnit , BattleUnit );
