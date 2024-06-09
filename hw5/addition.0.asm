Start:      LODD on:        ;
            STOD 4095       ;
            CALL BusyWrite: ;
            LOCO prompt:    ;
NextWord:   PSHI            ;
            ADDD c1:        ;
            STOD pstr1:     ;
            POP             ;
            JZER crnl:      ;
            STOD 4094       ;
            PUSH            ;
            SUBD c255:      ; Most sig 8 bits are zero
            JNEG icrnl:     ;
            CALL sb:        ;
            INSP 1          ;
            PUSH            ;
            CALL BusyWrite  ;
            POP             ;
            STOD 4094       ;
            CALL BuzyWait:  ;
            LODD PSTR1:     ;
            JUMP NextWord:  ; Continue to process the next word
BusyWrite:  LODD 4095       ; Buzy waiting write; wait until m[4095] >= 10
            SUBD mask:      ;
            JNEG BusyWrite: ;
            RETN            ; Return
BuzyRead:   LODD 4093       ; Buzy waiting read
            SUBD mask       ;
            JNEG BuzyRead   ;
            RETN            ; Return
FINISH:     LODL 1          ;
            RETN
.LOC 200
numoff:     48              ; ASCII code value of '0'
nextchar:   0               ; Next character
numptr:     binum1:         ; Pointer to the number to process
binum1:     0               ; First number to add
binum2:     0               ; Second number to add
mask:       10              ; ASCII code value of newline character '\n'
on:         8
nl:         10
cr:         13              ; ASCII code value of '\' (carriage return)
c1:         1               ; Constant 1
c10:        10              ; Constant 10
c255:       255             ; Constant 255
sum:        0
numcount:   1
pstr1:      0
prompt:     "Please input a 1-5 digit number followed by enter: "
