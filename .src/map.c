#include "../include/map.h"

static void IncreaseTurnCounter(CurrentMap Map)
{
    int Currentturn = Map.CurrentTurn;
    int * Currentturn = (int*)malloc(1 * sizeof(Map));

    if (Currentturn != NULL) {
        Currentturn += 1;
        Map.CurrentTurn = Currentturn;
        return;
        free(Currentturn);
    }
    else {
        free(Currentturn); //even though no memory was assigned its still best to clear the mem, juuuust in case
        return -1;
    }
};

int InitialiseMap()
{
    return 0;
};


void CheckTileType()
{

    return;
};
