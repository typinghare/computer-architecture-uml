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
FIB:        LODD memoaddr:  ; Load the address of the memo array
            ADDL 1          ; Caculate the address of memo[n]
            PSHI            ; Push memo[n] to the stack
            POP             ; Pop memo[n] to the accumulator
            ADDD c1         ; Increment the value in the accumulator by 1
            JZER FIBCALC:   ; If memo[n] == -1, the value has yet been calculated
            SUBD c1         ; Decrement the value in the accumulator by 1
            RETN            ; Return
FIBCALC:    LODL 1          ; Load the argument n to the accumulator
            SUBD c1:        ; Decrement the value in the accumulator by 1
            PUSH            ; Push (n - 1) to the stack
            CALL FIB:       ; Call the fib function (recursion) to calculate fib(n - 1)
            PUSH            ; Push the return value, fib(n - 1), to the stack
            LODL 1          ; Load (n - 1) back to the accumulator
            SUBD c1:        ; ac = n - 2
            PUSH            ; Push (n - 2) to the stack
            CALL FIB:       ; Call the fib function (recurssion) to calculate fib(n - 2)
            ADDL 1          ; ac += fib(n - 1), where ac = fib(n - 2)
            INSP 3          ; Clear the stack
            PUSH            ; Push fib(n) to the stack
            LODD memoaddr:  ; Load the address of the memo array
            ADDL 2          ; Caculate the address of memo[n]
            POPI            ; Save fib(n) to &memo[n] => memo[n] = fib(n)
            PSHI            ; Push memo[n] to the stack again
            POP             ; Pop memo[n] and save the value to the accumulator
            RETN            ; Return
FIBZER:     LODD c0:        ; Load 0 to the accumulator => fib(0) = 0
            RETN            ; Return
FIBONE:     LODD c1:        ; Load 1 to the accumulator => fib(1) = 1
            RETN            ; Return
DONE:       HALT            ; Halt
.LOC        100             ; Locate data beginning at 100
d0:         3               ; [102] Array of args for the fib function
            9               ; [103]
            18              ; [104]
            23              ; [105]
            25              ; [106]
f0:         0               ; [107] Array of result locations for fib results
            0               ; [108]
            0               ; [109]
            0               ; [110]
            0               ; [111]
c0:         0               ; [100] 0 (constant)
c1:         1               ; [101] 1 (constant)
daddr:      d0:             ; [112] Start address of fib args
faddr:      f0:             ; [113] Start address of fib results
count:      5               ; [114] The number of the remaining data elements to process
memo:       0               ; [115] memo[0] The memo array to store fib(n), where 0 <= n <= 25
            1               ; [116] memo[1]
            -1              ; [117] memo[2]
            -1              ; [118] memo[3]
            -1              ; [119] memo[4]
            -1              ; [120] memo[5]
            -1              ; [121] memo[6]
            -1              ; [122] memo[7]
            -1              ; [123] memo[8]
            -1              ; [124] memo[9]
            -1              ; [125] memo[10]
            -1              ; [126] memo[11]
            -1              ; [127] memo[12]
            -1              ; [128] memo[13]
            -1              ; [129] memo[14]
            -1              ; [130] memo[15]
            -1              ; [131] memo[16]
            -1              ; [132] memo[17]
            -1              ; [133] memo[18]
            -1              ; [134] memo[19]
            -1              ; [135] memo[20]
            -1              ; [136] memo[21]
            -1              ; [137] memo[22]
            -1              ; [138] memo[23]
            -1              ; [139] memo[24]
            -1              ; [140] memo[25]
memoaddr:   memo:           ; The address of the memo array