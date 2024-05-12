/*
                                                 ██████                            
                                                ██▒▒▒▒██                            
                                                ██▒▒▒▒██                            
                                                  ██▒▒██                            
                                                  ██▒▒██                          
                                                  ██▒▒██                          
                                                  ██▒▒██                          
                                                ██▒▒▒▒▒▒██                        
                                                ██▒▒▒▒▒▒██                        
                                            ████▒▒▒▒▒▒████                      
                                        ████▒▒▒▒▒▒▓▓▒▒▒▒▒▒████                  
                                    ████▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒████              
                                    ██▓▓▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▓▓██            
                                ██▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓██          
                                ██▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒██        
                            ██▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒██      
                            ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██    
                         ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██  
                         ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██  
 /$$       /$$          ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒██
| $$      |__/          ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██
| $$$$$$$  /$$ /$$$$$$$ ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██
| $$__  $$| $$| $$__  $$██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██
| $$  \ $$| $$| $$  \ $$  ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██  
| $$  | $$| $$| $$  | $$  ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██  
| $$$$$$$/| $$| $$  | $$    ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██    
|_______/ |__/|__/  |__/    ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██    
                              ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██      
                              ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██      
                                ██▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒██        
                                  ██▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒██          
                                    ██▓▓▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▒▒▓▓▒▒▒▒▓▓██            
                                      ██▒▒▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒██              
                                        ████▒▒▓▓▒▒▒▒▓▓▒▒▒▒▓▓▒▒████                
                                            ██████████████████                    

                        
The Binion File Format
The best onion format in the whole universe
*/

#pragma once
#include "types.h"

#define MAX_ENTRIES_OF_TYPE_IN_FILE = UINT16_MAX;

struct image {
    u32 ID;
    u8 isCompressed;
    u8 isEncrypted;     
    u8 type; 
    u16 crc16;
    u32 entrysize;
    u8 data;
};

struct sound {
    u32 ID;
    u8 isCompressed;    
    u8 isEncrypted;
    u8 type; 
    u16 crc16;  
    u32 entrysize;
    u8 data;            
};

struct text {
    u32 ID;
    u8 isCompressed;    
    u8 isEncrypted; 
    u8 type;      
    u16 crc16;   
    u32 entrysize;
    u8 data;     
};

struct gp_data {
    u32 ID;
    u8 isCompressed;
    u8 isEncrypted;  
    u8 type;       
    u16 crc16;  
    u32 entrysize;
    u8 data;      
};

struct gp_data_database
{
    u8 type;
    u8 data;
};

struct header{
    u32  signature;     //4b - BINO
    u8   version;       //1b - 0 = ver. 1.0
    u8   biniontype;    //1b - Potential future use?
    u32  crc32;         //4b
};

struct file{
    struct header       *header;
    const  u16          imagecount;
    struct image        *imagedata;
    const  u16          soundcount;
    struct sound        *sounddata;
    const u16           textcount;    
    struct text         *textdata;
    const u16           gpdatacount;    
    struct gp_data      *generaldata;
};

struct file* OpenFileIntoMemory(struct file *fileData);
u8 CheckIsBinionEncrypted();
u8 CheckIsBinionCompressed();
u8 CheckBinionEntryType(struct file *fileData);
u32 CalculateBinionCRC32();
u8 CheckIsBinionCorrupted();
u16 CalculateBinionEntryCRC16();
u8 CheckIsEntryCorrupted();
u8 SaveDatatoBinion();
u8 ReadDataFromBinion();
int EncryptBinion();
int DecryptBinion();
int CompressBinion();
int DecompressBinion();

enum image_type
{
    IMAGE_TYPE_BMP,
    IMAGE_TYPE_PNG,
    IMAGE_TYPE_TIFF
};

enum sound_type
{
    SOUND_TYPE_MID,
    SOUND_TYPE_WAV,
    SOUND_TYPE_OGG,
    SOUND_TYPE_MP3
};

enum text_type
{
    TEXT_TYPE_ANSI,
    TEXT_TYPE_UNIC,
    TEXT_TYPE_UTF8,
    TEXT_TYPE_AURS
};

enum gp_datatype
{
    GP_DATA_TYPE_SCRIPT,
    GP_DATA_TYPE_ANIM,
    GP_DATA_TYPE_DATABASE,
    GP_DATA_TYPE_OTHER
};

enum gp_data_database_type
{
    GP_DATA_DATABASE_CHAR,
    GP_DATA_DATABASE_SKILL,
    GP_DATA_DATABASE_MAP,
    GP_DATA_DATABASE_SKILL,
    GP_DATA_DATABASE_MISC
};
