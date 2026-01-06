<!--
SPDX-FileCopyrightText: 2026 =NONE

SPDX-License-Identifier: CC0-1.0
-->

BINion File Format Specification 1.0 by TypicalCrusader

BINion (Bin full of onions) is the custom binary storage file format used by
Aurus Engine.

Binions are made by python3 script which
a) creates binion file
b) creates header files with enums that have values being equal to entry name and the ID position within binion table of content

Binions are read by c based LibBINion library


BINion files are structured in following way
=============== 
=    Header   =
=   64 Bytes  =
= = = = = = = =
="B I N O 0xFF=
=     u8[5]   =
= = = = = = = =
= format ver. =
=     u32     =
= = = = = = = =
= header ver. = 
=     u32     =
= = = = = = = =
=  file CRC32 =
=     u32     =
= = = = = = = =
= file options=
=   u32 bit   =
= = = = = = = =
=  file size  =
=     u64     =
= = = = = = = =
=   reserved  =
=     u64[4]  =
= = = = = = = =
=  0xFFFEFEFF =
===============
=  Entry ID   =
=     u16     = <- max value of 
===============     INT16_MAX
=  Entry Size =
=     u32     =
===============
= Entry CRC16 =
=     u16     =
===============
=             =
=             =
=  Entry Data =
=             =
=             =
= = = = = = = =
=    0xFEFE   =
= = = = = = = =
=    0xFFFF   =
===============
=  X Entries  =
===============
=    0xFFFF   =
= = = = = = = =
=    0xFEFE   = 
===============
=  Table of   =
=  Contents   =
=  (pointers  =
=  to every   =
=  entry)     =
= u64[ENTRIES]= <- max size = uintptr_t
= = = = = = = =        [INT16_MAX] 
= Ammount of  =
=   Entries   =
=     u16     =
= = = = = = = =
=     EOF     = 
===============

# Header
- 64 bytes long
- magic numbers for binion format are 66 73 78 79 0xFF(BINO)
- format version is the current version of format it is using u32 structured in following way VVMMPPPP, V - is major version, M - is minor version, P - is patch, by the time of writing of this version of the specification current version is 1.0.0
- header version is the current version of header, it changes every time header changes, whether by additional usage of some of reserved bytes or by changing how some of other values look like, version scheme follows same rules as format version, current version is 1.0.0
- file CRC32, file crc32 calculated on creation, compared with current crc32 every time file is loaded for a first time, if it is not the same, engine will stop everything and calculate every single crc 16 of every entry in a file before logging discrapencies and then closing itself
- file options - bitfield of values,  in current specification only 2 most significant bits are used
    0 -> used to represent whether file (sans header and EOL (with 4 bytes preceding it)) is ZIP compressed
        0 - No
        1 - Yes
    1 -> used to represent whether file data (sans header and EOL (with 4 bytes preceding it)) are AES-128 encripted
        0 - No
        1 - Yes
- File size - size of file in bytes
- reserved - reserved bytes for potential future use
- 0xFFFEFEFF - Padding siginifying end of header

# Table of Contents
it is indexed (from 0) signed 16 bit array of offsets to begining of the each file entry, every entry is exactly 64 bit in length and the table size is variable on amount of entries and it is ended by 0xFF, take note that if you have many entries it make the table insanely big, as it is 8 (bytes) x amount of entries
Table of contents is ended by 0xFF byte

# Entry Data

as a name states it holds data, it itself is structured in following way:

=============== 
=  Entry ID   =
=     u16     =
===============
=  Entry Size =
=     u16     =
===============
= Entry CRC16 =
=     u16     =
===============
= Entry Header=
=   24 bytes  =
= = = = = = = =
=  Data Type  =
=     u16     =
= = = = = = = =
=Special Flags=
=   u32 bits  =
= = = = = = = = 
=   Reserved  =
=    u64[2]   =
= = = = = = = =
=    0xFFFF   =
===============
=  Entry Data =
=u8[ENTRY_SIZ]= <- technically u8
= = = = = = = =     [INT32_MAX]
=    0xFEFE   =
= = = = = = = =
=    0xFFFF   =
===============

- every entry has CRC16 it is checked if CRC 32 checksum fails on initial file load, if it fails it will check crc16 of EVERY entry and then will log out failed entry then close the game
## Entry Header
- Data Type is format type of data, in the current version of spec it supports following types of data
    0 - Table (stores whole table data)
    1 - PNG - !!8BIT PALETTE INDEXED!!
    2 - BMP - 8BIT DEPTH
    3 - OGG
    4 - MP3
    5 - WAV
    6 - ATX - Aurus Text 
    7 - MP4
    8 - AAM - Aurus AniMation
- Special Flags as with file header case are used to display some abnormal options in form of bits, as it is with header file options case only few most significant bits are used in current specification:
    0 - is entry split (note, will be ignored if last entry had flag set)
        0 - no
        1 - yes
    1 - is entry smaller than 1 KB (1024 B)
        0 - no
        1 - yes
    2 - (special) is final file entry
        0 - no
        1 - yes
- Reserved - data reserved for future use in future versions of the format
- 0xFFFF Header padding and end of header

#Entry Data
- Just a stream of bytes with size equal to entry size, each entry type might have each own rules, to know them you would need to check entry type
- 0xFEFE 0xFFFF - Padding signifying end of entry

tldr
create header -> create entry -> python saves id and entry name to enum -> entry offset is saved to a list in which offsets entry is equal to entry ID 