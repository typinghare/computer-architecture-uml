// Copyright 2024 lJames
// ReSharper disable CppDFAUnusedValue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Mic-1 Macro instructions. Three macro instructions are added to the new macro
 * compiler.
 */
#define LODD 1
#define STOD 2
#define ADDD 3
#define SUBD 4
#define JPOS 5
#define JZER 6
#define JUMP 7
#define LOCO 8
#define LODL 9
#define STOL 10
#define ADDL 11
#define SUBL 12
#define JNEG 13
#define JNZE 14
#define CALL 15
#define PSHI 16
#define POPI 17
#define PUSH 18
#define POP 19
#define RETN 20
#define SWAP 21
#define INSP 22
#define DESP 23
#define HALT 24
#define INTEG 25
#define JUNK 26
#define LABEL 27
#define LOC 28
#define STR 29
#define MULT 30
#define RSHIFT 31
#define DIV 32
#define LINE 100

/**
 * Global constants.
 */
char cstr_6[7] = "000000\0";
char cstr_8[9] = "00000000\0";
char cstr_12[13] = "000000000000\0";
char cstr_16[17] = "0000000000000000\0";
char binstr_16[17] = "0000000000000000\0";
int label_pc = -1;
unsigned short pc = 0;
unsigned short line = 1;
FILE* p1;

/**
 * @brief Converts a string form of a decimal number into a string of
 * corresponding binary sequence. The result will be saved to the global array
 * cstr_6[7] seen at the beginning of this file.
 * @param cstr The string form of a decimal number to be converted.
 * @example
 *      str_6("23") => "0010111"
 */
void str_6(const char* cstr);

/**
 * @brief Converts a string form of a decimal number into a string of
 * corresponding binary sequence. The result will be saved to the global array
 * cstr_8[9] seen at the beginning of this file.
 * @param cstr The string form of a decimal number to be converted.
 * @example
 *      str_6("23") => "0010111"
 */
void str_8(const char* cstr);

/**
 * @brief Converts a string form of a decimal number into a string of
 * corresponding binary sequence. The result will be saved to the global array
 * cstr_12[13] seen at the beginning of this file.
 * @param cstr The string form of a decimal number to be converted.
 * @example
 *      str_6("23") => "0010111"
 */
void str_12(const char* cstr);

/**
 * @brief Converts a string form of a decimal number into a string of
 * corresponding binary sequence. The result will be saved to the global array
 * cstr_16[17] seen at the beginning of this file.
 * @param cstr The string form of a decimal number to be converted.
 * @example
 *      str_6("23") => "0010111"
 */
void str_16(const char* cstr);

/**
 * @brief Converts an actual short integer into a string of 16 bits will a NULL
 * type in position 17 of the array.
 */
void bstr_16(unsigned short bin_num);

/**
 * @brief Rewinds the temporary file and complete each unresolved instruction,
 * then send binary to stdout.
 */
void generate_code(int);

/**
 * @brief Enter the value of a symbol to the symbol table.
 */
void update_symbol_table(const char* symbol);

/**
 * Searches the symbol table for a symbol. Return the symbol as soon as it is
 * found, otherwise, add the symbol to the table at the head of the symbol table
 * linked list.
 */
void search_symbol_table(const char* symbol);

/**
 * @brief Dumps a symbol table for the `-s` masm command line option.
 */
void dump_table(void);

/**
 * @brief Returns symbol value to complete an instruction.
 */
int get_symbol_val(const char* symbol);

/**
 * @brief Prints the message of a bad operand error, and exit the program.
 * @param name The name of the instruction.
 * @param token The operand token that causes the error.
 * @param line The line of the token.
 */
void badOperandError(char* name, char* token, int line);

/**
 * @brief Label name node.
 */
struct nament {
    char name[26];
    int addr;
    struct nament* next;
};

struct nament* symbol_table = NULL;

// Imported from `lex.yy.c`
extern int yylex(void);
extern char* yytext;

int main(const int argc, char* argv[]) {
    int tok, i, dump_tab = 0, line_number = 0;
    unsigned short temp;
    char temp_file[20];

    // if option `-s` is included on masm command, then set up to dump the
    // symbol table after the binary code
    if (argc > 1 && strcmp(argv[1], "-s") == 0)
        dump_tab = line_number = 1;

    sprintf(temp_file, "/tmp/asm_%d", getuid());
    p1 = fopen(temp_file, "w+");
    unlink(temp_file);

    while ((tok = yylex())) {
        switch (tok) {
            case LODD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0000%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0000000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("LODD", yytext, line);
                }
                break;

            case STOD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0001%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0001000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("STOD", yytext, line);
                }
                break;

            case ADDD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0010%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0010000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("ADDD", yytext, line);
                }
                break;

            case SUBD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0011%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0011000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("SUBD", yytext, line);
                }
                break;

            case JPOS:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0100%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0100000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("JPOS", yytext, line);
                }
                break;

            case JZER:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0101%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0101000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("JZER", yytext, line);
                }
                break;

            case JUMP:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0110%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0110000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("JUMP", yytext, line);
                }
                break;

            case LOCO:
                switch (tok = yylex()) {
                    case INTEG:
                        if (yytext[0] == '-') {
                            fprintf(
                                stderr,
                                "Negative operand after LOCO is %s on line %d, "
                                "must be positive !\n",
                                yytext, pc);
                            exit(1);
                        }
                        str_12(yytext);
                        fprintf(p1, "%d  0111%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U0111000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("LOCO", yytext, line);
                }
                break;


            case LODL:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("LODL", yytext, line);
                }
                str_12(yytext);
                fprintf(p1, "%d  1000%s\n", pc, cstr_12);
                break;

            case STOL:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("STOL", yytext, line);
                }
                str_12(yytext);
                fprintf(p1, "%d  1001%s\n", pc, cstr_12);
                break;

            case ADDL:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("ADDL", yytext, line);
                }
                str_12(yytext);
                fprintf(p1, "%d  1010%s\n", pc, cstr_12);
                break;

            case SUBL:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("SUBL", yytext, line);
                }
                str_12(yytext);
                fprintf(p1, "%d  1011%s\n", pc, cstr_12);
                break;

            case JNEG:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1100%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U1100000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("JNEG", yytext, line);
                }
                break;

            case JNZE:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1101%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U1101000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("JNZE", yytext, line);
                }
                break;

            case CALL:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1110%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(
                            p1, "%d  U1110000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        badOperandError("CALL", yytext, line);
                }
                break;

            case PSHI:
                fprintf(p1, "%d  1111000000000000\n", pc);
                break;

            case POPI:
                fprintf(p1, "%d  1111001000000000\n", pc);
                break;

            case PUSH:
                fprintf(p1, "%d  1111010000000000\n", pc);
                break;

            case POP:
                fprintf(p1, "%d  1111011000000000\n", pc);
                break;

            case RETN:
                fprintf(p1, "%d  1111100000000000\n", pc);
                break;

            case SWAP:
                fprintf(p1, "%d  1111101000000000\n", pc);
                break;

            case INSP:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("INSP", yytext, line);
                }
                str_8(yytext);
                fprintf(p1, "%d  11111100%s\n", pc, cstr_8);
                break;

            case DESP:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("DESP", yytext, line);
                }
                str_8(yytext);
                fprintf(p1, "%d  11111110%s\n", pc, cstr_8);
                break;

            case HALT:
                fprintf(p1, "%d  1111111111000000\n", pc);
                break;

            case MULT:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("MULT", yytext, line);
                }
                str_6(yytext);
                fprintf(p1, "%d 1111111100%s\n", pc, cstr_6);
                break;

            case RSHIFT:
                if ((tok = yylex()) != INTEG) {
                    badOperandError("RSHIFT", yytext, line);
                }
                str_6(yytext);
                fprintf(p1, "%d 1111111101%s\n", pc, cstr_6);
                break;

            case DIV:
                fprintf(p1, "%d 1111111110000000\n", pc);
                break;

            case INTEG:
                str_16(yytext);
                fprintf(p1, "%d  %s\n", pc, cstr_16);
                break;

            case LABEL:
                if (label_pc == pc) {
                    fprintf(p1, "%d  U0000000000000000    %s\n", pc, yytext);
                    break;
                }
                search_symbol_table(yytext);
                update_symbol_table(yytext);
                label_pc = pc;
                pc--;
                break;

            case LOC:
                if ((tok = yylex()) != INTEG) {
                    badOperandError(".LOC", yytext, line);
                }
                if ((temp = (unsigned short)atoi(yytext)) < pc) {
                    fprintf(
                        stderr, "Bad operand after .LOC is %s, TOO SMALL !\n",
                        yytext);
                    exit(1);
                }

                pc = temp - 1;
                break;

            case STR:
                i = 1;
                do {
                    if (*(yytext + i) == '\"') {
                        bstr_16(0);
                        fprintf(p1, "%d  %s\n", pc, binstr_16);
                        break;
                    }
                    temp = (unsigned short)*(yytext + i++);
                    if (*(yytext + i) != '\"') {
                        temp = temp | (unsigned short)*(yytext + i) << 8;
                    }
                    bstr_16(temp);
                    fprintf(p1, "%d  %s\n", pc, binstr_16);
                }
                while (*(yytext + i++) != '\"' && ++pc);
                break;

            case JUNK:
                fprintf(stderr, "Unrecognized token is %s\n", yytext);
                exit(26);

            case LINE:
                line++;
                break;

            default:
                fprintf(stderr, "Unknown token type: %d\n", tok);
                exit(26);
        }
        pc++;
    }

    generate_code(line_number);

    if (dump_tab)
        dump_table();

    return 0;
}

void dump_table(void) {
    FILE* fd = popen("sort +0 -1 -f", "w");
    printf("***********************************************\n");
    for (struct nament* list = symbol_table; list != (struct nament*)0;
         list = list->next) {
        fprintf(fd, "%-25s %4d\n", list->name, list->addr);
    }
    fclose(fd);
    wait(NULL);
    printf("***********************************************\n");
}

int get_symbol_val(const char* symbol) {
    for (const struct nament* list = symbol_table; list != NULL;
         list = list->next) {
        if (strcmp(list->name, symbol) == 0) {
            return list->addr;
        }
    }

    return -1;
}

void generate_code(const int line_num) {
    char line_buffer[10];
    char instruction[18];
    int pc, sym_val, i, old_pc, diff;

    int line_number = old_pc = 0;
    rewind(p1);

    sprintf(line_buffer, "%5d:  ", line_number);

    while (fscanf(p1, "%d %s", &pc, instruction) != EOF) {
        if ((diff = pc - old_pc) > 1) {
            for (int j = 1; j < diff; j++) {
                sprintf(line_buffer, "%5d:  ", line_number++);
                printf("%s1111111111111111\n", line_num ? line_buffer : "\0");
            }
        }
        sprintf(line_buffer, "%5d:  ", line_number++);
        old_pc = pc;

        if (instruction[0] == 'U') {
            char symbol[26];
            fscanf(p1, "%s", symbol);
            if ((sym_val = get_symbol_val(symbol)) == -1) {
                fprintf(stderr, "no symbol in symbol table: %s\n", symbol);
                exit(27);
            }

            for (i = 0; i < 12; i++) {
                cstr_12[i] = '0';
            }
            cstr_12[12] = '\0';

            int mask = 2048;
            for (i = 0; i < 12; i++) {
                if (sym_val & mask)
                    cstr_12[i] = '1';
                mask >>= 1;
            }
            for (i = 0; i < 12; i++) {
                instruction[i + 5] = cstr_12[i];
            }
            printf("%s%s\n", line_num ? line_buffer : "\0", &instruction[1]);
        } else
            printf("%s%s\n", line_num ? line_buffer : "\0", instruction);
    }
    fclose(p1);
}

void update_symbol_table(const char* symbol) {
    for (struct nament* list = symbol_table; list; list = list->next) {
        if (strcmp(list->name, symbol) == 0) {
            list->addr = pc;
            return;
        }
    }
    fprintf(stderr, "error from symbol table on line %d\n", pc);
    exit(27);
}

void search_symbol_table(const char* symbol) {
    for (const struct nament* list = symbol_table; list; list = list->next) {
        if (strcmp(list->name, symbol) == 0)
            return;
    }
    struct nament* element = malloc(sizeof(struct nament));
    strcpy(element->name, symbol);
    element->next = symbol_table;
    symbol_table = element;
}

void str_6(const char* cstr) {
    const unsigned short str_val = atoi(cstr);
    int mask = 1 << 5;
    for (int i = 0; i < 6; i++, mask >>= 1) {
        cstr_6[i] = str_val & mask ? '1' : '0';
    }
}

void str_8(const char* cstr) {
    const unsigned short str_val = atoi(cstr);
    int mask = 1 << 7;
    for (int i = 0; i < 8; i++, mask >>= 1) {
        cstr_8[i] = str_val & mask ? '1' : '0';
    }
}

void str_12(const char* cstr) {
    const unsigned short str_val = atoi(cstr);
    int mask = 1 << 11;
    for (int i = 0; i < 12; i++, mask >>= 1) {
        cstr_12[i] = str_val & mask ? '1' : '0';
    }
}

void str_16(const char* cstr) {
    const unsigned short str_val = atoi(cstr);
    int mask = 1 << 15;
    for (int i = 0; i < 16; i++, mask >>= 1) {
        cstr_16[i] = str_val & mask ? '1' : '0';
    }
}

void bstr_16(const unsigned short bin_num) {
    const short str_val = bin_num;
    int mask = 1 << 15;
    for (int i = 0; i < 16; i++, mask >>= 1) {
        binstr_16[i] = str_val & mask ? '1' : '0';
    }
}

void badOperandError(char* name, char* token, const int line) {
    fprintf(
        stderr, "Bad operand after %s is %s on line %d\n", name, token, line);
    exit(1);
}
