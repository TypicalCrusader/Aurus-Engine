#include "../include/types.h"

struct FileDataStruct
{
    int EntryIndex;
    int EntrySize;
    int EntryData[];
    short CRC16;
};


struct filestructure
{
    short FileHandlerVer; //0001,0002 ect
    u8 ArchiveType; // 00-Universal, 01 Image - dds, 02 - image - tga, 03 - image - png, 04 - Anim data - pngs mixed with anim commands, 05 - music - mid, 06 - music - obb
    bool IsEncrypted; //True for encrypted archive, False for not encrypted archive
    bool IsCompressed; //True if Compressed, only avilable for universal and image data sans 04
    int ArchiveSize; // Size of archive in bytes, just for redundancy
    struct FileDataStruct FileData;
    short CRC16; //obvious
};


