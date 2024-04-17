#include "../include/misc.h"

u8 DiceRollOnehundred () {
    srand(time(0));
    u8 OnedDHundred = (rand() % (100 - 1 + 1)) + 1;    
    return OnedDHundred;
};

u8 DiceRollOneTwenty () {
    srand(time(0));
    u8 OneDTwenty = (rand() % (20 - 1 + 1)) + 1;    
    return OneDTwenty;   
};

u8 DiceRollOneSix () {
    srand(time(0));
    u8 OnedDSix = (rand() % (6 - 1 + 1)) + 1;    
    return OnedDSix;
};