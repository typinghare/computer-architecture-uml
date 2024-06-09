Start:          LODD on             ;
                STOD 4095           ;
                CALL BusyWrite:     ;
                LOCO prompt:        ;
PrintStr:       PSHI                ; Push the first 2-chars to stack
                ADDD c1:            ; Increment the address in AC by 1
                STOD strptr:        ; Save the address of the next 2-chars
                POP                 ; Pop the first 2-chars to AC
                JZER PrintCRLF:     ; End printing if the character is '\0'
                STOD 4094           ; Store the 2-chars to buffer
                PUSH                ; Push the 2-chars to the stack
                SUBD c255:          ;
                JNEG CPrintCRLF:    ; Clean the stack and print CRLF
                CALL Sb:            ;
                INSP 1              ; Clear the stack
                PUSH                ; Push the
                CALL BusyWrite:     ;
                POP                 ;
                STOD 4094           ;
                CALL BusyWrite:     ;
                LODD strptr:        ; Load the address of the next-2chars to AC
                JUMP NEXTW:         ; Continue to print the string
CPrintCRLF:     INSP 1              ; Clean up the stack before printing CRLF
; @brief Prints "\r\n"
PrintCRLF:      LODD asciicr:       ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\r'
                LODD asciinl:       ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\n'
                LODD on:            ; Let MIC-1 program print the string
                STOD 4093           ; and scan in a 1-5 digit number
BusyWrite:      LODD 4095           ; Buzy waiting write; wait until m[4095] >= 10
                SUBD asciinl:       ;
                JNEG BusyWrite:     ;
                RETN                ; Return
BuzyRead:       LODD 4093           ; Buzy waiting read
                SUBD asciinl:       ;
                JNEG BuzyRead:      ;
                RETN                ; Return
; @brief Shifts the left 8 bits to the right
; @param m[sp + 1]: the 2-chars to be processed
Sb:             LOCO 8              ; ac := 8
Loop1:          JZER Finish:        ;
                SUBD c1:            ;
                STOD loopCount:     ; loopCount--;
                LODL 1              ; Load the 2-chars
                JNEG Add1:          ;
                ADDL 1              ;
                STOL 1              ; m[sp + 1] <<= 1
                LODD loopCount:     ; Continue next loop
                JUMP Loop1:         ;
Add1:           ADDL 1              ; ac += m[sp + 1]
                ADDD c1:            ; ac++;
                STOL 1              ; m[sp + 1] = (m[sp + 1] << 1) + 1
                LODD                ;
                JUMP LOOP1:         ;
Finish:         LODL 1              ; ac := m[sp + 1]
                RETN                ; Return m[sp + 1]
.LOC 200
on:             8                   ; MIC-1 on signal
ascii0:         48
asciinl:        10
asciicr:        13
c1:             1                   ; Constant 1
c10:            10                  ; Constant 10
c255:           255                 ; Constant 255
strptr:         0                   ; Pointer to character to print
loopCount:      0                   ; Loop count
prompt:         "Please input a 1-5 digit number followed by enter: "