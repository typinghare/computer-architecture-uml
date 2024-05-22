
FIBZER0:	LODD c0:        ; Load 0 to ac
	        RETN			; Return
FIBONE:	    LODD c1:        ; Load 1 to ac
	        RETN			; Return
DONE:	    HALT
.LOC 	    100			; Locate data beginning at 100
c0: 	    0			; 0 (constant)
c1: 	    1           ; 1 (constant)
d0:  	    3			; Array of args for the fib function
     	    9
     	    18
     	    23
     	    25
f0:  	    0			; Array of result locations for fib results
     	    0
     	    0
     	    0
     	    0
daddr:      d0:			; Start address of fib args
faddr:      f0:			; Start address of fib results
pasCnt:     5			; The number of data elements to process