start:      LODD d1:    ;
	        PUSH        ;
            MULT 0      ;
            HALT	    ; 1. ac = 0, m[sp] = 0
            LODD d2:    ;
            PUSH        ;
            MULT 37     ;
            HALT        ; 2. ac = 0, m[sp] = -13394
            LODD d3:    ;
            PUSH        ;
            MULT 63     ;
            HALT        ; 3. ac = 0, m[sp] = 32760
            LODD d4:    ;
            PUSH        ;
            MULT 16     ;
            HALT        ; 4. ac = 0, m[sp] = -32768
            LODD d5:    ;
            PUSH        ;
            MULT 49     ;
            HALT        ; 5. ac = 1, m[sp] = 715 (not -30501)
            LODD d6:    ;
            PUSH        ;
            MULT 55     ;
            HALT        ; 6. ac = 0, m[sp] = -55
.LOC 30
d1:	        2542
d2:	        -362
d3:	        520
d4:	        -2048
d5:	        715
d6:	        -1

