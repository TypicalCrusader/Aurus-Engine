#include <stdlib.h>
#include <time.h>

inline int DiceRollOnehundred () {
    srand(time(0));
    int OnedDHundred = (rand() % (100 - 1 + 1)) + 1;    
    return OnedDHundred;
}

inline int DiceRollOneSix () {
    srand(time(0));
    int OnedDSix = (rand() % (6 - 1 + 1)) + 1;    
    return OnedDSix;
}
