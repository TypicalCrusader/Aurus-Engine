#include "../include/battle.h"

struct RaceStruct Race[RACESAMOUNT];

s8 IncreaseStat(s8 stat, s8 statgrowth){
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

u8 AddLevel (BattleUnit unit)
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

BattleUnit (GenerateBattleStruct ()) {

    if(&SelectedUnit == NULL)
    {
        return;
    };

    BattleUnit bunit;
    BattleUnit *bunit = malloc(sizeof(BattleUnit));
    if (&bunit == NULL)
    {
        free(&bunit);
        fprintf(stderr, "Fatal Error: could not allocate memory for Battle Unit Struct in GenerateBattleStruct");
        return;
    }
    bunit.Unitinfo = SelectedUnit;
    //TODO in future check if its valid item
    bunit.EquippedWeapon = SelectedUnit.Inventory[0x0]; //first index of inventory is always a weapon, if its not a weapon then it means its either a hand or item
    bunit.MaxHP = SelectedUnit.MaxHP;
    bunit.CurrentHp = SelectedUnit.CurrentHp;
    bunit.CurrentAtk = SelectedUnit.CurrentAtk;
    bunit.CurrentMag = SelectedUnit.CurrentMag;
    bunit.CurrentDef = SelectedUnit.CurrentDef;
    bunit.CurrentMagDef = SelectedUnit.CurrentMagDef;
    bunit.CurrentSpd  = SelectedUnit.CurrentSpd;
    bunit.CurrentLck = SelectedUnit.CurrentLck;
    bunit.CurrentDex = SelectedUnit.CurrentDex;

    if(SelectedUnit.Class->ClassType != TYPE_MAGICAL)
    {
        bunit.UnitDamage = SelectedUnit.CurrentAtk; //base
        return bunit;
    }  
    bunit.UnitDamage = SelectedUnit.CurrentMag; //base           

    return bunit;
};

void MoveBattleState( BattleUnit Unit, BattleUnit AttackTarget)
{

    //15, 20, 25 spd +1 round

    if(Battle.BattleStatus >= BATTLE_STATUS_STARTED ){
        Battle.BattleStatus += 1;

        if(Battle.BattleStatus >= BATTLE_STATUS_RECIPIENT )
        {
            if(Unit.CurrentSpd <= 15)
            {
                Battle.BattleStatus = BATTLE_STATUS_END;
            }
            if((AttackTarget.CurrentSpd <= 20) & (Battle.BattleStatus == BATTLE_STATUS_RECIPIENT_FOLLOWUP)) //it means that no that no recipient followup attack should happen
            {
                Battle.BattleStatus = BATTLE_STATUS_END;                
            }
            if((Unit.CurrentSpd <= 25) & (Battle.BattleStatus >= BATTLE_STATUS_THIRD_ATTACK)) //it means that no that actor's third attack should happen
            {
                Battle.BattleStatus = BATTLE_STATUS_END;                
            }            
            return;
        }


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

u8 Initiate_PreBattleSkills( BattleUnit Unit) {
    u32 i;

    struct SkillStruct Skills[MAX_SKILLS_AMOUNT];


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

void CalcAttack( BattleUnit Unit)
{
    Unit.UnitDamage += CharInventory[Unit.EquippedWeapon].Attack;

    return;
}

void ApplyPreBattleSkills(u8 skill,  BattleUnit Unit)
{

    /*
         List of pre battle skills and their effect go here
    
    */

    return;
}

void SMTLikeRes( BattleUnit Unit,  BattleUnit AttackTarget)
{

    //.. its not necessarly the fastest way to do this mechanic but for sure its one of the easiest
    if (Race[Unit.Unitinfo.Unit.RaceID].RaceSMTShouldNullAtk != true) {
        return;// it means that race doesnt have the smt res array so dont waste time going through loops here
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

void CalcHit( BattleUnit Unit, BattleUnit AttackTarget)
{
    
    //over / underflow checker
    if (Unit.UnitDamage >= 100)
    {
        Unit.UnitDamage = 100;
    }
    if (Unit.UnitDamage <= -100)
    {
        Unit.UnitDamage = -100;
    }        

    /*
        Skills replacing attacks will go here
    */

    if(&CharInventory == NULL)
    {
        free(&CharInventory);
        fprintf(stderr, "Fatal Error: unalocated memory for CharInventory in GenerateBattleStruct");
        return;
    }

    //hit
    if((DiceRollOnehundred() - (Unit.CurrentLck * 0,1 )) <= (CharInventory[Unit.EquippedWeapon].Accuracy + Unit.CurrentDex - CharInventory[Unit.EquippedWeapon].Weight))
    {

        //check for crit
        if((DiceRollOnehundred() - (Unit.CurrentLck * 0,1 ) ) <= CharInventory[Unit.EquippedWeapon].CritRate)
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
        }

        if(CharInventory[Unit.EquippedWeapon].UseMAG != true)
        {
            AttackTarget.CurrentHp -= (Unit.UnitDamage - AttackTarget.CurrentDef);
            return;
        }

        AttackTarget.CurrentHp -= (Unit.UnitDamage - AttackTarget.CurrentMagDef);
        //OpenGl here

        return;
    }
    else { //miss
        //openGL here
        return;
    }

    return;
};

void AttackFunc(BattleUnit Actor, BattleUnit Recipient) {

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

//inline void Initiate_Battle(SelectedUnit Actor,SelectedUnit Recipient) {


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

//    return;
//};

void BattleLoop(struct SelectedUnitData Actor, struct SelectedUnitData Recipient){
    
    if(&Actor == NULL || &Recipient == NULL)
    {
        return;
    }
    
    BattleUnit BActor = GenerateBattleStruct(Actor); //on player turn this is the player characters, on enemy its enemy characters
    BattleUnit BRecipient = GenerateBattleStruct(Recipient);
    MoveBattleState(BActor, BRecipient);  
    ApplyPreBattleSkills(Initiate_PreBattleSkills(BActor), BActor);
    ApplyPreBattleSkills(Initiate_PreBattleSkills(BRecipient), BRecipient);

    while (Battle.BattleStatus != BATTLE_STATUS_END){
        AttackFunc(BActor, BRecipient);
        MoveBattleState(BActor, BRecipient);
    }

    //post battle skills go here
    return;
};
