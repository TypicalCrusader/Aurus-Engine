#pragma once
#include "types.h"
#include "character.h"
#include "class.h"
#include "item.h"

//most important defs
#define AURUS_SCRIPT_VERSION 0.5
#define MAX_GLOBAL_COUNTERS 16
typedef uintptr_t gpEvent;
static u64 uLocalFlagBitField[2];
static u64 uGlobalFlagBitField[13];
static u16 uGlobalCounters[MAX_GLOBAL_COUNTERS];
static u8  uGamePath;
static u8  uCurrentTurnNumber;
static u16 uPartyGold;

//"global" enums
enum eVictoryEventTypes {
    VICTORY_CONDITION_KILL_ALL = 0,
    VICTORY_CONDITION_DEFEND = 1,
    VICTORY_CONDITION_DEFEND_CHARACTER = 2,
    VICTORY_CONDITION_SURVIVE = 3,
    VICTORY_CONDITION_DEFEAT = 4,
    VICTORY_CONDITION_KILL_X_ENEMIES = 5,
};

enum ePlaceEventTypes {
    PLACE_EVENT_DEFAULT,
    PLACE_EVENT_CHARACTER_LIVES,
    PLACE_EVENT_CHARACTER_DONT_LIVE,
    PLACE_EVENT_CHARACTER_HAVE_ITEM,
    PLACE_EVENT_CHARACTER_DONT_HAVE_ITEM,
    PLACE_EVENT_FLAG_SET,
    PLACE_EVENT_FLAG_DONT_SET,
    PLACE_EVENT_SHOP
};

enum eConditionalEventTypes {
    CONDITIONAL_EVENT_CHARACTER_LIVES,
    CONDITIONAL_EVENT_CHARACTER_DONT_LIVE,
    CONDITIONAL_EVENT_CHARACTER_HAS_CLASS,
    CONDITIONAL_EVENT_CHARACTER_DONT_HAS_CLASS,    
    CONDITIONAL_EVENT_FLAG_SET,
    CONDITIONAL_EVENT_FLAG_DONT_SET,    
    CONDITIONAL_EVENT_CHARACTER_HAVE_ITEM,
    CONDITIONAL_EVENT_CHARACTER_DONT_HAVE_ITEM,
    CONDITIONAL_EVENT_ANY_CHARACTER_HAVE_ITEM,
    CONDITIONAL_EVENT_ANY_CHARACTER_DONT_HAVE_ITEM    
};

enum eTrapTypes {
    TRAP_TYPE_FUMES,
    TRAP_TYPE_MINE,
    TRAP_TYPE_BOMB,
    TRAP_TYPE_WOLF
};

enum eDestroyableTypes {
    DESTROYABLE_TYPE_CASTLE_WALL,
    DESTROYABLE_TYPE_WALL,
    DESTROYABLE_TYPE_SNAG,
    DESTROYABLE_TYPE_DOOR,
    DESTROYABLE_TYPE_CHEST
};

enum eDestroyableTypes {
    MAP_WPN_TYPE_BALLISTA,
    MAP_WPN_TYPE_CATAPULT,
    MAP_WPN_TYPE_MAGIC_ORB
};

//structs that are baked inside exec
typedef struct gpChapterVictoryConditionsStruct {
    u8 uVictoryType;
    u32 uCharacterID;
    u8 uTurnCount;
    u8 uEnemyCount;
    u8 uX;
    u8 uY;
}CHAPTER_VICTORY_CONDITIONS;

typedef struct gpChapterTurnEventListStruct {
    u8 uEventType;
    u8 uTurn;
    u8 uSetFlag;
    u8 uCheckFlag;
    gpEvent uEvent;
}CHAPTER_TURN_EVENT_LIST;

typedef struct gpChapterMapEventListStruct {
    u8 uEventType;
    u8 uSetFlag;
    u8 uCheckFlag;
    u8 uX;
    u8 uY;
    u32 uItemID;
    u32 uCharacterID;
    gpEvent uEvent;
    SHOPINVENTORY gShopInventory;
}CHAPTER_EVENT_LIST;

typedef struct gpChapterConditionalEventListStruct {
    u8 uEventType;    
    u16 uFlagToSet;
    u16 uFlagToCheck;
    u32 uCharacterID;
    u32 uCharacterClass;
    u32 uItemID;
    gpEvent gEvent;
}CHAPTER_CONDITIONAL_EVENT_LIST;

typedef struct gpTrapListStruct {
    u8 uTrapType;
    u8 uX;
    u8 uY
}CHAPTER_TRAP_LIST;

typedef struct gpMapWeaponsAndDestroyablesListStruct {
    u8 uTrapType;
    u8 uX;
    u8 uY
}CHAPTER_MAP_WEAPON_AND_DESTROYABLES_LIST;

struct gpChapterEventStruct {
    DATA CHAPTER_VICTORY_CONDITIONS gVictoryConditions;
    DATA CHAPTER_TURN_EVENT_LIST gTurnEventsList; // <- happens at x turn or range between x and y
    DATA CHAPTER_EVENT_LIST gMapEventsList;
    DATA CHAPTER_CONDITIONAL_EVENT_LIST gConditionalEventsList;
    DATA CHAPTER_TRAP_LIST gTrapList;
    DATA CHAPTER_MAP_WEAPON_AND_DESTROYABLES_LIST gMapWeaponsAndDestroyablesList;
    DATA gpEvent gMainEvent;
};

static struct gpChapterEventStruct GlobalEventTable[UINT16_MAX];

typedef struct gpUnitDefStruct {
    u32 uCharacterID;
    u32 uClassID;
    u8  uLevel;
    bool bAutolevel;
    u32 uInventory[5];
    u8  uAlignment;
    u64 uAI;
    u8  uX;
    u8  uY

}UNITDEF;

typedef struct gpUnitMoveStruct {
    u8 uX;
    u8 uY
}MOVEMENTDEF;

typedef struct gpPlaceEventStruct {
    u8 uEventType;
    u8 uSetFlag;
    u8 uCheckFlag;
    u8 uX;
    u8 uY;
    u32 uItemID;
    u32 uCharacterID;
    gpEvent uEvent;
}PLACEVENT;

typedef struct gpShopInventoryDefStruct {
    u32 uItemID;
    u16 uPrice;
    u8  uQuantity;
}SHOPINVENTORY;

//flags
u8 uCheckFlag(u16 uFlagNumber);
void vSetFlag(u16 uFlagNumber, bool uTrueFalse);

//counters
inline void vSetCounter(u8 uCounterNumber, u16 uCounterValue){
    uGlobalCounters[uCounterNumber] = uCounterValue;
    return;
};

//Promote
void vSilentPromote(u32 CharacterID, u32 Class);
void vPromote(u32 CharacterID, u32 Class, u32 Item);

//Text Display Stuff
void vDisplayText(u64 TextID);
void vResumeText();

//Add Item/gold
void vAddItem(u32 ItemID);
void vRemoveItem(u32 ItemID);
void vAddGold(u16 Gold);

//recruit/kill characters
void vRecruitCharacter(u32 CharacterID);
void vRetreatCharacter(u32 CharacterID);
void vKillCharacter(u32 CharacterID);

//map chapter change related
void vChangeMap(u32 uMapIndex);
void vChapterVictory();
void vGOTOChapterSkipWM(u32 uChapterID);
void vGOTOChapter(u32 uChapterID);
void vGOTOChapterSkipWMAndChangePath(u32 uChapterID);
void vGOTOChapterChangePath(u32 uChapterID);
void vGameOver();

//victory conditions
#define cKillAll {VICTORY_CONDITION_KILL_ALL,0,0,0,0,0}
#define cDefend(x,y) {VICTORY_CONDITION_DEFEND,0,0,0,(x),(y)}
#define cDefendCharacter(CharacterID) {VICTORY_CONDITION_DEFEND_CHARACTER,(CharacterID),0,0,0,0}
#define cSurvive(TurnCount) {VICTORY_CONDITION_SURVIVE,0,(TurnCount),0,0,0}
#define cDefeat(CharacterID) {VICTORY_CONDITION_DEFEAT,(CharacterID),0,0,0,0}
#define cKillXEnemies(EnemyCount) {VICTORY_CONDITION_KILL_X_ENEMIES,0,0,(EnemyCount),0,0}

//path related shit
enum ePathTypes {
    PATH_PATH_A,
    PATH_PATH_B,
    PATH_PATH_C
};
#define cChangePath(Path) uGamePath = Path
#define cCheckPath() uGamePath

//character movement
void vMoveOnto(MOVEMENTDEF Movement ); 
void vMoveOntoIgnoreTerrain(MOVEMENTDEF Movement);
void vMoveTo(MOVEMENTDEF Movement);
void vMoveToIgnoreTerrain(MOVEMENTDEF Movement);
void vMoveToCharacter(u32 CharacterID);
void vMoveToCharacterIgnoreTerrain(u32 CharacterID);
#define cMoveDef(x, y) {(x),(y)}

//unit spawning related
void vSpawnUnit(UNITDEF UnitDataList);
#define cUnitDef(Character,Class,Level,AutoLevel,Inv1,Inv2,Inv3,Inv4,Inv5,Alignment,AI,x,y) {(Character),(Class),(Level),(AutoLevel),{Inv1,Inv2,Inv3,Inv4,Inv5},(Alignment),(AI),(x),(y)}

//place events
#define cPlaceEvent(x, y, Event, SetFlag) {PLACE_EVENT_DEFAULT,(SetFlag),0,(x),(y),0,0,(Event),0}
#define cPlaceEventIfXLives(x, y, Character, Event, SetFlag) {PLACE_EVENT_CHARACTER_LIVES,(SetFlag),0,(x),(y),0,(Character),(Event),0}
#define cPlaceEventIfXDontLives(x, y, Character, Event, SetFlag) {PLACE_EVENT_CHARACTER_DONT_LIVE,(SetFlag),0,(x),(y),0,(Character),(Event),0}
#define cPlaceEventIfXLivesHasY(x, y, Character, ItemID, Event, SetFlag) {PLACE_EVENT_CHARACTER_HAVE_ITEM,(SetFlag),0,(x),(y),(ItemID),(Character),(Event),0}
#define cPlaceEventIfXLivesDontHaveY(x, y, Character, ItemID, Event, SetFlag) {PLACE_EVENT_CHARACTER_DONT_HAVE_ITEM,(SetFlag),0,(x),(y),(ItemID),(Character),(Event),0}
#define cPlaceEventIfFlagSet(x, y, Event, SetFlag, CheckFlag) {PLACE_EVENT_FLAG_SET,(SetFlag),(CheckFlag),(x),(y),0,0,(Event),0}
#define cPlaceEventIfFlagDontSet(x, y, Event, SetFlag, CheckFlag) {PLACE_EVENT_FLAG_DONT_SET,(SetFlag),(CheckFlag),(x),(y),0,0,(Event),0}
#define cShopEvent(x, y, ShopInventory) {PLACE_EVENT_SHOP,0,0,(x),(y),0,0,0,(ShopInventory)}

// checks
bool bIsCharacterDead(u32 CharacterID);
bool bIsCharacterAlive(u32 CharacterID);
bool bIsCharacterDeployed(u32 CharacterID);
bool bIsCharacterRecruited(u32 CharacterID);
bool bIsCharacteratXYCoords(u8 x, u8 y, u32 CharacterID);
bool bAreXEnemiesDead(u8 Amout);
bool bAreXAlliesDead(u8 Amount);
bool bAreXPlayersDead(u8 Amount);
inline bool bHaveXGold(u16 Amount) {
    if(uPartyGold == Amount) { return true; }    
    else { return false; };
}
inline bool bHaveMoreGoldThan(u16 Amount) {
    if(uPartyGold > Amount) { return true; }    
    else { return false; };
}
inline bool bHaveMoreGoldThanOrEqual(u16 Amount) {
    if(uPartyGold >= Amount) { return true; }    
    else { return false; };
}
bool bHaveItem(u32 ItemID);

//conditional events
#define cTriggerEventIfXDead(SetFlag, CharacterID, Event) {CONDITIONAL_EVENT_CHARACTER_LIVES,(SetFlag),0,(CharacterID),0,0,(Event)}
#define cTriggerEventIfXDeployed(SetFlag, CharacterID, Event) {CONDITIONAL_EVENT_CHARACTER_DONT_LIVE,(SetFlag),0,(CharacterID),0,0,(Event)}
#define cTriggerEventIfXHaveClass(SetFlag, CharacterID, Class, Event) {CONDITIONAL_EVENT_CHARACTER_HAS_CLASS,(SetFlag),0,(CharacterID),(Class),0,(Event)}
#define cTriggerEventIfXDontHaveClass(SetFlag, CharacterID, Class, Event) {CONDITIONAL_EVENT_CHARACTER_DONT_HAS_CLASS,(SetFlag),0,(CharacterID),(Class),0,(Event)}
#define cTriggerEventIfFlagSet(SetFlag, CheckFlag, Event) {CONDITIONAL_EVENT_FLAG_SET,(SetFlag),(CheckFlag),0,0,0,(Event)}
#define cTriggerEventIfFlagDontSet(SetFlag, CheckFlag, Event) {CONDITIONAL_EVENT_FLAG_DONT_SET,(SetFlag),(CheckFlag),0,0,0,(Event)}
#define cTriggerEventIfHaveItem(SetFlag, ItemID, Event) {CONDITIONAL_EVENT_CHARACTER_HAVE_ITEM,(SetFlag),0,0,0,(ItemID),(Event)}
#define cTriggerEventIfDontHaveItem(SetFlag, ItemID, Event) {CONDITIONAL_EVENT_CHARACTER_DONT_HAVE_ITEM,(SetFlag),0,0,0,(ItemID),(Event)}
#define cTriggerEventIfXHaveItem(SetFlag, CharacterID, ItemID, Event) {CONDITIONAL_EVENT_ANY_CHARACTER_HAVE_ITEM,(SetFlag),0,(CharacterID),0,(ItemID),(Event)}
#define cTriggerEventIfXDontHaveItem(SetFlag, CharacterID, ItemID, Event) {CONDITIONAL_EVENT_ANY_CHARACTER_DONT_HAVE_ITEM,(SetFlag),0,(CharacterID),0,(ItemID),(Event)}

//traps
#define cTrapFumes(x, y) {TRAP_TYPE_FUMES,(x),(y)}
#define cTrapMine(x, y) {TRAP_TYPE_MINE,(x),(y)}
#define cTrapBomb(x, y) {TRAP_TYPE_BOMB,(x),(y)}
#define cTrapWolfTrap(x, y) {TRAP_TYPE_WOLF,(x),(y)}

//destroyables
#define cCastleWall(x, y) {DESTROYABLE_TYPE_CASTLE_WALL,(x),(y)}
#define cWall(x, y) {DESTROYABLE_TYPE_WALL,(x),(y)}
#define cSnag(x, y) {DESTROYABLE_TYPE_SNAG,(x),(y)}
//technically not destroyable
#define cDoor(x, y) {DESTROYABLE_TYPE_DOOR,(x),(y)} 
#define cChest(x, y) {DESTROYABLE_TYPE_CHEST,(x),(y)} 

//map weapons
#define cBallista(x, y, Uses) {MAP_WPN_TYPE_BALLISTA,(x),(y),(Uses)}
#define cCatapult(x, y, Uses) {MAP_WPN_TYPE_CATAPULT,(x),(y),(Uses)}
#define cMagicOrb(x, y, Uses) {MAP_WPN_TYPE_MAGIC_ORB,(x),(y),(Uses)}

//cutscene
void vSpawnCutsceneCharacter(u32 CharacterID);
void vShakeScreen(u8 MSec, u8 Intensity);
void vFlashScreen(u8 MSec, u8 Intensity);
void vFadeToBlack(u8 Speed);
void vFadeFromBlack(u8 Speed);

//misc shit
#define cTriggerEvent(Event) Event()

//potential area for typos
