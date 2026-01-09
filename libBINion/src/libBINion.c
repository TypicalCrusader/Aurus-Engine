/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only
 */

#include "libBINion.h"


u16 uGetBinionFileNumber(u32 uEntryID) {
    if(uEntryID <= BINION_MAX_ENTRY_PER_FILE)
    {
        return 1;
    }
    else {
        f32 fDivRes = 2;
        u16 uFileNumber = 2;
        while(fDivRes > 1){
            fDivRes = uEntryID / (uFileNumber * BINION_MAX_ENTRY_PER_FILE);
            if(fDivRes > 1){
                uFileNumber++;
            };
        };
        return uFileNumber; 
    }
};

u16 uGetBinionEntryID(u32 uEntryID)
{
    if(uEntryID <= BINION_MAX_ENTRY_PER_FILE)
    {
        return 1;
    }
    else
    {
        u16 uFileNumber = 2;
        u32 uEntryTemp = uEntryID;
        while(uEntryTemp > BINION_MAX_ENTRY_PER_FILE)
        {
            uEntryTemp = uEntryID - (uFileNumber * BINION_MAX_ENTRY_PER_FILE);
            if(uEntryTemp > BINION_MAX_ENTRY_PER_FILE){
                uFileNumber ++;
            }
        }

        return uEntryID - (uFileNumber * BINION_MAX_ENTRY_PER_FILE);
    }
};

FILE* gGetBINion(u32 uEntryID) {
    u16 uBinionFileNum = uGetBinionFileNumber(uEntryID);
    char *uFilePath = malloc((sizeof(uBinionDataFilePath-1) + sizeof(uBinionFileNameSansNum-1))+(sizeof(uBinionFileNum)+sizeof(uBinionFileExtension-1))+1);
    memset(&uFilePath,0,(sizeof(uBinionDataFilePath-1) + sizeof(uBinionFileNameSansNum-1))+(sizeof(uBinionFileNum)+sizeof(uBinionFileExtension-1))+1);
    memcpy(&uFilePath, &uBinionDataFilePath, strlen(uBinionDataFilePath));
    memcpy(&uFilePath, &uBinionFileNameSansNum, strlen(uBinionFileNameSansNum));
    memcpy(&uFilePath, &uBinionFileNum, 2);
    memcpy(&uFilePath, &uBinionFileExtension, strlen(uBinionFileExtension));
    memcpy(&uFilePath, "\0", 1);
    FILE* gBinion;
    gBinion = fopen(uFilePath,"rb+");   
    free(uFilePath);
    return gBinion;
};

bool bIsBINion(u32 uEntryID) {
    FILE* gBinion = gGetBINion(uEntryID);
    u8 gBuffer[5];
    u8 uMagicNumber[5] = "BINO";
    uMagicNumber[4] = 0xff;
    fread(gBuffer,1,5,gBinion);
    fclose(gBinion);
    if(gBuffer != uMagicNumber) {
        free(gBuffer);
        return false;
    }
    else {
        free(gBuffer);
        return true;
    }
};

u32 uGetBINionStandardVersionFromFile(u32 uEntryID) {
    FILE* gBinion = gGetBINion(uEntryID);
    u32 uBuffer;
    u32 uBinionVersion;

    fseek(gBinion,HEADER_FORMAT_VER,SEEK_SET);
    fread(&uBuffer,__SIZEOF_INT__,1,gBinion);
    fclose(gBinion);
    uBinionVersion = uBuffer;
    free(&uBuffer);

    return uBinionVersion;
};

u32 uGetBinionHeaderStandardVersionFromFile(u32 uEntryID) {
    FILE* gBinion = gGetBINion(uEntryID);
    u32 uBuffer;
    u32 uBinionHeaderVersion;

    fseek(gBinion,HEADER_HEADER_VER,SEEK_SET);
    fread(&uBuffer,(__SIZEOF_INT__),1,gBinion);
    fclose(gBinion);
    uBinionHeaderVersion = uBuffer;
    free(&uBuffer);

    return uBinionHeaderVersion;  
}

u64 gGetBINionEntry(u16 uEntryID, FILE* Binion)
{
    u64 uBuffer;
    u16 uBuffer2;
    u64 uEntryOffset;
    FILE* gBinion = Binion;

    fseek(gBinion,-(1+(__SIZEOF_SHORT__+__SIZEOF_INT__)),SEEK_END); //go to end binion an go 7 bytes back to get to entry amount
    fread(&uBuffer,__SIZEOF_SHORT__,1,gBinion); //Read Entry amount to buffer

    //get sizes of entry table and all entries up to ours
    uBuffer2 = (__SIZEOF_LONG__ * uBuffer);
    uBuffer = (__SIZEOF_LONG__ * uEntryID);

    //go to our entry in table
    fseek(gBinion,-((uBuffer2-uBuffer)-1),SEEK_CUR);

    //free what we no longer neeed
    free(&uBuffer);
    free(&uBuffer2);

    uBuffer = (uintptr_t) malloc(__SIZEOF_LONG__);

    fread(&uBuffer,__SIZEOF_LONG__,1,gBinion);
    fclose(gBinion);
    uEntryOffset = uBuffer;
    free(&uBuffer);
    return uEntryOffset;

};

struct gBINionEntryStruct gGetBINionEntryStruct(u32 uEntryID)
{
    struct gBINionEntryStruct gEntry;
    FILE* gBinion = gGetBINion(uEntryID);

    u64 uEntryOffset = gGetBINionEntry(uGetBinionEntryID(uEntryID),gBinion);

    fseek(gBinion,(uEntryOffset),SEEK_SET); 
    fread(&gEntry.uEntryID,__SIZEOF_SHORT__,1,gBinion); //get entryID
    fseek(gBinion,__SIZEOF_SHORT__,SEEK_CUR);
    fread(&gEntry.uEntrySize,__SIZEOF_INT__,1,gBinion); //get EntrySize
    fseek(gBinion,__SIZEOF_INT__,SEEK_CUR);
    fread(&gEntry.uEntryCRC16,__SIZEOF_SHORT__,1,gBinion); //get EntryCRC16
    fseek(gBinion,__SIZEOF_SHORT__,SEEK_CUR);
    fread(&gEntry.gEntryHeader.uEntryDataType,__SIZEOF_SHORT__,1,gBinion);
    fseek(gBinion,__SIZEOF_SHORT__,SEEK_CUR);
    fread(&gEntry.gEntryHeader.uEntrySpecialFlags,__SIZEOF_INT__,1,gBinion);
    fseek(gBinion,__SIZEOF_INT__,SEEK_CUR);
    fread(&gEntry.gEntryHeader.uReserved[0],__SIZEOF_LONG__,1,gBinion);
    fseek(gBinion,__SIZEOF_LONG__,SEEK_CUR);
    fread(&gEntry.gEntryHeader.uReserved[1],__SIZEOF_LONG__,1,gBinion);
    fseek(gBinion,__SIZEOF_LONG__,SEEK_CUR);
    fread(&gEntry.gEntryHeader.uPadding,__SIZEOF_SHORT__,1,gBinion);
    fseek(gBinion,__SIZEOF_SHORT__,SEEK_CUR);
    fread(&gEntry.uEntryData,1,gEntry.uEntrySize,gBinion); //get EntryData
    fseek(gBinion,gEntry.uEntrySize,SEEK_CUR);
    fread(&gEntry.uEOE,__SIZEOF_INT__,1,gBinion);
    fclose(gBinion);

    return gEntry;
}



uintptr_t gGetBINionEntryData(u32 uEntryID)
{
    FILE* gBinion = gGetBINion(uEntryID);

    u32 uBuffer;
    u64 uEntryOffset = gGetBINionEntry(uGetBinionEntryID(uEntryID),gBinion);
    fseek(gBinion,(uEntryOffset),SEEK_SET); 

    fseek(gBinion,(__SIZEOF_SHORT__ ),SEEK_CUR);  
    fread(&uBuffer,__SIZEOF_INT__,1,gBinion); //get EntrySize

    uintptr_t  gBuffer2;
    fseek(gBinion,(__SIZEOF_INT__ + __SIZEOF_SHORT__),SEEK_CUR);
    fread(&gBuffer2,1,gBuffer2,gBinion);
    fclose(gBinion);
    free(&uBuffer);

    return gBuffer2;
};

u16 uGetBINionEntryCRC16(u32 uEntryID) {

    FILE* gBinion = gGetBINion(uEntryID); 
    u16 uBuffer;
    u64 uEntryOffset = gGetBINionEntry(uGetBinionEntryID(uEntryID),gBinion);  
    u16 uTemp;

    fseek(gBinion,(uEntryOffset),SEEK_SET);   
    fseek(gBinion,(__SIZEOF_SHORT__+__SIZEOF_INT__),SEEK_CUR); 
    fread(&uBuffer,__SIZEOF_SHORT__,1,gBinion); 
    fclose(gBinion);
    uTemp = uBuffer;
    free(&uBuffer);
    return uTemp;
}

u32 uGetBINionEntrySize(u32 uEntryID)
{
    FILE* gBinion = gGetBINion(uEntryID); 
    u32 uBuffer;
    u32 uEntrySize;
    u64 uEntryOffset = gGetBINionEntry(uGetBinionEntryID(uEntryID),gBinion);  

    fseek(gBinion,(uEntryOffset),SEEK_SET);   
    fseek(gBinion,(__SIZEOF_SHORT__ ),SEEK_CUR);  
    fread(&uBuffer,__SIZEOF_INT__,1,gBinion); //get EntrySize
    uEntrySize = uBuffer;
    free(&uBuffer);
    fclose(gBinion);

    return uEntrySize;
}

u32 uGetBINionFileCRC32(u32 uEntryID) {
    FILE* gBinion = gGetBINion(uEntryID); 
    u32 uBuffer;
    u32 uBinionCRC32;
    fseek(gBinion,-(1+__SIZEOF_INT__),SEEK_END); 
    fread(&uBuffer,__SIZEOF_INT__,1,gBinion);
    fclose(gBinion);
    uBuffer = uBinionCRC32;
    free(&uBuffer);
    return uBinionCRC32;
};

/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/
u16 crc16(u8 *uDataPointer, u16 ulength)
{
    u8 i;
    u32 data;
    u32 crc = 0xffff;

    if (ulength == 0)
        return (~crc);

    do
    {
        for (i=0, data=(unsigned int)0xff & *uDataPointer++;
                i < 8; 
                i++, data >>= 1)
        {
                if ((crc & 0x0001) ^ (data & 0x0001))
                    crc = (crc >> 1) ^ POLY;
                else  crc >>= 1;
        }
    } while (--ulength);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);
}

u16 uGetBINionEntryDataType(u32 uEntryID)
{
    FILE* gBinion = gGetBINion(uEntryID);

    u64 uEntryOffset = gGetBINionEntry(uGetBinionEntryID(uEntryID),gBinion);
    u16 uBuffer;
    u16 uBinionDataType;

    fseek(gBinion,(uEntryOffset + 8),SEEK_SET); 
    fread(&uBuffer,__SIZEOF_SHORT__,1,gBinion);  
    fclose(gBinion);

    uBinionDataType = uBuffer;
    free(&uBuffer);

    return uBinionDataType;
};