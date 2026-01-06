/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "rng.h"


bool bIsNumberEven(u32 unumber) {
    u32 unumber;
    if(unumber == 0){
        return true;
    }
    else {
        unumber = unumber % 2;
        if(unumber == 0) {
            return true;
        }
        else {
            return false;
        }
    }
}

u8 uRollD100()
{
    srand(time(NULL));

    u32 uRandNum1 = rand();
    u32 uRandNum2 = rand();
    uRandNum1 = uRandNum1 ^ uRandNum2;
    uRandNum1 = uRandNum1 / 0x10000000;
    return (u8) uRandNum1;
};

u8 uRoll2D100(){
    return (uRollD100() + uRollD100());
};

u8 uRollD20(){
    srand(time(NULL));

    u32 uRandNum1 = rand();
    u32 uRandNum2 = rand();
    uRandNum1 = uRandNum1 ^ uRandNum2; 
    uRandNum1 <<= 27;
    uRandNum1 >>= 27;

    if(uRandNum1 > 20 )
    {
        if(bIsNumberEven(uRollD6()) == true)
        {
            uRandNum1 / 2;
        }
        else {
            uRandNum1 == 20;
        };
    };
    return (u8) uRandNum1;
};

u8 uRollD6()
{
    srand(time(NULL));

    u32 uRandNum1 = rand();
    u32 uRandNum2 = rand();
    uRandNum1 = uRandNum1 ^ uRandNum2; 
    uRandNum1 <<= 29;
    uRandNum1 >>= 29;

    if(uRandNum1 == 7)
    {
        uRandNum1 = 6;
    };
    return (u8) uRandNum1;
};

u8 uRollD4()
{
    srand(time(NULL));

    u32 uRandNum1 = rand();
    u32 uRandNum2 = rand();
    uRandNum1 = uRandNum1 ^ uRandNum2; 
    uRandNum1 <<= 31;
    uRandNum1 >>= 31;
    return (u8) uRandNum1;
};