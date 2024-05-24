
#include "../include/char.h"

void ExchangeInvSlotInfo(u8 SlotFrom, u8 SlotInto)
{
    if(&Character != NULL) //sanity check so we dont access unalocated memory
    {

    }
    return;
};
void ChangeGender(u8 Gender) //fuckin dragons are putting magic into the water that turns the heckin humans gae
{
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return;
    }
    if(Gender > GENDER_NONE) //3 defined
    {
        return;
    }

    CurrentCharacter->MiscData.gender = Gender;

    return;
}
void ChangeAlignment(u8 Alignment)
{
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return;
    }
    if(Alignment > ALIGNMENT_ANIMA) 
    {
        return;
    }
    CurrentCharacter->CharData->alignment = Alignment;

    return;
}
//0-23 follows the CurrCharData order
u8 GetStatSkill(u8 Stat){
    struct CurrCharData CurrentCharacter[MAX_DEPLOYED_ALL_UNITS];

    if(&CurrentCharacter == NULL) //sanity check so we dont access unalocated memory
    {
        return 0;
    }
    if(Stat > 23) 
    {
        return 0;
    }
    if(&CurrentCharacter + (39+Stat) == NULL)
    {
        return 0;
    }

    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL){
        return 0;
    }
    #if UINTPTR_MAX != UINT32_MAX
        u8 *StatVal = &CurrentCharacter[SelectedUnit.DeploymentIndex] + (54+Stat);
    #elif UINTPTR_MAX == UINT32_MAX
        u8 *StatVal = &CurrentCharacter[SelectedUnit.DeploymentIndex] + (34+Stat); 

    #else
        //something is severly fucked
        //TODO ADD ERROR HERE
        return -1;
    #endif

    if(&StatVal == NULL)
    {
        //TODO ADD ERROR HERE
        return -1;
    }
    return *StatVal;
};
u16 GetCharID(){

    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL)
    {
        return -1;
    }
    if(&SelectedUnit.Unit == NULL)
    {
        return -1;
    }    
    return SelectedUnit.Unit->UnitID;
};
u8 GetRace(){

    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL)
    {
        return -1;
    }
    if(&SelectedUnit.Unit == NULL)
    {
        return -1;
    }
    return SelectedUnit.Unit->RaceID;
};