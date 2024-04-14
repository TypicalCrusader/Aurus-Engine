#pragma once

#include "types.h"
#include "misc.h"
#include "char.h"
#include "inventory.h"
#include <stdlib.h>
#include <assert.h>

u8 PermaFlags[UINT8_MAX];
u8 TempFlags[UINT8_MAX];
/*
    `void SetPermaFlagTo` - Sets Permament flag to either `0` or `1`
    \param `Flag` FlagID
    \param `SetUnset` Either `0` or `1` decides if flag is set or not, `0` unsets, `1` sets`
    \returns Returns Flag Value which is `0` if unset and `1` if set
    \since This Function is available since version 0.1 of Aurus Engine
*/
void SetPermaFlagTo(u8 Flag, u8 SetUnset );
/*
    `CheckPermaFlag` - Checks Permament flag value and returns it
    \param `Flag` FlagID
    \returns `PermaFlags[Flag]`
    \since This Function is available since version 0.1 of Aurus Engine
*/
int CheckPermaFlag(u8 Flag);
/*
    `void SetTempFlagto` - Sets Temporary flag to either `0` or `1`
    Temporary Flags despite getting unset upon chapter's end persist through midchapter saves
    \param `Flag` FlagID
    \param `SetUnset` Either `0` or `1` decides if flag is set or not, `0` unsets, `1` sets`
    \returns Returns Flag Value which is `0` if unset and `1` if set
    \since This Function is available since version 0.1 of Aurus Engine
*/
void SetTempFlagto(u8 Flag, u8 SetUnset);
/*
    `CheckTempFlag` - Checks Temporary flag value and returns it
    \param `Flag` FlagID
    \returns `TempFlags[Flag]`
    \since This Function is available since version 0.1 of Aurus Engine
*/
int CheckTempFlag(u8 Flag);
/*
    `AddGoldToTeam` - Adds `GoldAmount` to Gold Data
    \param `GoldAmount`  Amount of Gold to add 
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine    
*/
void AddGoldToTeam(u16 GoldAmount);
/*
    `AddItemToCharacter` - Adds `Item` to Character Invetory
    if inventory is full it will send item to Convoy, if convoy is full and item has special flag then first non story important item shall be purged from convoy data
    \param `CharID` CharacterID
    \param `ItemID` ItemID
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void AddItemToCharacter(u16 CharID, u16 ItemID);
/*
    `AddItemToConvoy` - Adds `Item` to Convoy, if convoy is full and item has special flag then first non story important item shall be purged from convoy data.
    \param `ItemID` ItemID
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void AddItemToConvoy(u16 ItemID);
/*
    `ChangeBattleMusic` - Changes Battle music the the `TrackID` provided to function after amount of `Ticks` set passed
    \param `TrackID` TrackID
    \param `Ticks` Ticks in Ms before music track changes
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void ChangeBattleMusic(u16 TrackID, u32 Ticks);
/*
    `ChangeMapMusic` - Changes Map music the the `TrackID` provided to function after amount of `Ticks` set passed
    \param `TrackID` TrackID
    \param `Ticks` Ticks in Ms before music track changes
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void ChangeMapMusic(u16 TrackID, u32 Ticks);
/*
    `RoutCharacter` - Removes character from map without killing the character
    \param `CharID` Character ID
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void RoutCharacter(u16 CharID);
/*
    `KillCharacter` - Kills character and removes them from map
    \param `CharID` Character ID
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void KillCharacter(u16 CharID);
/*
    `SpawnUnit` - Spawns Character of `CharID` with `Faction` `Skills` and `Inventory` on the map,
    \param `CharID` Character ID
    \param `Faction` Faction to spawn Character In, Can use `CharacterFaction` Enum to pass on the value
    - 0 - Player Faction
    - 1 - Enemy Faction
    - 2 - Ally (NPC) Faction
    - 3 - 2nd Enemy Faction (for cases where Many factions fight against you and each other)
    - 4 - 3rd Enemy Faction (see above)
    \param `AiData` - Bitfield Values for ai - TODO ME
    \param `Inventory` - character inventory - stores IDs of items
    \param `Skills` - character skills - stores IDs of skills    
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void SpawnUnit(u16 CharID, u8 Faction, struct AiData Ai, u16 Inventory[0x5], u16 Skills[0x5]);
/*
    `MoveUnit` - moves character on map
    \param `CharID` Character ID
    \param `IgnoreTerrain` Make Character ignore terrain
    \param `IgnoreUnit` Make Character ignore terrain
    \param `MoveDespiteRoutDeath` Make Character Appear and move despite being Dead
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void MoveUnit(u16 CharID, bool IgnoreTerrain, bool IgnoreUnit, bool MoveDespiteRoutDeath );
/*
    `SpawnDialogue`- Spawns dialogue box of selected type

    \param `DialogueEntry` yaml entry string
    \param `DialogueType` textbox type
    Can use Enum values from `DialogueType`
    - 0 - normal dialogue, black text, white background
    - 1 - fullscreen dialogue scene (requires usage of SpawnCGImage before calling Spawn Dialogue), black text, white frame
    - 2 - black background, white text no frame
    - 3 - black background, black text, white frame
    - 4 - normal dialogue, allows color change of text, white frame
    - 5 - normal dialogue, allows color change of frame, black text
    - 6 - normal dialogue, allows color change of both text and frame
    - 7 - fullscreen dialogue scene (requires usage of SpawnCGImage before calling Spawn Dialogue), allows color change of text, white frame
    - 8 - fullscreen dialogue scene (requires usage of SpawnCGImage before calling Spawn Dialogue), black text, allows color change of frame
    - 9 - fullscreen dialogue scene (requires usage of SpawnCGImage before calling Spawn Dialogue), allows color change of both text and frame   
    \param `DeadSpeak` Killed characters will speak their lines in dialogue even if dead if set to `true`
    \param `BoxPosition` placement of textbox
    Can use Enum values from `TextBoxPosition`
    - 0 - Mid
    - 1 - Left
    - 2 - Left Left
    - 3 - Left Left Left
    - 4 - Up
    - 5 - Left Up
    - 6 - Right Up
    - 7 - Right
    - 8 - Right Right
    - 9 - Right Right Right 
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine       
*/
void SpawnDialogue(char* DialogueEntry, u8 DialogueType, bool DeadSpeak, u8 BoxPosition);
/*
    `SpawnCGImage` - Spawns full screen Cutscene Image, must be used in conjuction with `SpawnDialogue` with certain `DialogueType` (look above)
    \param `ImageID` ID of the image to spawn
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine    
*/
void SpawnCGImage(u16 ImageID);
/*
    `Chapter` - Function storing important values for current chapter
    \param `ChapterID` ChapterID (aka its number)
    \param `WinType` What kind of conditions are there to successfully finish chapter
    \param `ChapterMultiMap` - does chapter uses multiple maps? `true` if yes `false` if not
*/
void Chapter(u16 ChapterID, u8 WinType, bool ChapterMultiMap);
/*
    `GameOver` - end the game
    \param None
    \returns None
    \since This Function is available since version 0.1 of Aurus Engine
*/
void GameOver();
/*
    `EndChapter` - sucessfully finish currently played chapter
    \param None
    \returns None    
    \since This Function is available since version 0.1 of Aurus Engine
*/
void EndChapter();
/*
    MapEvent
    \param `MapEvent` Spawn an Map event of selected Type at selected coordinated
    \param `EventType` Type of event
    Can use Enum values from `EventType`
    - 0 - Village
    - 1 - Fort
    - 2 - Castle
    - 3 - Temple
    - 4 - Shop (requires usage of `Shop` before calling `MapEvent`)
    \returns None    
    \since This Function is available since version 0.1 of Aurus Engine
*/
void MapEvent(u8 EventType, u8 MapX, u8 MapY);


