AAM (Aurus AniMation) File Format Specification 1.0 by TypicalCrusader

Released under GPLv2 license (as is the whole Aurus Engine Project)

AMM is the custom file format for storing animation data, used by Aurus engine

AAM's are made by python3 script which
a) creates AAM file
b) creates header files with paths to every single AAM file, they have the name of __[ANIMATION_NAME]_ANIM

AAM's are read by c based LibAurusAnim library, the animation files are structured in following way:


=============== 
=    Header   =
=   64 Bytes  =
= = = = = = = =
=   "A A M"   =
=    u8[3]    =
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
=     u64[3]  =
= = = = = = = =
= beginning of=
=data position=
=     u64     =
= = = = = = = =
=  0xFFFEFEFF =
===============
=     DATA    = <- split into frames, max data per entry 32 788 bytes -> 0.032 MB  
= = = = = = = =
=  Entry CRC16=
=     u16     =
= = = = = = = =
=    Speed    =
=      u8     =
= = = = = = = =
=     SFX     =
=     u32     =
= = = = = = = =
=     GFX     =
=     u32     =
= = = = = = = = 
=  Frame Size =
=     u16     = <- max size of INT16_MAX
= = = = = = = = 
=Frame Picture= <- 8bit (256c) depth png  
=   u8[u16]   = <- max size = u8[INT16_MAX]
= = = = = = = =
=  Next Entry = <- location of the byte in which next entry starts
=     u64     =
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
= = = = = = = =
=     EOF     =  
=============== 

Every animation consists of 2 things
- series of 8bit pallete pngs
- .conf file which setups animation frames, their time, other gfx, sfx and type by default character animations follow similar format of anim types to that of Fire Emblem GBA games, aka there are types of animations for every type of weapon and item, every animation is more or less tied to character class.