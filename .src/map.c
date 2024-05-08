#include "../include/map.h"

int InitialiseMap()
{
    return 0;
};


void CheckTileType()
{

    return;
};


void MoveUnit(SelectedUnit Unit, u8 MapX, u8 MapY){
    Unit.MapX = MapX;
    Unit.MapY = MapY;
    return;
}

void AttackUnit(SelectedUnit Actor, SelectedUnit Recipient){
    BattleLoop(BattleUnit Actor, BattleUnit Recipient);
    return;
}