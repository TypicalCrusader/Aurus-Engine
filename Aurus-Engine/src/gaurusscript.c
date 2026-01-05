#include "gaurusscript.h"

//0-128 = local
//> 128 = global

u8 uCheckFlag(u16 uFlagNumber) {
    u64 uIndexNumber;
    u64 uShift;
    u64 uFlag;

    if(uFlagNumber > 1600)
    {
        uFlagNumber = 1600;
    };
    if(uFlagNumber > 128) { 
        uFlagNumber = uFlagNumber - 128;
        uIndexNumber = uFlagNumber / 64;
        uFlag = uGlobalFlagBitField[uIndexNumber];
        uShift = uFlagNumber - (uIndexNumber * 64);
        uFlag <<= ( uShift - 1);
        uFlag >>= 63;
        uFlag ^= 0;
    }
    else {
        uIndexNumber = uFlagNumber / 64;
        uFlag = uLocalFlagBitField[uIndexNumber];
        uShift = uFlagNumber - (uIndexNumber * 64);
        uFlag <<= ( uShift - 1);
        uFlag >>= 63;
        uFlag ^= 0;
    }
    return uFlag;
};

void vSetFlag(u16 uFlagNumber, bool uTrueFalse) {
    u64 uIndexNumber;
    u64 uShift;
    u64 uFlag;
    u64 uFlagLongLong;

    if(uFlagNumber > 1600)
    {
        uFlagNumber = 1600;
    };    
    if(uFlagNumber > 128) { 
        uFlagNumber = uFlagNumber - 128;
        uIndexNumber = uFlagNumber / 64;
        uFlagLongLong = uGlobalFlagBitField[uIndexNumber];
        uFlag = (u64) uTrueFalse;
        uShift = uFlagNumber - (uIndexNumber * 64);
        uFlag <<= 63;
        uFlag >>= ( uShift - 1);
        uFlagLongLong |= uFlag;
        uGlobalFlagBitField[uIndexNumber] = uFlagLongLong;
    }
    else  { 
        uIndexNumber = uFlagNumber / 64;
        uFlagLongLong = uLocalFlagBitField[uIndexNumber];
        uFlag = (u64) uTrueFalse;
        uShift = uFlagNumber - (uIndexNumber * 64);
        uFlag <<= 63;
        uFlag >>= ( uShift - 1);
        uFlagLongLong |= uFlag;
        uLocalFlagBitField[uIndexNumber] = uFlagLongLong;
    }
    return;
};


