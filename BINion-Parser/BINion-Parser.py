# SPDX-FileCopyrightText: 2024-Present =TypicalCrusader <typicalcrusader@noreply.codeberg.org>
#
# SPDX-License-Identifier: GPL-2.0-only

import tableparser as table
from multiprocessing import Process

def main():
    c = Process(target=table.character_table_parser, args=())
    c.start()
    c.join()

if __name__ == "__main__":
    main()