#include "types.h"

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
    u8 RaceSMTShouldNullAtk;    
};

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

