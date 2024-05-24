LOOP:       LODD count:     ; Load the number of the remaining data elements to process
            JZER DONE:      ; If count == 0 then end the program
            SUBD c1:        ; [Assignment] ac -= 1
            STOD count:     ; [Assignment] count -= 1
P1:         LODD daddr:     ; Load the pointer of a fib argument d[n]
            PSHI            ; Push the argument to the stack
            ADDD c1:        ; [Assignment] ac += 1
            STOD daddr:     ; [Assignment] daddr += 1
            CALL FIB:       ; Call the fib function
            INSP 1          ; Clear the stack
P2:         PUSH            ; Put the return value in the accumulator to the stack
            LODD faddr:     ; Load the pointer of f[n]
            POPI            ; Pop the result to f[n]
            ADDD c1:        ; [Assignment] ac += 1
            STOD faddr:     ; [Assignment] faddr += 1
            JUMP LOOP:      ; Go back to the beginning of the loop
FIB:        LODL 1          ; Load the argument n to the accumulator
            JZER FIBZER:    ; If n == 0 goto FIBZER
            SUBD c1:        ; Decrement the value in the accumulator by 1
            JZER FIBONE:    ; If (n - 1) == 0 goto FIBONE
            PUSH            ; Push (n - 1) to the stack
            CALL FIB:       ; Call the fib function (recursion) to calculate fib(n - 1)
            PUSH            ; Push the return value, fib(n - 1), to the stack
            LODL 1          ; Load (n - 1) back to the accumulator
            SUBD c1:        ; ac = n - 2
            PUSH            ; Push (n - 2) to the stack
            CALL FIB:       ; Call the fib function (recurssion) to calculate fib(n - 2)
            ADDL 1          ; ac += fib(n - 1), where ac = fib(n - 2)
            INSP 3          ; Clear the stack
            RETN            ; Return
FIBZER:     LODD c0:        ; Load 0 to the accumulator; f(0) = 0
	        RETN			; Return
FIBONE:	    LODD c1:        ; Load 1 to the accumulator; f(1) = 1
	        RETN			; Return
DONE:	    HALT            ; Halt
.LOC 	    100			    ; Locate data beginning at 100
c0: 	    0			    ; [100] 0 (constant)
c1: 	    1               ; [101] 1 (constant)
d0:  	    3			    ; [102] Array of args for the fib function
     	    9               ; [103]
     	    0               ; [104]
     	    0               ; [105]
     	    0               ; [106]
f0:  	    0			    ; [107] Array of result locations for fib results
     	    0               ; [108]
     	    0               ; [109]
     	    0               ; [110]
     	    0               ; [111]
daddr:      d0:			    ; [112] Start address of fib args
faddr:      f0:			    ; [113] Start address of fib results
count:      1			    ; [114] The number of the remaining data elements to process