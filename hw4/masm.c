// Copyright 2024 James Chen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/wait.h>

/**
 * Marco instructions. Three macro instructions are added: RSHIFT, MULT, and DIV.
 */
#define         LODD       1
#define         STOD       2
#define         ADDD       3
#define         SUBD       4
#define         JPOS       5
#define         JZER       6
#define         JUMP       7
#define         LOCO       8
#define         LODL       9
#define         STOL      10
#define         ADDL      11
#define         SUBL      12
#define         JNEG      13
#define         JNZE      14
#define         CALL      15
#define         PSHI      16
#define         POPI      17
#define         PUSH      18
#define         POP       19
#define         RETN      20
#define         SWAP      21
#define         INSP      22
#define         DESP      23
#define         HALT      24
#define         INTEG     25
#define         JUNK      26
#define         LABEL     27
#define         LOC       28
#define         STR       29
#define         NAND	  30
#define         RSHIFT	  31
#define         MULT      32
#define         DIV       33

/**
 * @brief Name node.
 */
struct nament {
    char name[26];
    int addr;
    struct nament *next;
};

// The head of the symbol table
struct nament *symbol_table = NULL;

/**
 * Global variables.
 */
char cstr_6[7];
char cstr_8[9];
char cstr_12[13];
char cstr_16[17];
char binstr_16[17];
int label_pc = -1;
unsigned short pc = 0;
FILE *p1;

void str_6(char *);

void str_8(char *);

void str_12(char *);

void str_16(char *);

void bstr_16(unsigned short);

void generate_code(int);

void update_sym_table(char *);

void search_sym_table(char *);

void dump_table(void);

// imported from the lex.yy.c code
extern int yylex(void);

extern char *yytext;


int main(const int argc, char *argv[]) {
    int tok, i, dump_tab = 0, line_num = 0;
    unsigned short temp;
    char temp_file[20];

    // if the option `-s` is included on masm command, set up to dump the symbol table after the
    // binary code
    if (argc > 1 && 0 == strcmp(argv[1], "-s")) dump_tab = line_num = 1;

    sprintf(temp_file, "/tmp/asm_%d", getuid());

    p1 = fopen(temp_file, "w+");
    unlink(temp_file);
    while ((tok = yylex())) {
        switch (tok) {
            // ReSharper disable once CppDFAUnusedValue
            case LODD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0000%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0000000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after LODD is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case STOD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0001%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0001000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after STOD is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case ADDD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0010%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0010000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after ADDD is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case SUBD:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0011%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0011000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after SUBD is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case JPOS:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0100%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0100000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after JPOS is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case JZER:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0101%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0101000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after JZER is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case JUMP:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  0110%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0110000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after JUMP is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case LOCO:
                switch (tok = yylex()) {
                    case INTEG:
                        if (yytext[0] == '-') {
                            fprintf(
                                stderr,
                                "Negative operand after LOCO is %s on line %d, must be positive !\n",
                                yytext, pc);
                            exit(1);
                        }
                        str_12(yytext);
                        fprintf(p1, "%d  0111%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U0111000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after LOCO is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case LODL:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after LODL is %s\n", yytext);
                    exit(1);
                }
                str_12(yytext);
                fprintf(p1, "%d  1000%s\n", pc, cstr_12);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case STOL:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after STOL is %s\n", yytext);
                    exit(1);
                }
                str_12(yytext);
                fprintf(p1, "%d  1001%s\n", pc, cstr_12);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case ADDL:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after ADDL is %s\n", yytext);
                    exit(1);
                }
                str_12(yytext);
                fprintf(p1, "%d  1010%s\n", pc, cstr_12);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case SUBL:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after SUBL is %s\n", yytext);
                    exit(1);
                }
                str_12(yytext);
                fprintf(p1, "%d  1011%s\n", pc, cstr_12);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case JNEG:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1100%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U1100000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after JNEG is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case JNZE:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1101%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U1101000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after JNZE is %s on line %d\n", yytext, pc);
                        exit(1);
                }
                break;

            // ReSharper disable once CppDFAUnusedValue
            case CALL:
                switch (tok = yylex()) {
                    case INTEG:
                        str_12(yytext);
                        fprintf(p1, "%d  1110%s\n", pc, cstr_12);
                        break;
                    case LABEL:
                        fprintf(p1, "%d  U1110000000000000    %s\n", pc, yytext);
                        break;
                    default:
                        fprintf(stderr, "Bad operand after CALL is %s on line %d\n", yytext, pc);
                        exit(1);
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

            // ReSharper disable once CppDFAUnusedValue
            case INSP:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after INSP is %s\n", yytext);
                    exit(1);
                }
                str_8(yytext);
                fprintf(p1, "%d  11111100%s\n", pc, cstr_8);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case DESP:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after DESP is %s\n", yytext);
                    exit(1);
                }
                str_8(yytext);
                fprintf(p1, "%d  11111110%s\n", pc, cstr_8);
                break;

            case HALT:
                fprintf(p1, "%d  1111111111000000\n", pc);
                break;

            case NAND:
                fprintf(p1, "%d  1111111100000000\n", pc);
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
                search_sym_table(yytext);
                update_sym_table(yytext);
                label_pc = pc;
                pc--;
                break;

            // ReSharper disable once CppDFAUnusedValue
            case LOC:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after .LOC is %s\n", yytext);
                    exit(1);
                }
                if ((temp = ((unsigned short) atoi(yytext))) < pc) {
                    fprintf(stderr, "Bad operand after .LOC is %s, TOO SMALL !\n", yytext);
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
                    temp = (unsigned short) *(yytext + i++);
                    if (*(yytext + i) != '\"') {
                        temp = (temp | ((unsigned short) *(yytext + i) << 8));
                    }
                    bstr_16(temp);
                    fprintf(p1, "%d  %s\n", pc, binstr_16);
                } while (*(yytext + i++) != '\"' && ++pc);
                break;


            case JUNK: fprintf(stderr, "Unrecognized token is %s\n", yytext);
                exit(26);

            // ReSharper disable once CppDFAUnusedValue
            case RSHIFT:
                if ((tok = yylex() != INTEG)) {
                    fprintf(stderr, "Bad operand after RSHIFT is %s\n", yytext);
                    exit(1);
                }
                str_6(yytext);
                fprintf(p1, "%d  1111111101%s\n", pc, cstr_6);
                break;

            // ReSharper disable once CppDFAUnusedValue
            case MULT:
                if ((tok = yylex()) != INTEG) {
                    fprintf(stderr, "Bad operand after MULT is %s\n", yytext);
                    exit(1);
                }
                str_6(yytext);
                fprintf(p1, "%d 1111111100%s\n", pc, cstr_6);
                break;

            case DIV:
                fprintf(p1, "%d 1111111110000000\n", pc);
                break;

            default: fprintf(stderr, "Default case, unrecoverable error\n");
                exit(26);
        }
        pc++;
    }

    generate_code(line_num);

    if (dump_tab)dump_table();

    return 0;
}
