/*
 * SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "event.h"

//test event

CHAPTER_VICTORY_CONDITIONS Ch1VictoryConditions [] = {
    cKillAll
};

CHAPTER_TURN_EVENT_LIST Ch1TurnEventList [] = {

};

CHAPTER_EVENT_LIST Ch1MapEventsList [] = {
    cPlaceEvent(0,1,NULL,2)
};

CHAPTER_CONDITIONAL_EVENT_LIST Ch1ConditionalEventsList [] = {
    cTriggerEventIfXDead(1,1,NULL)
};

CHAPTER_MAP_WEAPON_AND_DESTROYABLES_LIST Ch1MapWeaponsAndDestroyablesList [] = {
    cDoor(1,2)
};

CHAPTER_TRAP_LIST Ch1Trap [] = {
    cTrapWolfTrap(1,0)
};

UNITDEF TestChptUnit [] = {
    cUnitDef(1,1,1,false,0,0,0,0,0,0,0,1,0)
};

void amongus() {
    return;
}

void Ch1MainEvent() {
    //vSpawnUnit(*TestChptUnit);
    vSetFlag(1,true);
    if(uCheckFlag(1)==1)
    {
        cTriggerEvent(amongus);
    }
    //vSilentPromote(1,1);
    //vFlashScreen(1,10);
    //vChapterVictory();
    //vGOTOChapterChangePath(1);
    return;
}

const struct gpChapterEventStruct Ch1Events = {
    .gVictoryConditions = Ch1VictoryConditions,
    .gTurnEventsList = Ch1TurnEventList,
    .gMapEventsList = Ch1MapEventsList,
    .gConditionalEventsList = Ch1ConditionalEventsList,
    .gTrapList = Ch1Trap,
    .gMapWeaponsAndDestroyablesList = Ch1MapWeaponsAndDestroyablesList,
    .gMainEvent = Ch1MainEvent, 
};