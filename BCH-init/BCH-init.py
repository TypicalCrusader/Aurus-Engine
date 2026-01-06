# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

import zlib
import os
import csv

def main():
    filenamelist = ["item","class","character"]
    csv_data = ["Character_data","Class_data"]

    x = 0
    y = 0

    while x <= len(filenamelist):
        if os.path.exists("./build/"+filenamelist[x]+".bch","r") == True:
            bch = open("./build/"+filenamelist[x]+".bch","a")
            bch_crc = bch.readline()
            bch_crc = bch_crc.split("- ")
        else:
            bch = open("./build/"+filenamelist[x]+".bch","a")
            bch_crc = 0
        f = open("Aurus-Engine/include"+filenamelist[x]+".h","r")
        if zlib.crc32(f,len(f)) == bch_crc :
            print("[PY] " + filenamelist +".h HAS SAME CRC32 CHECKSUM AS BCH FILE. SKIPPING IT")
            bch.close()
            f.close()
            x += 1
        else:
            bch_crc = zlib.crc32(f,len(f))
            bch.write(filenamelist[x] + ".h - " + bch_crc) 
            with open("Aurus-Engine/include"+filenamelist[x]+".h","r") as f:
                for line in f:
                    if 'enum' in line:
                        break

                for line in f:
                    if '}' in line:
                        f.close()
                        print("[PY] "+filenamelist[x]+".bch CREATED")
                        x += x
                        break
                    else:
                        y += 1
                        if '=' in line:
                           bch.write(line.strip()) #write enum value  
                        else:
                            bch.write(line.strip()+" = "+y) #write enum value 
    
    x = 0

    while x <= len(csv_data):
        if os.path.exists("./build/"+csv_data[x]+".bch","r") == True:
            bch = open("./build/"+csv_data[x]+".bch","a")
            bch_crc = bch.readline()
            bch_crc = bch_crc.split("- ")
        else:
            bch = open("./build/"+csv_data[x]+".bch","a")
            bch_crc = 0
        f = open("./Aurus-Engine/data/tabledata/"+csv_data[x]+".h","r")
        if zlib.crc32(f,len(f)) == bch_crc :
            bch.close()
            f.close()
            x += x        
        else:
            f.close()
<<<<<<< Updated upstream
            bch.write(csv_data[x]+".csv"+" - "+zlib.crc32(f,len(f))) 
=======
            bch.write(csv_data[x]+".bch"+" - "+zlib.crc32(f,len(f))) 
            h = open("./Aurus-Engine/include/generated"+csv_data[x]+".h","a")
            h.write("enum "+csv_data[x]+"{\n")
>>>>>>> Stashed changes
            with open("./Aurus-Engine/data/tabledata/"+csv_data[x]+".csv", 'r', newline='unix') as f:
                reader = csv.reader(f, delimiter=";")
                g = 0
                for i in reader:
                    h.write(i[0]+",\n")
                    bch.write(i[0]+"\n")
                    f.close()
                h.write("}\n")
                h.close()


if __name__ == "__main__":
    main()