#pragma once
#include "misc.h"
#include "inventory.h"
#include "skills.h"
#include "char.h"
#include "map.h"
#include <stdint.h>
#include <stdio.h>

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

/*
    `int AddLevel` - Adds level to x character
    \param `unit` Battle Unit which will get increased level
    \returns increased `level`
    \since This Function is available since version 0.1 of Aurus Engine
*/
u8 AddLevel (BattleUnit unit); 
/*
    `int IncreaseStat` - Adds level to x character
    \param `stat` Current Statistics number (eg. if you have 4 ATK the value will be 4)
    \param `statgrowth` Grow rate of selected statistics represented in form of intiger going from 0 to 100
    \returns increased `stat`
    \since This Function is available since version 0.1 of Aurus Engine
*/
s8 IncreaseStat(s8 stat, s8 statgrowth); //this can either be used with BUnit or CurrUnit
BattleUnit (GenerateBattleStruct ( SelectedUnit unit));
u8 Initiate_PreBattleSkills( BattleUnit );
void BattleLoop(SelectedUnit Actor,SelectedUnit Recipient);
void AttackFunc();
//void Initiate_Battle(BattleUnit Actor, SelectedUnit Recipient);
void CalcAttack( BattleUnit );
void MoveBattleState( BattleUnit , BattleUnit );
void ApplyPreBattleSkills(u8 skill,  BattleUnit Unit));
void SMTLikeRes( BattleUnit ,  BattleUnit );
void CalcHit( BattleUnit , BattleUnit );


