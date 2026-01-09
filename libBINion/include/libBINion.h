/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-only
 */

/*
!TODO:
- add checking of file options
- add checking of entry options
- add unzipping
- add huge entry handling
- add encription shit

potentially in future if ever needed (it wont be)
- fsetpos,fgetpos for 64 bit file support (aka 1 file > 4 gigs)


*/

#pragma once
#include "types.h"
#include <zlib.h>

#define BINION_FORMAT_STANDARD 0x01000000
#define BINION_HEADER_FORMAT_STANDARD 0x01000000

#define BINION_END_OF_HEADER 0xFFFF
#define BINION_END_OF_ENTRY  0xFEFEFFFF

#define BINION_MAX_ENTRY_PER_FILE UINT16_MAX

static char uBinionDataFilePath[] = "./data/";
static char uBinionFileNameSansNum[] = "data_";
static char uBinionFileExtension[] = ".bin";

#define POLY 0x8408

enum eEntryTypes {
    FILE_TYPE_TABLE,
    FILE_TYPE_PNG,
    FILE_TYPE_BMP,
    FILE_TYPE_OGG,
    FILE_TYPE_MP3,
    FILE_TYPE_WAV,
    FILE_TYPE_ATX,
    FILE_TYPE_AAM
};

enum eBinionHeaderBytes {
    HEADER_MAGIC = 0,
    HEADER_FORMAT_VER = 4,
    HEADER_HEADER_VER = 8,
    HEADER_FILE_CRC32 = 12,
    HEADER_FILE_OPTIONS = 16,
    HEADER_FILE_SIZE = 20,
    HEADER_FILE_RESERVED = 28,
    HEADER_FILE_EOE = 60
};

enum eEntrySpecialFlag {
    BINION_ENTRY_SPLIT = (1 << 0),
    BINION_ENTRY_BIG   = (1 << 1),   
    BINION_ENTRY_FINAL = (1 << 2)
};

struct gBINionEntryHeader {
    u16 uEntryDataType;
    u32 uEntrySpecialFlags;
    u64 uReserved[2];
    u16 uPadding;
};

struct gBINionEntryStruct{
    u16 uEntryID;
    u32 uEntrySize;
    u16 uEntryCRC16;
    struct gBINionEntryHeader gEntryHeader;
    u8 uEntryData[INT32_MAX];
    u32 uEOE;
};

struct gpBINionStruct {
    struct gBINionHeader {
        u8 uBINionMagicNumbers[5];
        u32 uBINionFormatVer;
        u32 uBINionHeaderVer;
        u32 uUnused;
        u32 uBINionFileOptions;
        u64 uBINionFileSize;
        u64 uReserved[4];
        u32 uEOE;
    };
    struct gBINionEntryStruct gBINionEntry[INT16_MAX];
    u32 uPadding; //0xFFFFFEFE
    struct gBINionTableofContents {
        uintptr_t gBINionEntryOffset[INT16_MAX];
        u16 uBINionEntryAmount;
    };    
    u32 uBINionCRC32;
    u8 uEOF;
};

u16 uGetBinionFileNumber(u32 uEntryID); //this gets turned into proper number anyways
FILE* gGetBINion(u32 uEntryID);

inline u32 uGetBinionStandardVersion() {
    return BINION_FORMAT_STANDARD;
};

inline u32 uGetBinionHeaderStandardVersion() {
    return BINION_HEADER_FORMAT_STANDARD;
}

u32 uGetBinionStandardVersionFromFile(u32 uEntryID);
u32 uGetBinionHeaderStandardVersionFromFile(u32 uEntryID);

bool bIsBINion(u32 uEntryID);

inline bool bIsBINionFormatDifferent(u32 uEntryID) {
    if(uGetBinionStandardVersionFromFile(uEntryID) != uGetBinionStandardVersion()){
        return false;
    }
    else {
        return true;
    }
};

inline bool bIsBINionHeaderFormatDifferent(u32 uEntryID) {
    if(uGetBinionHeaderStandardVersionFromFile(uEntryID) != uGetBinionStandardVersion()){
        return false;
    }
    else {
        return true;
    }
};

//used for error handling
inline bool bIsBINionFormatVersionGreaterThanDefined(u32 uEntryID) {
    if(uGetBinionStandardVersionFromFile(uEntryID) > uGetBinionStandardVersion()){
        return true;
    } 
    else {
        return false;
    }
};

//returns offset
u64 gGetBINionEntry(u16 uEntryID, FILE* Binion);
u32 uGetBINionFileCRC32(u32 uEntryID);
struct gBINionEntryStruct gGetBINionEntryStruct(u32 uEntryID);
uintptr_t gGetBINionEntryData(u32 uEntryID);
u16 uGetBINionEntryCRC16(u32 uEntryID);
u32 uGetBINionEntrySize(u32 uEntryID);
u16 crc16(u8 *uDataPointer, u16 ulength);

inline bool bIsEntryCRC16Correct(u32 uEntryID){
    uintptr_t BinionEntryDataPointer = gGetBINionEntryData(uEntryID);
    u32 uEntrySize = uGetBINionEntrySize(uEntryID);
    u8 BinionEntryData = (u8) memcpy(&BinionEntryDataPointer,&BinionEntryData,uEntrySize);
    if(uGetBINionEntryCRC16(uEntryID) != crc16(&BinionEntryData,uGetBINionEntrySize(uEntryID)))
    {
        return false;
    }
    else
    {
        return true;
    }
};

//ONLY RUN THIS IF IT FAILS CRC16 CHECK, IT LOADS WHOLE BINION TO MEMORY TO FUCKING CRC32 IT, DO NOT
//EVER EVER EVER RUN IT ANYWHERE ELSE
inline bool bIsBinionCRC32Correct(u32 uEntryID) {
    u32 ucrc32;
    FILE* gBinion = gGetBINion(uEntryID);

    fseek(gBinion,0L,SEEK_END);
    u32 uFilesize = ftell(gBinion);
    fseek(gBinion,0L,SEEK_SET);
    u8* uFileData = (u8*) malloc(uFilesize);
    fread(uFileData,1,uFilesize,gBinion);
    fclose(gBinion);

    if(crc32(ucrc32,uFileData,uFilesize) != uGetBINionFileCRC32(uEntryID)){
        free(&uFileData);
        return true;
    }
    free(&uFileData);
    return false;
};
u16 uGetBINionEntryDataType(u32 uEntryID);
u16 uGetBinionEntryID(u32 uEntryID);