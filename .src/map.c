#include "../include/map.h"

int InitialiseMap()
{
    return 0;
};


void CheckTileType()
{

    return;
};


void MoveUnit(struct SelectedUnitData Unit, u8 MapX, u8 MapY){
    Unit.MapX = MapX;
    Unit.MapY = MapY;
    return;
}

void AttackUnit(struct SelectedUnitData Actor, u16 EnemyUnitDevIndex){

    BattleLoop(Actor, EnemyUnitDevIndex);
    return;
}