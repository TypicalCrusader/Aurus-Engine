<!--
SPDX-FileCopyrightText: 2026 =NONE

SPDX-License-Identifier: CC0-1.0
-->

- uses Private area use UTF characters for command codes
- JSON ENTRY -> parsed SCSU compressed .atx entry -> BINion maker -> binion
- +/- 50 normal latin characters per line excluding control codes


uses utf 32 characters

Private Use Area
E000-F8FF -> 0000E000 - 0000F8FF
Supplementary Private Use Area-A
F0000-FFFFF -> 000F0000 - 000FFFFF
Supplementary Private Use Area-B
100000-10FFFD -> 00100000 - 0010FFFD

# Command codes
```
    #textc #0-20, - changes text color - shorthand #tc #0-20
    goes from 0000E000 - 0000E014
    used codes
        - 0000E000 - White
        - 0000E001 - Black
        - 0000E002 - Red
        - 0000E003 - Dark Red
        - 0000E004 - Blue
        - 0000E005 - Dark Blue
        - 0000E006 - Green
        - 0000E007 - Dark Green
        - 0000E008 - Purple
        - 0000E009 - Yellow
        - 0000E00A - Orange
        - 0000E00B - Pink
        - 0000E00C - Grey
        - 0000E00D - Unused
        - 0000E00E - Unused
        - 0000E00F - Unused
        - 0000E010 - Unused
        - 0000E011 - Unused
        - 0000E012 - Unused
        - 0000E013 - Unused
        - 0000E014 - Unused

    #textbgc #0-5, shorthand - #tbg #0-5
    0000E015 - 0000E019
        - 0000E015 - Standard
        - 0000E016 - Black
        - 0000E017 - Unused
        - 0000E018 - Unused
        - 0000E019 - Unused 

    #display_r_far_far - display portrait at far far right position, shorthand - #d_r_ff
        - 0000E01A

    #display_r_far - display portrait at far right position, shorthand - #d_r_f
        - 0000E01B

    #display_r - display portrait at right position, shorthand - #d_r
        - 0000E01C    

    #display_mid - display portrait at middle position, shorthand - #d_m
        - 0000E01D

    #display_l - display portrait at left position, shorthand - #d_l
        - 000E01DE

    #display_l_far - display portrait at far left position, shorthand - #d_l_f
        - 0000E01F

    #display_l_far_far - display portrait at far far left position, shorthand - #d_l_ff
        - 0000E020

    #display_name_r_far_far, shorthand - #nrff
        - 0000E021

    #display_name_r_far, shorthand - #nrf
        - 0000E022

    #display_name_r, shorthand - #nr
        - 0000E023

    #display_name_mid, shorthand - #nm 
        - 0000E024

    #display_name_l, shorthand - #nl 
        - 0000E025

    #display_name_l_far, shorthand - #dlf
        - 0000E026

    #display_name_l_far_far, shorthand - #dlff   
        - 0000E027

    \n 
        - 0000000A 
        
    \t 
        - 00000009

    #wait_until_press, shorthand - #a
        - 00000006

    #bold, shorthand - #b
        - 0000E028

    #narrow_text, shorthand - #nrrw
        - 0000E029 

    #normal_text, shorthand - #ntxt
        - 0000E02A

    #big_text, shorthand - #btxt
        - 0000E02B

    #huge_text, shorthand - #htxt
        - 0000E02C

    #set_active_character #rff,rf,r,m,l,lf,lff - sets active character slot, shorthand - #achr #rff,rf,r,m,l,lf,lff
    0000E02D - 0000E033
        - 0000E02D - rff
        - 0000E02E - rf
        - 0000E02F - r
        - 0000E030 - m
        - 0000E031 - l
        - 0000E032 - lf
        - 0000E033 - lff

    #switch_character #0-3 - changes the character portrait + name at active slot to selected one, shorthand - #schr #0-3
    0000E034 - 0000E037
        - 0000E034 - 0
        - 0000E035 - 1
        - 0000E036 - 2    
        - 0000E037 - 3          

    #cursive, shorthand - #c
        - 0000E038

    #small, shorthand - #stxt 
        - 0000E039

    #display_gold_symbol, shorthand - #dgld
        - 0000E03A

    #display_gold_val, shorthand - #gldv
        - 0000E03B

    #dotdot, shorthand - #..
        - 0000E03C

    #dotdotdot, shorthand - #...
        - 0000E03D

    #blink, shorthand - #blnk
        - 0000E03E

    #wait #0-14, shorthand - #w #0-14
        - 0000E03F - 0000E04D

    #mid_text_event, shorthand - #mtev
        - 0000E04E

    #display_glob_val #0-32, shorthand - #glob #0-32
        - 0000E04F - 0000E06F

    #display_local_val #0-16, shorthand - #locl #0-16
        - 0000E070 - 0000E080


