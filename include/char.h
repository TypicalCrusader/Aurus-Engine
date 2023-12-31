#include "types.h"
#include <stdint.h>

struct CharacterData
{
    u16 UnitID;
    u32 UnitName;
    u32 UnitDesc;
    u8 RaceID;
    u8 CharGender;
    u8 alignment;
    u16 BaseClass;
    u32 CharSkills[0x4];
    s8 BaseHp;
    s8 BaseAtk;
    s8 BaseMag;
    s8 BaseDef;
    s8 BaseMagDef;
    s8 BaseSpd;
    s8 BaseLck;
    s8 BaseDex;
    s8 HpCharGrowth;
    s8 AtkCharGrowth;
    s8 MagCharGrowth;
    s8 DefCharGrowth;
    s8 MagDefCharGrowth;
    s8 SpdCharGrowth;
    s8 LckCharGrowth;
    s8 DexCharGrowth;
    u8 BaseSwrd;
    u8 BaseDgr;
    u8 BaseSpr;
    u8 BaseAxe;
    u8 BaseThrow;
    u8 BaseBow;
    u8 BaseLight;
    u8 BaseDark;
    u8 BaseWind;
    u8 BaseFire;
    u8 BaseWater;
    u8 BaseIce;
    u8 BaseThunder;
    u8 BaseEarth;
    u8 BaseStaves;
    u8 BaseStone;
};

struct CurrCharData
{
    u16 UnitID;
    struct CharacterData CharData;
    struct ClassStruct ClassData;
    u8 InventoryData[0x5];
    u8 CurrentSkills[UINT8_MAX];
    s8 CurrHp;
    s8 CurrAtk;
    s8 CurrMag;
    s8 CurrDef;
    s8 CurrMagDef;
    s8 CurrSpd;
    s8 CurrLck;
    s8 CurrDex;
    u8 CurrSwrd;
    u8 CurrDgr;
    u8 CurrSpr;
    u8 CurrAxe;
    u8 CurrThrow;
    u8 CurrBow;
    u8 CurrLight;
    u8 CurrDark;
    u8 CurrWind;
    u8 CurrFire;
    u8 CurrWater;
    u8 CurrIce;
    u8 CurrThunder;
    u8 CurrEarth;
    u8 CurrStaves;
    u8 CurrStone;
};

struct CurrCharData CurrChar;

enum gender {
    GENDER_MALE,
    GENDER_FEMALE,
    GENDER_NONE
};

enum alignment
{
    ALIGNMENT_NONE,
    ALIGNMENT_LIGHT,
    ALIGNMENT_DARK,
    ALIGNMENT_WIND,
    ALIGNMENT_FIRE,
    ALIGNMENT_THUNDER,
    ALIGNMENT_WATER,
    ALIGNMENT_EARTH,
    ALIGNMENT_ICE,
    ALIGNMENT_ANIMA
};

struct RaceBoostStruct 
{
    s8 HPBon;
    s8 POWBon;
    s8 SKLBon;
    s8 SPDBon;
    s8 DEFBon;
    s8 RESBon;
    s8 LCKBon;
};

struct RaceSMTLikeRes
{
    u16 NulllignmentDmg [0xa];
    u16 ResAlignmentDmg [0xa];
    u16 ReverseAlignmentDmg [0xa];
    u16 SpecialWeaponNullDmg [0xa];
};

struct RaceStruct
{
    u8 RaceID;
    u8 RaceSkill;
    u16 RaceName;
    u16 RaceDesc;
    struct RaceSMTLikeRes SMTRes;
    struct RaceBoostStruct Raceboost;
    bool RaceSMTShouldNullAtk;    
};

extern struct RaceStruct Race[UINT8_MAX];

struct ClassStruct
{
    u8 ClassID;
    u32 ClassName; 
    u32 ClassDesc;
    u8 ClassType;
    u8 ClassGenderLock;
    u8 ClassSkill;
    u8 ClassPromoBranch[0x2];
    s8 BaseHp;
    s8 BaseAtk;
    s8 BaseMag;
    s8 BaseDef;
    s8 BaseMagDef;
    s8 BaseSpd;
    s8 BaseLck;
    s8 BaseDex;
    s8 HpCharGrowth;
    s8 AtkCharGrowth;
    s8 MagCharGrowth;
    s8 DefCharGrowth;
    s8 MagDefCharGrowth;
    s8 SpdCharGrowth;
    s8 LckCharGrowth;
    s8 DexCharGrowth;    
    bool ClassUsesSwrd;
    bool ClassUsesDgr;
    bool ClassUsesSpr;
    bool ClassUsesAxe;
    bool ClassUsesThrow;
    bool ClassUsesBow;
    bool ClassUsesLight;
    bool ClassUsesDark;
    bool ClassUsesWind;
    bool ClassUsesFire;
    bool ClassUsesWater;
    bool ClassUsesIce;
    bool ClassUsesThunder;
    bool ClassUsesEarth;
    bool ClassUsesStaves;
    bool ClassUsesStone;
};

enum ClassType
{
    TYPE_INFANTRY,
    TYPE_CAVALERY,
    TYPE_ARMORED,
    TYPE_LIGHT,
    TYPE_FLYER,
    TYPE_MAGICAL,
    TYPE_MONSTER,
};

