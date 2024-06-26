#include "../include/battle.h"

//TODO: CREATE SIMULATE BATTLE FUNC


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
            if (DiceRollOnehundred() < statgrowth) {

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
            if ((DiceRollOnehundred() *-1) > statgrowth) {

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
    unit.Unitinfo->CurrAtk += IncreaseStat(unit.Unitinfo->CurrAtk, unit.Unitinfo->CharData->AtkCharGrowth);
    unit.Unitinfo->CurrMag += IncreaseStat(unit.Unitinfo->CurrMag, unit.Unitinfo->CharData->MagCharGrowth);
    unit.Unitinfo->CurrHp += IncreaseStat(unit.Unitinfo->CurrHp, unit.Unitinfo->CharData->HpCharGrowth);
    unit.Unitinfo->CurrDef += IncreaseStat(unit.Unitinfo->CurrDef, unit.Unitinfo->CharData->DefCharGrowth);
    unit.Unitinfo->CurrMagDef += IncreaseStat(unit.Unitinfo->CurrMagDef, unit.Unitinfo->CharData->MagDefCharGrowth);
    unit.Unitinfo->CurrSpd += IncreaseStat(unit.Unitinfo->CurrSpd, unit.Unitinfo->CharData->SpdCharGrowth);
    unit.Unitinfo->CurrLck += IncreaseStat(unit.Unitinfo->CurrLck, unit.Unitinfo->CharData->LckCharGrowth);
    unit.Unitinfo->CurrDex += IncreaseStat(unit.Unitinfo->CurrDex, unit.Unitinfo->CharData->DexCharGrowth);

    return unit.Unitinfo->CurrLvl += 1;
};

BattleUnit* (GenerateBattleStructPlayer ()) {

    struct SelectedUnitData SelectedUnit;
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];    

    if(&SelectedUnit == NULL)
    {
        return NULL;
    };

    BattleUnit *bunit;
    bunit = malloc(sizeof(BattleUnit));
    if (&bunit == NULL)
    {
        free(&bunit);
        fprintf(stderr, "Fatal Error: could not allocate memory for Battle Unit Struct in GenerateBattleStructPlayer");
        return NULL;
    }
    bunit->Unitinfo = SelectedUnit.Unit;
    //TODO in future check if its valid item
    bunit->EquippedWeapon = SelectedUnit.Inventory[0].ItemID;
    bunit->MaxHP = SelectedUnit.MaxHP;
    bunit->CurrentHp = SelectedUnit.CurrentHp;
    bunit->CurrentAtk = SelectedUnit.CurrentAtk;
    bunit->CurrentMag = SelectedUnit.CurrentMag;
    bunit->CurrentDef = SelectedUnit.CurrentDef;
    bunit->CurrentMagDef = SelectedUnit.CurrentMagDef;
    bunit->CurrentSpd  = SelectedUnit.CurrentSpd;
    bunit->CurrentLck = SelectedUnit.CurrentLck;
    bunit->CurrentDex = SelectedUnit.CurrentDex;

    if(SelectedUnit.Class->ClassType != TYPE_MAGICAL)
    {
        bunit->UnitDamage = SelectedUnit.CurrentAtk; //base
        return bunit;
    }  
    bunit->UnitDamage = SelectedUnit.CurrentMag; //base           

    return bunit;
};

BattleUnit* (GenerateBattleStructEnemy (u16 DevIndex)) {
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL)
    {
        return NULL;
    };
    if(DevIndex > MAX_DEPLOYED_ALL_UNITS)
    {
        return NULL;
    };

    BattleUnit *bunit;
    bunit = malloc(sizeof(BattleUnit));
    if (bunit == NULL)
    {
        free(bunit);
        fprintf(stderr, "Fatal Error: could not allocate memory for Battle Unit Struct in GenerateBattleStructEnemy");
        return NULL;
    }
    bunit->Unitinfo = &CurrentCharacter[DevIndex];
    //TODO in future check if its valid item
    bunit->EquippedWeapon = CurrentCharacter[DevIndex].Inventory[0]->ItemID; //first index of inventory is always a weapon, if its not a weapon then it means its either a hand or item
    bunit->MaxHP = CurrentCharacter[DevIndex].MaxHP;
    bunit->CurrentHp = CurrentCharacter[DevIndex].CurrHp;
    bunit->CurrentAtk = CurrentCharacter[DevIndex].CurrAtk;
    bunit->CurrentMag = CurrentCharacter[DevIndex].CurrMag;
    bunit->CurrentDef = CurrentCharacter[DevIndex].CurrDef;
    bunit->CurrentMagDef = CurrentCharacter[DevIndex].CurrMagDef;
    bunit->CurrentSpd  = CurrentCharacter[DevIndex].CurrSpd;
    bunit->CurrentLck = CurrentCharacter[DevIndex].CurrLck;
    bunit->CurrentDex = CurrentCharacter[DevIndex].CurrDex;

    if(CurrentCharacter[DevIndex].ClassData->ClassType != TYPE_MAGICAL)
    {
        bunit->UnitDamage = CurrentCharacter[DevIndex].CurrAtk; //base
        return bunit;
    }  
    bunit->UnitDamage = CurrentCharacter[DevIndex].CurrMag; //base           

    return bunit;
};

void MoveBattleState( BattleUnit Unit, BattleUnit AttackTarget)
{

    //15, 20, 25 spd +1 round
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];
    BattleState Battle;

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
        Battle.BattleRange = Unit.Unitinfo->Inventory[0]->AttackRange;
    }

    if ( (Battle.BattleStatus = BATTLE_STATUS_STARTED) & (Unit.Unitinfo->Inventory[0]->ItemType != ITEM_TYPE_WEAPON)) //this should never happen, you cant attack without a weapon
    {
        //TODO fprintf
        return;
    }

    Battle.BattleAttackType = Unit.Unitinfo->Inventory[0]->AttackType;

    return;
};

f32 CalcWeaponEff( BattleUnit Unit, BattleUnit AttackTarget)
{
    struct weaponTypeStruct weaponType[7];

    if(&weaponType == NULL)
    {
        return 100;
    }

    struct WeaponSubTypeStruct WeaponSubType[33];

    if(&WeaponSubType == NULL)
    {
        return 100;
    }    

    if(Unit.Unitinfo->Inventory[0]->WeaponType == WEAPON_TYPE_NONE)
    {
        return 100;
    }
    if(Unit.Unitinfo->Inventory[0]->WeaponSubType == WEAPON_SUB_TYPE_NONE)
    {
        return 100;
    }

    if(Unit.Unitinfo->Inventory[0]->WeaponType != AttackTarget.Unitinfo->Inventory[0]->WeaponType) //if its different then do comparison of types
    {
        if(Unit.Unitinfo->Inventory[0]->WeaponType == WEAPON_TYPE_MAGIC_ELEMENTAL && AttackTarget.Unitinfo->Inventory[0]->WeaponType != WEAPON_TYPE_MAGIC_DAWN_DUSK)
        {
            return BATTLE_TYPE_EFFECTIVENESS;
        }                 
        if(Unit.Unitinfo->Inventory[0]->WeaponType == WEAPON_TYPE_MAGIC_DRAGON_SYGIL)
        {
            return BATTLE_TYPE_EFFECTIVENESS;          
        }     
        if(weaponType[Unit.Unitinfo->Inventory[0]->WeaponType].WeaponTypeEff == AttackTarget.Unitinfo->Inventory[0]->WeaponType)
        {
            return BATTLE_TYPE_EFFECTIVENESS;           
        }
        if(WeaponSubType[Unit.Unitinfo->Inventory[0]->WeaponSubType].WeaponEffAgainstType == AttackTarget.Unitinfo->Inventory[0]->WeaponType)
        {
            return BATTLE_TYPE_EFFECTIVENESS;           
        }        
        if(AttackTarget.Unitinfo->Inventory[0]->WeaponType == WEAPON_TYPE_MAGIC_ELEMENTAL && Unit.Unitinfo->Inventory[0]->WeaponType != WEAPON_TYPE_MAGIC_DAWN_DUSK)
        {
            return BATTLE_TYPE_RESISTANCE;
        }                  
        if(AttackTarget.Unitinfo->Inventory[0]->WeaponType == WEAPON_TYPE_MAGIC_DRAGON_SYGIL)
        {
            return BATTLE_TYPE_RESISTANCE;          
        }             
        if(weaponType[AttackTarget.Unitinfo->Inventory[0]->WeaponType].WeaponTypeEff == Unit.Unitinfo->Inventory[0]->WeaponType)
        {
            return BATTLE_TYPE_RESISTANCE;           
        }
        if(WeaponSubType[AttackTarget.Unitinfo->Inventory[0]->WeaponSubType].WeaponEffAgainstType == Unit.Unitinfo->Inventory[0]->WeaponType)
        {
            return BATTLE_TYPE_RESISTANCE;           
        }          
    }
    else { 
        if(Unit.Unitinfo->Inventory[0]->WeaponSubType == WEAPON_SUB_TYPE_MAGIC_ANIMA || Unit.Unitinfo->Inventory[0]->WeaponSubType == WEAPON_SUB_TYPE_SYGIL_DECADENT )
        {
            return BATTLE_SUB_TYPE_EFFECTIVENESS;  
        }
        if(WeaponSubType[Unit.Unitinfo->Inventory[0]->WeaponSubType].WeaponSubTypeEff == AttackTarget.Unitinfo->Inventory[0]->WeaponSubType)
        {
            return BATTLE_SUB_TYPE_EFFECTIVENESS;           
        }       
        if(AttackTarget.Unitinfo->Inventory[0]->WeaponSubType == WEAPON_SUB_TYPE_MAGIC_ANIMA || AttackTarget.Unitinfo->Inventory[0]->WeaponSubType == WEAPON_SUB_TYPE_SYGIL_DECADENT )
        {
            return BATTLE_SUB_TYPE_RESISTANCE;  
        }
        if(WeaponSubType[AttackTarget.Unitinfo->Inventory[0]->WeaponSubType].WeaponSubTypeEff == Unit.Unitinfo->Inventory[0]->WeaponSubType)
        {
            return BATTLE_SUB_TYPE_RESISTANCE;           
        }        
    }

    return 100;
}

u8 CalcAttack( BattleUnit Unit, BattleUnit AttackTarget)
{

    //base attack
    u8 Damage = Unit.UnitDamage;
    Damage += Unit.Unitinfo->Inventory[0]->Attack;
    f32 AtkAdd;
    AtkAdd = CalcWeaponEff(Unit, AttackTarget);
    if(AtkAdd != 100)
    {
        u8 DamageAdd;
        DamageAdd *= AtkAdd;
        Damage += DamageAdd;
    }
    f32 SMTRes;
    SMTRes = SMTLikeRes(Unit, AttackTarget);
    if(SMTRes != 100)
    {
       Damage *SMTRes;
    }

    return Damage;
}

void ApplyPreBattleSkills(BattleUnit Unit)
{

    struct SkillStruct Skills[MAX_SKILLS_AMOUNT];

    //sanity checks

    if(&Skills == NULL)
    {
        return;
    }

    u8 i;
    for(i=0;i<=5;i++)
    {
        if(Skills[Unit.Unitinfo->CurrentSkills[i]].FunctionPointer != NULL && Skills[Unit.Unitinfo->CurrentSkills[i]].SkillActivation == SKILL_ACTIVATION_PRE_BATTLE )
        {
            Skills[Unit.Unitinfo->CurrentSkills[i]].FunctionPointer(0);
        }
    }    

    return;
}

f32 SMTLikeRes( BattleUnit Unit,  BattleUnit AttackTarget)
{

    //.. its not necessarly the fastest way to do this mechanic but for sure its one of the easiest
    if (Race[Unit.Unitinfo->CharData->RaceID].RaceSMTShouldNullAtk != true) {
        return 100;// it means that race doesnt have the smt res array so dont waste time going through loops here
    }

    u32 i;
    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.SpecialWeaponNullDmg) / sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.SpecialWeaponNullDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.SpecialWeaponNullDmg[i] == Unit.Unitinfo->Inventory[0]->ItemID)
        {
            //ifs based here on item effect and type, most likely only omega and Tyfrang of Revolution will go here
            return 0;
        }
    
    }    
    
    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ResAlignmentDmg) / sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ResAlignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ResAlignmentDmg[i] == Unit.Unitinfo->Inventory[0]->AffinityRes)
        {
            return 0.25;
        }
    
    }

    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.NulllignmentDmg) / sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.NulllignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.NulllignmentDmg[i] == Unit.Unitinfo->Inventory[0]->AffinityNul)
        {
            return 0;
        }
    
    }

    for(i=0;i <= (sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ReverseAlignmentDmg) / sizeof(Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ReverseAlignmentDmg[0]));i++)    
    {
        if (Race[AttackTarget.Unitinfo->CharData->RaceID].SMTRes.ReverseAlignmentDmg[i] == Unit.Unitinfo->Inventory[0]->AffinityAbs)
        {
            return -1;
        }
    
    }

    return -1;
}

void CalcHit( BattleUnit Unit, BattleUnit AttackTarget)
{
    struct SkillStruct Skills[MAX_SKILLS_AMOUNT]; 

    if(&Skills == NULL)
    {
        return;
    }

    u8 UnitATK;
    UnitATK = CalcAttack(Unit, AttackTarget);
    if(UnitATK == 0) //if 0 then just do 0 atk anim and hit always to skim on few cpu cycles
    {
        return;
    }

    //over / underflow checker
    if (UnitATK >= 100)
    {
        UnitATK = 100;
    }
    if (UnitATK <= -100)
    {
        UnitATK = -100;
    }        

    u8 i;
    for(i=0;i<=5;i++)
    {
        if(Skills[Unit.Unitinfo->CurrentSkills[i]].FunctionPointer != NULL && Skills[Unit.Unitinfo->CurrentSkills[i]].SkillActivation == SKILL_ACTIVATION_BATTLE)
        {
            Skills[Unit.Unitinfo->CurrentSkills[i]].FunctionPointer(0);
        }
    }


    if(&Unit == NULL)
    {
        free(&Unit);
        fprintf(stderr, "Fatal Error: unalocated memory for CharInventory in GenerateBattleStruct");
        return;
    }

    //hit
    if((DiceRollOnehundred() - (Unit.CurrentLck * 0,1 )) <= (Unit.Unitinfo->Inventory[0]->Accuracy + Unit.CurrentDex - Unit.Unitinfo->Inventory[0]->Weight))
    {

        //check for crit
        if((DiceRollOnehundred() - (Unit.CurrentLck * 0,1 ) ) <= Unit.Unitinfo->Inventory[0]->CritRate)
        {
            UnitATK *= 2;
            if (UnitATK >= 100)
            {
                UnitATK = 100;
            }
            if (UnitATK <= -100)
            {
                UnitATK = -100;
            }
        }

        if(Unit.Unitinfo->Inventory[0]->UseMAG != true)
        {
            AttackTarget.CurrentHp -= (UnitATK - AttackTarget.CurrentDef);
            return;
        }

        AttackTarget.CurrentHp -= (UnitATK - AttackTarget.CurrentMagDef);
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

    BattleState Battle;
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if((Battle.BattleStatus == BATTLE_STATUS_STARTED) || (Battle.BattleStatus == BATTLE_STATUS_FOLLOWUP) || (Battle.BattleStatus == BATTLE_STATUS_THIRD_ATTACK) )
    {

        CalcAttack(Actor, Recipient);
        CalcHit(Actor, Recipient);
    }
    else
    {
        CalcAttack(Recipient, Actor);
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

void BattleLoop(u16 EnemyUnitDevIndex){
    
    struct SkillStruct Skills[MAX_SKILLS_AMOUNT];
    BattleState Battle;
    struct SelectedUnitData Actor;
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&Skills == NULL)
    {
        return;
    }

    if(&Actor == NULL || &CurrentCharacter[EnemyUnitDevIndex] == NULL)
    {
        return;
    }
    
    BattleUnit BActor = *GenerateBattleStructPlayer(); //on player turn this is the player characters, on enemy its enemy characters
    BattleUnit BRecipient = *GenerateBattleStructEnemy(EnemyUnitDevIndex);
    MoveBattleState(BActor, BRecipient);  

    //initialise pre battle (technically not needed as func tbh tbh)

    ApplyPreBattleSkills(BActor);
    ApplyPreBattleSkills(BRecipient);

    while (Battle.BattleStatus != BATTLE_STATUS_END){
        AttackFunc(BActor, BRecipient);
        MoveBattleState(BActor, BRecipient);
    }

    if(BRecipient.CurrentHp == 0 || BActor.CurrentHp ==0)
    {
        if(BRecipient.CurrentHp == 0)
        {
            KillCharacter(BRecipient.Unitinfo -> DevelopmentIndex);
        }
        if(BActor.CurrentHp == 0)
        {
            u8 z;
            u16 DeadCharacter[MAX_POSSIBLE_RECRUITABLE_UNITS];
            for(z=0;z<=MAX_POSSIBLE_RECRUITABLE_UNITS;z++)
            {
                if(DeadCharacter[z]==0)
                {
                    DeadCharacter[z] = BActor.Unitinfo->UnitID;
                }
            }            
            KillCharacter(BActor.Unitinfo -> DevelopmentIndex);
        }        
    }

    //post battle skills go here

    u8 i;
    for(i=0;i<=5;i++)
    {
        if(Skills[BActor.Unitinfo->CurrentSkills[i]].FunctionPointer != NULL && Skills[BActor.Unitinfo->CurrentSkills[i]].SkillActivation == SKILL_ACTIVATION_POST_BATTLE)
        {
            Skills[BActor.Unitinfo->CurrentSkills[i]].FunctionPointer(0);
        }        
    }
    for(i=0;i<=5;i++)
    {
        if(Skills[BRecipient.Unitinfo->CurrentSkills[i]].FunctionPointer != NULL && Skills[BRecipient.Unitinfo->CurrentSkills[i]].SkillActivation == SKILL_ACTIVATION_POST_BATTLE)
        {
            Skills[BRecipient.Unitinfo->CurrentSkills[i]].FunctionPointer(0);
        }        
    }


    return;
};
