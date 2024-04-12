#include "../include/misc.h"

int DiceRollOnehundred () {
    srand(time(0));
    int OnedDHundred = (rand() % (100 - 1 + 1)) + 1;    
    return OnedDHundred;
};

int DiceRollOneTwenty () {
    srand(time(0));
    int OneDTwenty = (rand() % (20 - 1 + 1)) + 1;    
    return OneDTwenty;   
};

int DiceRollOneSix () {
    srand(time(0));
    int OnedDSix = (rand() % (6 - 1 + 1)) + 1;    
    return OnedDSix;
};