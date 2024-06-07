start:      LODD d1:    ;
	        RSHIFT 0    ;
	        HALT        ; ac = 3451
	        LODD d2:    ;
            RSHIFT 3    ;
            HALT        ; ac = 1024
            LODD d3:    ;
            RSHIFT 7    ;
            HALT        ; ac = 448
            LODD d4:    ;
            RSHIFT 15   ;
            HALT        ; ac = 1
            LODD d5:    ;
            RSHIFT 4    ;
            HALT        ; ac = 59
.LOC 20
d1:         3451
d2:         8192
d3:         -8192
d4:         -32768
d5:         944