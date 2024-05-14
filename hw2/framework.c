#include "framework.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int print_bits(const FLOAT_UN float_32, char *text) {
    // Initialize an all-spaces string
    char bit_string[43];
    for (int i = 0; i < 42; i++) {
        bit_string[i] = ' ';
    }
    bit_string[42] = '\0';

    // Sign bit
    bit_string[0] = float_32.bit.b31 ? '1' : '0';

    // Exponent
    bit_string[2] = float_32.bit.b30 ? '1' : '0';
    bit_string[3] = float_32.bit.b29 ? '1' : '0';
    bit_string[4] = float_32.bit.b28 ? '1' : '0';
    bit_string[5] = float_32.bit.b27 ? '1' : '0';
    bit_string[7] = float_32.bit.b26 ? '1' : '0';
    bit_string[8] = float_32.bit.b25 ? '1' : '0';
    bit_string[9] = float_32.bit.b24 ? '1' : '0';
    bit_string[10] = float_32.bit.b23 ? '1' : '0';

    // Mantissa
    bit_string[12] = float_32.bit.b22 ? '1' : '0';
    bit_string[13] = float_32.bit.b21 ? '1' : '0';
    bit_string[14] = float_32.bit.b20 ? '1' : '0';
    bit_string[16] = float_32.bit.b19 ? '1' : '0';
    bit_string[17] = float_32.bit.b18 ? '1' : '0';
    bit_string[18] = float_32.bit.b17 ? '1' : '0';
    bit_string[19] = float_32.bit.b16 ? '1' : '0';
    bit_string[21] = float_32.bit.b15 ? '1' : '0';
    bit_string[22] = float_32.bit.b14 ? '1' : '0';
    bit_string[23] = float_32.bit.b13 ? '1' : '0';
    bit_string[24] = float_32.bit.b12 ? '1' : '0';
    bit_string[26] = float_32.bit.b11 ? '1' : '0';
    bit_string[27] = float_32.bit.b10 ? '1' : '0';
    bit_string[28] = float_32.bit.b9 ? '1' : '0';
    bit_string[29] = float_32.bit.b8 ? '1' : '0';
    bit_string[31] = float_32.bit.b7 ? '1' : '0';
    bit_string[32] = float_32.bit.b6 ? '1' : '0';
    bit_string[33] = float_32.bit.b5 ? '1' : '0';
    bit_string[34] = float_32.bit.b4 ? '1' : '0';
    bit_string[36] = float_32.bit.b3 ? '1' : '0';
    bit_string[37] = float_32.bit.b2 ? '1' : '0';
    bit_string[38] = float_32.bit.b1 ? '1' : '0';
    bit_string[39] = float_32.bit.b0 ? '1' : '0';

    // Print the binary string
    printf("%23s  %s\n", text, bit_string);

    return 0;
}

char *bold(const char *text) {
    const static char *ANSI_BOLD = "\033[1m";
    const static char *ANSI_RESET = "\033[0m";

    const size_t len = strlen(ANSI_BOLD) + strlen(text) + strlen(ANSI_RESET);
    char *formatted_text = malloc(len * sizeof(char));
    if (formatted_text != NULL) {
        strcat(formatted_text, ANSI_BOLD);
        strcat(formatted_text, text);
        strcat(formatted_text, ANSI_RESET);
    }

    return formatted_text;
}
