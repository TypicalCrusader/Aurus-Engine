#include "../include/battle.h"
#include "../include/inventory.h"
#include "../include/misc.h"
#include "../include/skills.h"
#include <stdint.h>

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

void MoveBattleState(struct BattleUnit Unit)
{

    if(Battle.BattleStatus != BATTLE_STATUS_STARTED ){
        Battle.BattleStatus += 1;
        if(Battle.BattleStatus == BATTLE_STATUS_END) {
            return;
        }
    }
    else {
        Battle.BattleStatus = BATTLE_STATUS_STARTED;
        Battle.BattleRange = CharInventory[Unit.EquippedWeapon].AttackRange;
    }

    if ( (Battle.BattleStatus = BATTLE_STATUS_STARTED) & (CharInventory[Unit.EquippedWeapon].ItemType != ITEM_TYPE_WEAPON)) //this should never happen, you cant attack without a weapon
    {
        assert(CharInventory[Unit.EquippedWeapon].ItemType != ITEM_TYPE_WEAPON);
        return;
    }

    Battle.BattleAttackType = CharInventory[Unit.EquippedWeapon].AttackType;

    return;
};

void Initiate_Battle() {
    GenerateBattleStruct(SelectedUnit, Actor);
    GenerateBattleStruct(EnemyUnit, Recipient);
    MoveBattleState(Actor);

    //TODO: Add here OpenGL shit here

    /*
    - initialise battle gui
    - show battle gui
    - show battle spites
    - show battle bgs
    
    =========================================+
    = Hp |||||||||||| Hit |||  =             =
    = Atk ||| Def ||| Crt |||  =             =
    =========================================+
    */

    return;
};

int Initiate_PreBattleSkills(struct BattleUnit Unit) {
    u32 i;

    for(i=0;i <= (sizeof(Unit.Unitinfo.Unit.CharSkills) / sizeof(Unit.Unitinfo.Unit.CharSkills[0]));i++)
    {
        if (Skills[Unit.Unitinfo.Unit.CharSkills[i]].SkillActivation == SKILL_ACTIVATION_PRE_BATTLE)
        {
            u8 skill = Skills[Unit.Unitinfo.Unit.CharSkills[i]].SkillID;
            return skill;
        }
    }

    u8 skill = 0;
    return skill;
};

void CalcAttack(struct BattleUnit Unit)
{
    Unit.UnitDamage += CharInventory[Unit.EquippedWeapon].Attack;

    return;
}

void SMTLikeRes(struct BattleUnit Unit, struct BattleUnit AttackTarget)
{
    if (Race[Unit.Unitinfo.Unit.RaceID].RaceSMTShouldNullAtk != true) {
        return;// it means that race doesnt have the smt res array so dont waste time going through loop here
    }

    u32 i;
    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.SpecialWeaponNullDmg) / sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.SpecialWeaponNullDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.SpecialWeaponNullDmg[i] == (u16) CharInventory[Unit.EquippedWeapon].ItemID)
        {
            //ifs based here on item effect and type, most likely only omega and Tyfrang of Revolution will go here
            return;
        }
    
    }    
    
    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ResAlignmentDmg) / sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ResAlignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ResAlignmentDmg[i] == (u16) CharInventory[Unit.EquippedWeapon].AffinityRes)
        {
            Unit.UnitDamage *= 0.25;
            return;
        }
    
    }

    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.NulllignmentDmg) / sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.NulllignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.NulllignmentDmg[i] == (u16) CharInventory[Unit.EquippedWeapon].AffinityNul)
        {
            Unit.UnitDamage *= 0;
            return;
        }
    
    }

    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ReverseAlignmentDmg) / sizeof(Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ReverseAlignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo.Unit.RaceID].SMTRes.ReverseAlignmentDmg[i] == (u16) CharInventory[Unit.EquippedWeapon].AffinityAbs)
        {
            Unit.UnitDamage *= -1;
            return;
        }
    
    }

    return;
}

void CalcHit(struct BattleUnit Unit, struct BattleUnit AttackTarget)
{
    
    //over / underflow checker
    if ((Unit.UnitDamage >= 100) || ( Unit.UnitDamage <= -100))
    {
        if (Unit.UnitDamage >= 100)
        {
            Unit.UnitDamage = 100;
        }
        if (Unit.UnitDamage <= -100)
        {
            Unit.UnitDamage = -100;
        }        
    }

    //hit
    if(DiceRollOnehundred() <= (CharInventory[Unit.EquippedWeapon].Accuracy + Unit.CurrentDex - CharInventory[Unit.EquippedWeapon].Weight))
    {
        // BATTLE SKILLS GO HERE :)

        //check for crit
        if(DiceRollOnehundred() <= CharInventory[Unit.EquippedWeapon].CritRate)
        {
            Unit.UnitDamage *= 2;
            if (Unit.UnitDamage >= 100)
            {
                Unit.UnitDamage = 100;
            }
            if (Unit.UnitDamage <= -100)
            {
                Unit.UnitDamage = -100;
            }

            AttackTarget.CurrentHp -= Unit.UnitDamage;
            //OpenGl here
            return;
        }

        AttackTarget.CurrentHp -= Unit.UnitDamage;
        //OpenGl here

        return;
    }
    else { //miss
        //openGL here
        return;
    }

    return;
};

void AttackFunc() {

    //skills
    //calc attack v
    //check and apply res v
    //check if overflows v
    //actually attack - branch if skill attack or crit - mostly

    if((Battle.BattleStatus == BATTLE_STATUS_STARTED) || (Battle.BattleStatus == BATTLE_STATUS_FOLLOWUP) || (Battle.BattleStatus == BATTLE_STATUS_THIRD_ATTACK) )
    {
        CalcAttack(Actor);
        SMTLikeRes(Actor, Recipient);
        CalcHit(Actor, Recipient);
    }
    else
    {
        CalcAttack(Recipient);
        SMTLikeRes(Recipient, Actor);
        CalcHit(Recipient, Actor);
    }
    
    return;
};

int BattleLoop(){
    Initiate_Battle();
    u8 PreBattleSkillActor = Initiate_PreBattleSkills(Actor);
    u8 PreBattleSkillRecipient = Initiate_PreBattleSkills(Recipient);

    while (Battle.BattleStatus != BATTLE_STATUS_END){
        AttackFunc();
        MoveBattleState(Recipient);
    }

    //post battle skills go here
    return 0;
};
