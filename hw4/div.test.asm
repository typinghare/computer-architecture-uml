start:      LODD div1:  ;
            PUSH        ;
            LODD dnd1:  ;
            PUSH        ;
            DIV         ; 1. ac = 0, [4943, 0] (4943 = -5152 * 0 + 4943)
            HALT        ; [-5152, 4943, 4943, 0]
            LODD div2:  ;
            PUSH        ;
            LODD dnd2:  ;
            PUSH        ;
            DIV         ; 2. ac = -1, [-1, 0] (illegal)
            HALT        ; [0, 437, -1, 0]
            LODD div3:  ;
            PUSH        ;
            LODD dnd3:  ;
            PUSH        ;
            DIV         ; 3. ac = 0, [9, 513] (-8199 = -16 * 513 + 9)
            HALT        ; [-16, -8199, 9, 513]
            LODD div4:  ;
            PUSH        ;
            LODD dnd4:  ;
            PUSH        ;
            DIV         ; 4. ac = 0, [255, -95] (24575 = -256 * -95 + 255)
            HALT        ; [-256, 24575, 255, -95]
            LODD div5:  ;
            PUSH        ;
            LODD dnd5:  ;
            PUSH        ;
            DIV         ; 5. ac = 0, [0, 0] (0 = 511 * 0 + 0)
            HALT        ; [511, 0, 0, 0]
            LODD div6:  ;
            PUSH        ;
            LODD dnd6:  ;
            PUSH        ;
            DIV         ; 6. ac = 0, [14, 481] (8191 = 17 * 481 + 14)
            HALT        ; [17, 8191, 14, 481]
.LOC 40
div1:       -5152
dnd1:       4943
div2:       0
dnd2:       437
div3:       -16
dnd3:       -8199
div4:       -256
dnd4:       24575
div5:       511
dnd5:       0
div6:       17
dnd6:       8191
