#include "../include/map.h"

int InitialiseMap(u16 MapArray[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return false;
    }


    return 0;
};

bool CheckIfTileType(u8 TileType , u8 TileX , u8 TileY)
{
    if(TileType > SPECIAL_TYPE_COLLUMN)
    {
        return false; //undefined
    }

    if(TileX > MAX_MAP_SIZE)
    {
        return false; //undefined
    }

    if(TileY > MAX_MAP_SIZE)
    {
        return false; //undefined
    }

    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return false;
    }

    if(&CurrMap.Map == NULL)
    {
        return false;
    }

    if(&CurrMap.Map->Tile == NULL)
    {
        return false;
    }

    if(&CurrMap.Map->Tile[TileX][TileY] == NULL)
    {
        return false;
    }

    if(CurrMap.Map->Tile[TileX][TileY]->TileType == TileType)
    {
        return true;
    }
    else{
        return false;
    }
};

/*
    3 args
    1 amount of movements (z)
    2. array with movements on X axis during Z move
    3. array with movements on Y axis during Z move
    IF ITS PASSING TRHOUGH UNPASSABLE TERRAIN THEN IT RETURNS -1
*/

u8 MoveUnit(u8 MovementIt, u8 MovementX[MovementIt], u8 MovementY[MovementIt]){
    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL)
    {
        return -1;
    }

    struct CurrentMap CurrMap;

    if(&CurrMap == NULL)
    {
        return -1;
    }

    if(&CurrMap.Map == NULL)
    {
        return -1;
    }

    u8 i;


    for(i=0;i<=MovementIt;i+=)
    {
        if(SelectedUnit.MapX + MovementX[i] > CurrMap.Map->MapX)
        {
            return -1;
        }
        while(SelectedUnit.MapX < SelectedUnit.MapX + MovementX[i])
        {
            SelectedUnit.MapX ++ 1;
        }
        if(SelectedUnit.MapY + MovementX[i] > CurrMap.Map->MapY)
        {
            return -1;
        }        
        while(SelectedUnit.MapY + 1 < SelectedUnit.MapY + MovementY[i])
        {
            SelectedUnit.MapY ++ 1;
        }
    } 

    return 0;
}

void AttackUnit(u16 EnemyUnitDevIndex){

    struct SelectedUnitData SelectedUnit;

    if(&SelectedUnit == NULL)
    {
        return;
    }    

    if(EnemyUnitDevIndex > MAX_DEPLOYED_ALL_UNITS)
    {
        return;
    }

    BattleLoop(SelectedUnit, EnemyUnitDevIndex);
    return;
}