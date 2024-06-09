Start:          LODD on:            ;
                STOD 4095           ;
                CALL BusyWrite:     ;
                LOCO prompt:        ;
PrintStr:       PSHI                ; Push the first 2-chars to stack
                ADDD c1:            ; Increment the address in AC by 1
                STOD strptr:        ; Save the address of the next 2-chars
                POP                 ; Pop the first 2-chars to AC
                JZER PrintCRLF:     ; End printing if the character is '\0'
                STOD 4094           ; Store the lower character to the buffer
                PUSH                ; Push the 2-chars to the stack
                SUBD c255:          ;
                JNEG CPrintCRLF:    ; Clean the stack and print CRLF
                CALL SwapChars:     ; Swap the two characters
                INSP 1              ; Clear the stack
                PUSH                ; Push the swaped 2-chars to the stack
                CALL BusyWrite:     ;
                POP                 ; Pop the swapeed 2-chars to AC
                STOD 4094           ; Store the higher character to the buffer
                CALL BusyWrite:     ; Wait until it is printed
                LODD strptr:        ; Load the address of the next 2-chars to AC
                JUMP PrintStr:      ; Continue to print the string
CPrintCRLF:     INSP 1              ; Clean up the stack before printing CRLF
; @brief Prints "\r\n"
PrintCRLF:      LODD asciicr:       ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\r'
                LODD asciinl:       ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\n'
                LODD on:            ;
                STOD 4093           ; Let MIC-1 program print the string
; @brief Scan in a 1-5 digit number
ScanNum:        call BusyRead:      ; Read a character
                LODD 4092           ; Lodd the character to AC
                SUBD ascii0:        ; Convert it into the corresponding digit
                PUSH                ; Push the digit to the stack
NextDigit:      CALL BusyRead:      ; Read a character
                LODD 4092           ;
                STOD nextChar:      ; Store the character
                SUBD asciinl:       ;
                JZER EndNum:        ; If the character is '\n', it ends reading
                MULT 10             ; Base 10 left shift
                LODD nextChar:      ; Load the next character to AC
                SUBD ascii0:        ; Convert it into the corresponding digit
                ADDL 0              ; Add m[sp] to it
                STOL 0              ; Store the result to m[sp]
                JUMP NextDigit:     ; Continue to read the next digit
; @brief Increments numPtr and decrements numCount; Jumps to AddNums if
;        numnCount == 0, otherwise reads the other number
EndNum:         LODD numPtr:        ;
                POPI                ; Pop and store the value to numPtr
                ADDD c1:            ;
                STOD numPtr:        ; numPtr++;
                LODD numCount:      ;
                JZER AddNum:        ; Add the two numbers if numCount == 0
                SUBD c1:            ;
                STOD numCount:      ; numCount--;
                JUMP Start:         ; Read the other number
; @brief Adds the two numbers.
AddNum:         HALT                ;
; @brief Writes a character to the buffer; wait until m[4095] >= 10
BusyWrite:      LODD 4095
                SUBD asciinl:       ;
                JNEG BusyWrite:     ;
                RETN                ; Return
; @brief Reads a character into the buffer; wait until m[4093] >= 10
BusyRead:       LODD 4093           ; Buzy waiting read
                SUBD asciinl:       ;
                JNEG BusyRead:      ;
                RETN                ; Return
; @brief Shifts the left 8 bits to the right
; @param m[sp + 1]: the 2-chars to be processed
SwapChars:      LOCO 8              ; ac := 8
Loop1:          JZER Finish:        ;
                SUBD c1:            ;
                STOD loopCount:     ; loopCount--;
                LODL 1              ; ac = m[sp + 1]
                JNEG Add1:          ; If MSB == 1, add 1 after the shift
                ADDL 1              ; Equivalent to: ac <<= 1
                JUMP StoreNewChars: ;
Add1:           ADDL 1              ; Equivalent to: ac <<= 1
                ADDD c1:            ; ac++;
StoreNewChars:  STOL 1              ; m[sp + 1] = ac
                LODD loopCount:     ; Continue next loop
                JUMP Loop1:         ;
Finish:         LODL 1              ; ac := m[sp + 1]
                RETN                ; Return m[sp + 1]
.LOC 200                            ; Constants
on:             8                   ; MIC-1 on signal
ascii0:         48                  ; '0'
asciinl:        10                  ; '\n'
asciicr:        13                  ; '\r'
c1:             1                   ; Constant 1
c10:            10                  ; Constant 10
c255:           255                 ; Constant 255
prompt:         "Please input a 1-5 digit number followed by enter: "
.LOC 500                            ; Variables
strptr:         0                   ; Pointer to character to print
nextChar:       0                   ; Next character
num1:           0                   ; The first addend
num2:           0                   ; The second addend
numPtr:         num1:               ; Pointer to the number to process
numCount:       1                   ; The count of remaining numbers to read
loopCount:      0                   ; Loop counts used in SwapChars
