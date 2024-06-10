Start:          LOCO PROMPT:        ;
                CALL PrintStr:      ; Print the prmopt string
                CALL ScanNum:       ; Scan the first number
                LOCO PROMPT:        ;
                CALL PrintStr:      ; Print the prmopt string
                CALL ScanNum:       ; Scan the second number
                CALL AddNums:       ; Add the two numbers
                CALL PrintNum:      ; Print the sum
                JUMP Exit:          ; Exit the program

; @brief Prints a string.
; @param r[ac] The address of the string to print.
PrintStr:       PUSH                ; Push the address onto the stack
                LODD ON:            ; (Actually idk what does ON: mean)
                STOD 4095           ; Prepare for writing buffer
                CALL BusyWrite:     ; Wait until the the buffer is ready
                POP                 ; Pop the address to the stack
PrintLoop:      PSHI                ; Push the first 2-chars to stack
                ADDD C1:            ; Increment the address in AC by 1
                STOD str_ptr:       ; Save the address of the next 2-chars
                POP                 ; Pop the first 2-chars to AC
                JZER PrintCRLF:     ; End printing if the character is '\0'
                STOD 4094           ; Store the lower character to the buffer
                PUSH                ; Push the 2-chars onto the stack
                SUBD C255:          ;
                JNEG CPrintCRLF:    ; Clean the stack and print CRLF
                CALL SwapChars:     ; Swap the two characters
                INSP 1              ; Clear the stack
                PUSH                ; Push the swaped 2-chars onto the stack
                CALL BusyWrite:     ;
                POP                 ; Pop the swapeed 2-chars to AC
                STOD 4094           ; Store the higher character to the buffer
                CALL BusyWrite:     ; Wait until it is printed
                LODD str_ptr:       ; Load the address of the next 2-chars to AC
                JUMP PrintLoop:     ; Continue to print the string
CPrintCRLF:     INSP 1              ; Clean up the stack before printing CRLF
PrintCRLF:      LODD ASCII_CR:      ; The following prints "\r\n".
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\r'
                LODD ASCII_NL:      ;
                STOD 4094           ;
                CALL BusyWrite:     ; Print '\n'
                LODD ON:            ;
                STOD 4093           ; Let MIC-1 program print the string
                RETN                ; Return

; @brief Scans in a 1-5 digit number. The number will be stored to either num1
;        or num2 according to num_ptr.
ScanNum:        CALL BusyRead:      ; Read a character
                LODD 4092           ; Lodd the character to AC
                SUBD ASCII_0:       ; Convert it into the corresponding digit
                PUSH                ; Push the digit onto the stack
NextDigit:      CALL BusyRead:      ; Read a character
                LODD 4092           ;
                STOD next_char:     ; Store the character
                SUBD ASCII_NL:      ;
                JZER EndNum:        ; If the character is '\n', it ends reading
                MULT 10             ; Base 10 left shift
                LODD next_char:     ; Load the next character to AC
                SUBD ASCII_0:       ; Convert it into the corresponding digit
                ADDL 0              ; Add m[sp] to it
                STOL 0              ; Store the result to m[sp]
                JUMP NextDigit:     ; Continue to read the next digit

; @brief Increments num_ptr and decrements num_count; Jumps to AddNums if
;        numnCount == 0, otherwise reads the other number.
EndNum:         LODD num_ptr:       ;
                POPI                ; Pop and store the value to num_ptr
                ADDD C1:            ;
                STOD num_ptr:       ; num_ptr++;
                LODD num_count:     ;
                JZER EndNumReturn:  ; Add the two numbers if num_count == 0
                SUBD C1:            ;
                STOD num_count:     ; num_count--;
EndNumReturn:   RETN                ; Return

; @brief Writes a character to the buffer; wait until m[4095] >= 10.
BusyWrite:      LODD 4095           ;
                SUBD ASCII_NL:      ;
                JNEG BusyWrite:     ;
                RETN                ; Return

; @brief Reads a character into the buffer; wait until m[4093] >= 10.
BusyRead:       LODD 4093           ; Buzy waiting read
                SUBD ASCII_NL:      ;
                JNEG BusyRead:      ;
                RETN                ; Return

; @brief Shifts the left 8 bits to the right.
; @param m[sp + 1] The 2-chars to be processed.
SwapChars:      LOCO 8              ; ac = 8
Loop1:          JZER Finish:        ;
                SUBD C1:            ;
                STOD loop_count:    ; loop_count--;
                LODL 1              ; ac = m[sp + 1]
                JNEG Add1:          ; If MSB == 1, add 1 after the shift
                ADDL 1              ; Equivalent to: ac <<= 1
                JUMP StoreNewChars: ;
Add1:           ADDL 1              ; Equivalent to: ac <<= 1
                ADDD C1:            ; ac++;
StoreNewChars:  STOL 1              ; m[sp + 1] = ac
                LODD loop_count:    ; Continue next loop
                JUMP Loop1:         ;
Finish:         LODL 1              ; ac = m[sp + 1]
                RETN                ; Return m[sp + 1]

; @brief Adds the two numbers. The result is stored to AC.
; @return ac The result of num1 + num2
AddNums:        LODD num1:          ; ac = num1
                PUSH                ; Push num1 onto the stack
                LODD num2:          ; ac = num2
                ADDL 0              ; ac = num1 + num2
                INSP 1              ; Clear the stack
                RETN                ; Return

; @brief Prints a number in the string form of base 10.
; @param ac The number to print.
; 1234 -> ['2', '1'], ['4', '3'], ['\0', '\0']
; 456 -> ['5', '4'], ['\0', '6']
; But: 1234 -> ['4', '3'], []
PrintNum:       STOD temp_num:      ; Store the number to print to temp_num
                CALL ResolveChars:  ; Resolve chars
                CALL Resolve2Chars: ; Resolve 2chars
                RETN                ; Return

; @brief Converts each digit in temp_num to corresponding digit char, and push
;        it onto the res_char stack (see char_stack). When return,
;        char_stack_ptr is ensured to point to the first non-zero character.
ResolveChars:   LODD temp_num:      ;
                JZER RCDone:        ; Return if temp_num == 0
                CALL NextDigitChar: ; Get the next digit char
                PUSH                ; Push it onto the stack
                LODD char_stack_ptr:; Load the pointer to the next res_char
                SUBD C1:            ;
                STOD char_stack_ptr:; char_stack_ptr++
                POPI                ; Pop the next digit char to res_char
                JUMP ResolveChars:  ; Contninue to resolve temp_num
RCDone:         RETN

; @brief Convert chars in the res_char stack to 2-chars and put them to the
;        2chars array (see chars-arr).
Resolve2Chars:  LODD char_stack_ptr:;
                PSHI                ;
                POP                 ; ac = m[char_stack_ptr]
                JNEG R2CDone:       ; Out of stack
                PUSH                ; Push m[char_stack_ptr] onto stack
                LODD chars_ptr:     ; Load the 2-chars pointer
                POPI                ; Pop m[char_stack_ptr] to &char_ptr
                LODD char_stack_ptr:;
                ADDD C1:            ;
                STOD char_stack_ptr:; char_stack_ptr++;
                PSHI                ;
                POP                 ; ac = m[char_stack_ptr]
                JNEG R2CDone:       ; Out of stack
                PUSH                ; Push m[char_stack_ptr] onto stack
                LODD chars_ptr:     ; Load the 2-chars pointer
                PSHI                ; Push m[chars_ptr] onto stack
                CALL SwapChars:     ; Left shift the char to get the high char
                POP                 ; Pop to get the shifted char (high char)
                ADDL 0              ; ac = high_char + low_char
                PUSH                ;
                LODD chars_ptr:     ;
                POPI                ; Pop the combined 2-chars to &char_ptr
                JUMP Resolve2Chars: ; Continue to resolve remaining 2-chars
                LODD char_stack_ptr:;
                ADDD C1:            ;
                STOD char_stack_ptr:; char_stack_ptr++;
                LODD chars_ptr:     ;
                ADDD C1:            ;
                STOD chars_ptr:     ; chars_ptr++;
R2CDone:        RETN                ; Return

; @brief Divides temp_num by 10, and return the remainder as corresponding char.
NextDigitChar:  LODD C10:           ; ac = 10
                PUSH                ; Divisor: 10
                LODD temp_num:      ; Load the temporary number
                PUSH                ; Dividend: temp_num
                DIV                 ; temp_num /= 10
                POP                 ; ac = quotient
                STOD temp_num:      ; temp_num = quotient
                POP                 ; ac = remainder
                ADDD ASCII_0:       ; Convert it into the corresponding char
                INSP 2              ; Clear the stack
                RETN                ; Return

; @brief Exit the program.
Exit:           HALT                ;
                JUMP Exit:          ; Forever halt

.LOC 200                            ; <Constants>
ON:             8                   ; MIC-1 on signal
ASCII_0:        48                  ; '0'
ASCII_NL:       10                  ; '\n'
ASCII_CR:       13                  ; '\r'
C1:             1                   ; Constant 1
C10:            10                  ; Constant 10
C255:           255                 ; Constant 255
PROMPT:         "Please input a 1-5 digit number followed by enter: "

.LOC 500                            ; <Variables>
str_ptr:        0                   ; Pointer to character to print
next_char:      0                   ; Next character
num1:           0                   ; The first addend
num2:           0                   ; The second addend
num_ptr:        num1:               ; Pointer to the number to process
num_count:      1                   ; The count of remaining numbers to read
loop_count:     0                   ; Loop counts used in some functions
temp_num:       0                   ; Temporary number
high_char:      0                   ; High character used in PrintNum
char_stack_top: 0                   ; [509] Char stack
                0
                0
                0
                0
char_stack_bot: -1
char_stack_ptr: char_stack_bot:
chars_arr:      0
                0
                0
chars_ptr:      chars_arr:
