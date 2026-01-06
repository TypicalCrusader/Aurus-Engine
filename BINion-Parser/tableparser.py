# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

import csv
import os
import glob
import pandas
import struct

table_files = [glob.glob("Aurus-Engine/data/tabledata*.csv")]

character_table_list_to_be_replaced = [
    "CharacterIndex",
    "CharacterName",
    "CharacterDesc",
    "CharacterClass",
    "CharacterPortraitID",
    "MapSprite",
    "BaseCharacterSkills",
    "Race",
    "StartingSword",
    "StartingPole",
    "StartingAxe",
    "StartingRanged",
    "StartingMAGEFire",
    "StartingMAGEIce",
    "StartingMAGEThunder",
    "StartingMAGEWind",
    "StartingMAGEDawn",
    "StartingMAGEDusk",
    "StartingMAGEDragon",
    "StartingMAGEMonster",
    "StartingStave"    
]
character_table_dict_replace_val = {
    "CharacterIndex":[],
    "CharacterName":[],
    "CharacterDesc":[],
    "CharacterClass":[],
    "CharacterPortraitID":[],
    "MapSprite":[],
    "BaseCharacterSkills":[],
    "Race":[],
    "StartingSword":[],
    "StartingPole":[],
    "StartingAxe":[],
    "StartingRanged":[],
    "StartingMAGEFire":[],
    "StartingMAGEIce":[],
    "StartingMAGEThunder":[],
    "StartingMAGEWind":[],
    "StartingMAGEDawn":[],
    "StartingMAGEDusk":[],
    "StartingMAGEDragon":[],
    "StartingMAGEMonster":[],
    "StartingStave":[]
}

def character_table_parser():
    table_to_save = []

    with os.open("./Aurus-Engine/build/data_cache/character.bch") as f:
        print("[PY]     Building Master dict from character.bch")
        for line in f:
            if 'CHARACTER_' in line:
                character_table_dict_replace_val["CharacterIndex"] = int(line.strip("= ")) #based on table
            if 'PORTRAIT_' in line: 
                character_table_dict_replace_val["CharacterPortraitID"] = int(line.strip("= ")) #based on table
            if 'SPRITE_' in line:
                character_table_dict_replace_val["MapSprite"] = int(line.strip("= ")) #based on table            
            if 'RACE_' in line:
                character_table_dict_replace_val["Race"] = int(line.strip("= ")) #based on table
            if 'WPN_' in line:
                character_table_dict_replace_val["StartingSword"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingPole"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingAxe"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingRanged"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEFire"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEIce"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEThunder"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEWind"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEDawn"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEDusk"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEDragon"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingMAGEMonster"] = int(line.strip("= "))
                character_table_dict_replace_val["StartingStave"] = int(line.strip("= "))
        f.close()
    
    with os.open("./Aurus-Engine/build/data_cache/master_text.bch") as f:
        print("[PY]     Building Master dict from master_text.bch")
        for line in f:
            if 'NAME_' in line:
                character_table_dict_replace_val["CharacterName"] = int(line.strip("= "))
            if 'DESC_' in line:
                character_table_dict_replace_val["CharacterDesc"] = int(line.strip("= "))
            if 'DIALOGUE_' in line:
                break        
        f.close()

    with os.open("./Aurus-Engine/build/data_cache/class.bch") as f:
        print("[PY]     Building Master dict from class.bch")
        for line in f:
            if 'CLASS_' in line:
                character_table_dict_replace_val["CharacterClass"] = int(line.strip("= ")) #based on class  
        f.close()    
            
    with os.open("./Aurus-Engine/build/data_cache/skill.bch") as f:
        print("[PY]     Building Master dict from skill.bch")
        for line in f:
            if 'SKILL_' in line:
                character_table_dict_replace_val["BaseCharacterSkills"] = int(line.strip("= ")) #based on skill  
        f.close()    

    with pandas.read_csv("./Aurus-Engine/data/tabledata/Character_data.csv",sep=";") as t:
        t.pandas.replace(to_replace=character_table_list_to_be_replaced,value=character_table_dict_replace_val)
        t.pandas.replace({'true': 1, 'false': 0})
        parsed_table = {} 
        t.pandas.to_dict(orient="records",into=parsed_table) #[{col1:val, col2:val},{col1:val, col2:val}]

        i = 0

        while i < len(parsed_table):
            table_to_save = struct.pack('>HQQHL5Hb?b23c13b', parsed_table[p]["CharacterIndex"], parsed_table[p]["CharacterName"], parsed_table[p]["CharacterDesc"], parsed_table[p]["CharacterClass"], parsed_table[p]["CharacterPortraitID"], parsed_table[p]["MapSprite"], parsed_table[p]["BaseCharacterSkills"], parsed_table[p]["Race"], parsed_table[p]["UseCombinedGrowths"], parsed_table[p]["StartHP"], parsed_table[p]["StartingStr"], parsed_table[p]["StartingMag"], parsed_table[p]["StartingAgi"], parsed_table[p]["StartingSpd"], parsed_table[p]["StartingPdef"], parsed_table[p]["StartingMdef"], parsed_table[p]["StartingMana"], parsed_table[p]["StartingChr"], parsed_table[p]["StartingLck"], parsed_table[p]["StartingEnd"], parsed_table[p]["StartingMov"], parsed_table[p]["HPGrowth"], parsed_table[p]["StrGrowth"], parsed_table[p]["MagGrowth"], parsed_table[p]["AgiGrowth"], parsed_table[p]["SpdGrowth"], parsed_table[p]["PDefGrowth"], parsed_table[p]["MDefGrowth"], parsed_table[p]["ManaGrowth"], parsed_table[p]["ChrGrowth"], parsed_table[p]["LckGrowth"], parsed_table[p]["EndGrowth"], parsed_table[p]["MovGrowth"], parsed_table[p]["StartingSword"], parsed_table[p]["StartingPole"], parsed_table[p]["StartingAxe"], parsed_table[p]["StartingRanged"], parsed_table[p]["StartingMAGEFire"], parsed_table[p]["StartingMAGEIce"], parsed_table[p]["StartingMAGEThunder"], parsed_table[p]["StartingMAGEWind"], parsed_table[p]["StartingMAGEDawn"], parsed_table[p]["StartingMAGEDusk"], parsed_table[p]["StartingMAGEDragon"], parsed_table[p]["StartingMAGEMonster"], parsed_table[p]["StartingStave"])

            with os.open("./Aurus-Engine/build/temp_data/Character.bin",mode="ab") as f:
                print("[PY]     Writing Character-Table temp bin")
                f.write(table_to_save)
                f.close()            
                i += 1
            
            """
            x 	pad byte 	no value 	  	 
            c 	char 	bytes of length 1 	1 	 
            b 	signed char 	integer 	1 	(1),(3)
            B 	unsigned char 	integer 	1 	(3)
            ? 	_Bool 	bool 	1 	(1)
            h 	short 	integer 	2 	(3)
            H 	unsigned short 	integer 	2 	(3)
            i 	int 	integer 	4 	(3)
            I 	unsigned int 	integer 	4 	(3)
            l 	long 	integer 	4 	(3)
            L 	unsigned long 	integer 	4 	(3)
            q 	long long 	integer 	8 	(2), (3)
            Q 	unsigned long long 	integer 	8 	(2), (3)
            n 	ssize_t 	integer 	  	(4)
            N 	size_t 	integer 	  	(4)
            f 	float 	float 	4 	(5)
            d 	double 	float 	8 	(5)
            s 	char[] 	bytes 	  	 
            p 	char[] 	bytes 	  	 
            P 	void * 	integer 	  	(6)            
            """

