Start:

PrintPrompt:    LODD on:            ;
                STOD 4095           ;
                CALL BusyWrite:     ;
                LOCO prompt:        ;
                CALL PrintStr       ; Print the prompt string
                CALL ScanNum        ; Scan the first number
                CALL PrintStr       ; Print the prompt string
                CALL ScanNum        ; Scan the second number
                CALL AddNums        ; Add the two numbers

; @brief Prints a string.
; @param r[ac] The address of the string to print.
PrintStr:       PSHI                ; Push the first 2-chars to stack
                ADDD c1:            ; Increment the address in AC by 1
                STOD str_ptr:       ; Save the address of the next 2-chars
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
                LODD str_ptr:       ; Load the address of the next 2-chars to AC
                JUMP PrintStr:      ; Continue to print the string
CPrintCRLF:     INSP 1              ; Clean up the stack before printing CRLF
PrintCRLF:      LODD ascii_cr:      ; The following prints "\r\n".
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\r'
                LODD asciinl:       ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\n'
                LODD on:            ;
                STOD 4093           ; Let MIC-1 program print the string
                RETN                ; Return

; @brief Scans in a 1-5 digit number. The number will be stored to either num1
;        or num2 according to num_ptr.
ScanNum:        call BusyRead:      ; Read a character
                LODD 4092           ; Lodd the character to AC
                SUBD ascii0:        ; Convert it into the corresponding digit
                PUSH                ; Push the digit to the stack
NextDigit:      CALL BusyRead:      ; Read a character
                LODD 4092           ;
                STOD next_char:     ; Store the character
                SUBD asciinl:       ;
                JZER EndNum:        ; If the character is '\n', it ends reading
                MULT 10             ; Base 10 left shift
                LODD next_char:     ; Load the next character to AC
                SUBD ascii0:        ; Convert it into the corresponding digit
                ADDL 0              ; Add m[sp] to it
                STOL 0              ; Store the result to m[sp]
                JUMP NextDigit:     ; Continue to read the next digit

; @brief Increments num_ptr and decrements num_count; Jumps to AddNums if
;        numnCount == 0, otherwise reads the other number.
EndNum:         LODD num_ptr:       ;
                POPI                ; Pop and store the value to num_ptr
                ADDD c1:            ;
                STOD num_ptr:       ; num_ptr++;
                LODD num_count:     ;
                JZER AddNums:       ; Add the two numbers if num_count == 0
                SUBD c1:            ;
                STOD num_count:     ; num_count--;
                RETN                ; Return

; @brief Writes a character to the buffer; wait until m[4095] >= 10.
BusyWrite:      LODD 4095           ;
                SUBD asciinl:       ;
                JNEG BusyWrite:     ;
                RETN                ; Return

; @brief Reads a character into the buffer; wait until m[4093] >= 10.
BusyRead:       LODD 4093           ; Buzy waiting read
                SUBD asciinl:       ;
                JNEG BusyRead:      ;
                RETN                ; Return

; @brief Shifts the left 8 bits to the right.
; @param m[sp + 1] The 2-chars to be processed.
SwapChars:      LOCO 8              ; ac := 8
Loop1:          JZER Finish:        ;
                SUBD c1:            ;
                STOD loop_count:    ; loop_count--;
                LODL 1              ; ac = m[sp + 1]
                JNEG Add1:          ; If MSB == 1, add 1 after the shift
                ADDL 1              ; Equivalent to: ac <<= 1
                JUMP StoreNewChars: ;
Add1:           ADDL 1              ; Equivalent to: ac <<= 1
                ADDD c1:            ; ac++;
StoreNewChars:  STOL 1              ; m[sp + 1] = ac
                LODD loop_count:    ; Continue next loop
                JUMP Loop1:         ;
Finish:         LODL 1              ; ac := m[sp + 1]
                RETN                ; Return m[sp + 1]

; @brief Adds the two numbers. The result is stored to AC.
AddNums:        HALT                ;

.LOC 200                            ; <Constants>
on:             8                   ; MIC-1 on signal
ascii_0:        48                  ; '0'
ascii_nl:       10                  ; '\n'
ascii_cr:       13                  ; '\r'
c1:             1                   ; Constant 1
c10:            10                  ; Constant 10
c255:           255                 ; Constant 255
prompt:         "Please input a 1-5 digit number followed by enter: "

.LOC 500                            ; <Variables>
str_ptr:        0                   ; Pointer to character to print
next_char:      0                   ; Next character
num1:           0                   ; The first addend
num2:           0                   ; The second addend
num_ptr:        num1:               ; Pointer to the number to process
num_count:      1                   ; The count of remaining numbers to read
loop_count:     0                   ; Loop counts used in SwapChars
