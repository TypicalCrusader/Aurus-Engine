#!/usr/bin/env bash
#SPDX-FileCopyrightText: 2026 =NONE

#SPDX-License-Identifier: CC0-1.0
# generate_compile_commands.sh, BECAUSE ON MY FUCKING WINDOWS NOTHING ELSE WORKS??

echo "[" > compile_commands.json

first=1
for src in $(find . -name "*.c"); do
    dir=$(dirname "$src")
    obj="${src%.c}.o"
    if [ $first -eq 1 ]; then
        first=0
    else
        echo "," >> compile_commands.json
    fi
    cat <<EOF >> compile_commands.json
{
  "directory": "$(pwd)/$dir",
  "command": "gcc -std=gnu23 -Iinclude -c $src -o $obj",
  "file": "$src"
}
EOF
done

echo "]" >> compile_commands.json