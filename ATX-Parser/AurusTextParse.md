<!--
SPDX-FileCopyrightText: 2026 =NONE

SPDX-License-Identifier: CC0-1.0
-->

- uses Private area use UTF-8 characters for command codes
- supports ALL utf-8 characters
- JSON -> parsed entry -> BINion maker -> binion
- +/- 50 normal latin characters per line excluding control codes


!!!!!!! NEEED TO USE UTF-32 INSTEAD OF UTF-8 AS UTF-32 CHARACTERS ARE ALL 32 BIT WIDTH SIZE !!!!!!!!!!!!!!!!!!

# Command codes
```
    #textc #0-20, - changes text color - shorthand #tc #0-20
    used codes
        - 0xee 0x80 0x80 - White
        - 0xee 0x80 0x81 - Black
        - 0xee 0x80 0x82 - Red
        - 0xee 0x80 0x83 - Dark Red
        - 0xee 0x80 0x84 - Blue
        - 0xee 0x80 0x85 - Dark Blue
        - 0xee 0x80 0x86 - Green
        - 0xee 0x80 0x87 - Dark Green
        - 0xee 0x80 0x88 - Purple
        - 0xee 0x80 0x89 - Yellow
        - 0xee 0x80 0x8A - Orange
        - 0xee 0x80 0x8B - Pink
        - 0xee 0x80 0x8C - Grey
        - 0xee 0x80 0x8D - Unused
        - 0xee 0x80 0x8E - Unused
        - 0xee 0x80 0x8F - Unused
        - 0xee 0x80 0x90 - Unused
        - 0xee 0x80 0x91 - Unused
        - 0xee 0x80 0x92 - Unused
        - 0xee 0x80 0x93 - Unused
        - 0xee 0x80 0x94 - Unused

    #textbgc #0-5, shorthand - #tbg #0-5
        - 0xee 0x80 0x95 - Standard
        - 0xee 0x80 0x96 - Black
        - 0xee 0x80 0x97 - Unused
        - 0xee 0x80 0x98 - Unused
        - 0xee 0x80 0x99 - Unused 

    #display_r_far_far - display portrait at far far right position, shorthand - #d_r_ff
        - 0xee 0x80 0x9A

    #display_r_far - display portrait at far right position, shorthand - #d_r_f
        - 0xee 0x80 0x9B

    #display_r - display portrait at right position, shorthand - #d_r
        - 0xee 0x80 0x9C    

    #display_mid - display portrait at middle position, shorthand - #d_m
        - 0xee 0x80 0x9D

    #display_l - display portrait at left position, shorthand - #d_l
        - 0xee 0x80 0x9E

    #display_l_far - display portrait at far left position, shorthand - #d_l_f
        - 0xee 0x80 0x9F

    #display_l_far_far - display portrait at far far left position, shorthand - #d_l_ff
        - 0xee 0x80 0xA0

    #display_name_r_far_far, shorthand - #nrff
        - 0xee 0x80 0xA1

    #display_name_r_far, shorthand - #nrf
        - 0xee 0x80 0xA2

    #display_name_r, shorthand - #nr
        - 0xee 0x80 0xA2

    #display_name_mid, shorthand - #nm 
        - 0xee 0x80 0xA3

    #display_name_l, shorthand - #nl 
        - 0xee 0x80 0xA4

    #display_name_l_far, shorthand - #dlf
        - 0xee 0x80 0xA5

    #display_name_l_far_far, shorthand - #dlff   
        - 0xee 0x80 0xA6

    \n 
        - 0x0A 
        
    \t 
        - 0x09

    #wait_until_press, shorthand - #a
        - 0x06

    #bold, shorthand - #b
        - 0xEE 0x87 0x31    

    #narrow_text, shorthand - #nrrw
        - 0xEE 0x87 0x31 

    #normal_text, shorthand - #ntxt
        - 0xEE 0x87 0x32

    #big_text, shorthand - #btxt
        - 0xEE 0x87 0x33

    #huge_text, shorthand - #htxt
        - 0xEE 0x87 0x34

    #set_active_character #rff,rf,r,m,l,lf,lff - sets active character slot, shorthand - #achr #rff,rf,r,m,l,lf,lff
        - 0xEE 0x87 0x35 - rff
        - 0xEE 0x87 0x36 - rf
        - 0xEE 0x87 0x37 - r
        - 0xEE 0x87 0x38 - m
        - 0xEE 0x87 0x39 - l
        - 0xEE 0x87 0x3A - lf
        - 0xEE 0x87 0x3B - lff

    #switch_character #0-3 - changes the character portrait + name at active slot to selected one, shorthand - #schr #0-3
        - 0xEE 0x87 0x3c - 0
        - 0xEE 0x87 0x3d - 1
        - 0xEE 0x87 0x3e - 2    
        - 0xEE 0x87 0x3e - 3          

    #cursive, shorthand - #c
        - 0xee 0x80 0xA7

    #small, shorthand - #stxt 
        - 0xee 0x80 0xA8

    #display_gold_symbol, shorthand - #dgld
        - 0xee 0x80 0xA9

    #display_gold_val, shorthand - #gldv
        - 0xee 0x80 0xAA

    #dotdot, shorthand - #..
        - 0xee 0x80 0xAB

    #dotdotdot, shorthand - #...
        - 0xee 0x80 0xAC

    #blink, shorthand - #blnk
        - 0xee 0x80 0xAD

    #wait #0-14, shorthand - #w #0-14
        - 0xee 0x80 0xAE -- 0xee 0x80 0xBC

    #mid_text_event, shorthand - #mtev
        - 0xee 0x80 0xBD

    #display_glob_val #0-32, shorthand - #glob #0-32
        - 0xee 0x80 0xBE -- 0xee 0x80 0xDE

    #display_local_val #0-16, shorthand - #locl #0-16
        - 0xee 0x80 0xDF -- 0xee 0x80 0xEF

    #DEBUG_display_flag_val #0-1600
        - 0xee 0x80 0xF0 -- 0xEE 0x87 0x30


