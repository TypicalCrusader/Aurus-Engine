#include "../include/battle.h"
#include "../include/inventory.h"
#include "../include/misc.h"
#include <stdint.h>
#include <stdlib.h>

int IncreaseStat(s8 stat, s8 statgrowth){
    s8 maxstat = stat * 100; 
    s8 currentstat = maxstat / statgrowth;
    currentstat = maxstat / statgrowth;
    maxstat = currentstat - statgrowth;

    if (stat != (maxstat + stat ))
    {
        if(statgrowth >= 100){
            statgrowth = 100;
        }
        if(statgrowth <= -100){
            statgrowth = -100;
        }

        if(statgrowth >= 0) {
            //check if growth actually works
            if (DiceRollOnehundred() <= statgrowth) {

                //check if quallifies for +2
                if (DiceRollOnehundred() == 100) {
                    stat += 1;
                }

                stat += 1;
            }
            else {
                stat = 0;
            }
        }
        else {
            //check if growth actually works
            if ((DiceRollOnehundred() *-1) >= statgrowth) {

                //check if quallifies for -2
                if (DiceRollOnehundred() == 100) {
                    stat -= 1;
                }

                stat -= 1;
            }     
            else {
                stat = 0;
            }              
        }

        return stat;
    }

    stat = 0;
    return stat;
};

int AddLevel (struct BattleUnit unit)
{
    u8 level = unit.Unitinfo.level;

    unit.Unitinfo.CurrentAtk += IncreaseStat(unit.Unitinfo.CurrentAtk, unit.Unitinfo.Unit.AtkCharGrowth);
    unit.Unitinfo.CurrentMag += IncreaseStat(unit.Unitinfo.CurrentMag, unit.Unitinfo.Unit.MagCharGrowth);
    unit.Unitinfo.CurrentHp += IncreaseStat(unit.Unitinfo.CurrentHp, unit.Unitinfo.Unit.HpCharGrowth);
    unit.Unitinfo.CurrentDef += IncreaseStat(unit.Unitinfo.CurrentDef, unit.Unitinfo.Unit.DefCharGrowth);
    unit.Unitinfo.CurrentMagDef += IncreaseStat(unit.Unitinfo.CurrentMagDef, unit.Unitinfo.Unit.MagDefCharGrowth);
    unit.Unitinfo.CurrentSpd += IncreaseStat(unit.Unitinfo.CurrentSpd, unit.Unitinfo.Unit.SpdCharGrowth);
    unit.Unitinfo.CurrentLck += IncreaseStat(unit.Unitinfo.CurrentLck, unit.Unitinfo.Unit.LckCharGrowth);
    unit.Unitinfo.CurrentDex += IncreaseStat(unit.Unitinfo.CurrentDex, unit.Unitinfo.Unit.DexCharGrowth);

    level += 1;

    return level;
};

int GenerateBattleStruct (struct SelectedUnit unit, struct BattleUnit bunit) {
    bunit.Unitinfo = unit;
    bunit.EquippedWeapon = unit.Inventory[0x0]; //first index of inventory is always a weapon, if its not a weapon then it means its either a hand or item
    bunit.MaxHP = unit.MaxHP;
    bunit.CurrentHp = unit.CurrentHp;
    bunit.CurrentAtk = unit.CurrentAtk;
    bunit.CurrentMag = unit.CurrentMag;
    bunit.CurrentDef = unit.CurrentDef;
    bunit.CurrentMagDef = unit.CurrentMagDef;
    bunit.CurrentSpd  = unit.CurrentSpd;
    bunit.CurrentLck = unit.CurrentLck;
    bunit.CurrentDex = unit.CurrentDex;

    if(unit.Class.ClassType != TYPE_MAGICAL)
    {
        bunit.UnitDamage = unit.CurrentAtk; //base
    }  
    else
    {
        bunit.UnitDamage = unit.CurrentMag; //base           
    }

    return 0;
};

void MoveBattleState()
{
    if(Battle.BattleStatus != BATTLE_STATUS_STARTED ){
        Battle.BattleStatus += 1;
        if(Battle.BattleStatus == BATTLE_STATUS_END) {
            return;
        }
    }
    else {
        struct InventoryData CharInventory[UINT16_MAX];

        if ( CharInventory[Actor.EquippedWeapon].ItemType != ITEM_TYPE_WEAPON) 
        {

        }



        Battle.BattleAttackType = Actor.EquippedWeapon
        Battle.BattleRange
        Battle.BattleStatus 
    }

    return;
};

void Initiate_Battle() {
    GenerateBattleStruct(SelectedUnit, Actor);
    GenerateBattleStruct(EnemyUnit, Recipient);
    Battle.BattleStatus = BATTLE_STATUS_STARTED;


    return;
};

int BattleLoop(){
    Initiate_Battle();
};
