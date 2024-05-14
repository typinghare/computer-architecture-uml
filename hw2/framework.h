#ifndef FRAMEWORK_H
#define FRAMEWORK_H

typedef union float_32 {
    float floating_value_in_32_bits;
    int arg_32;

    struct sign_exp_mantissa {
        unsigned mantissa: 23;
        unsigned exponent: 8;
        unsigned sign: 1;
    } f_bits;

    struct single_bits {
        unsigned b0: 1;
        unsigned b1: 1;
        unsigned b2: 1;
        unsigned b3: 1;
        unsigned b4: 1;
        unsigned b5: 1;
        unsigned b6: 1;
        unsigned b7: 1;
        unsigned b8: 1;
        unsigned b9: 1;
        unsigned b10: 1;
        unsigned b11: 1;
        unsigned b12: 1;
        unsigned b13: 1;
        unsigned b14: 1;
        unsigned b15: 1;
        unsigned b16: 1;
        unsigned b17: 1;
        unsigned b18: 1;
        unsigned b19: 1;
        unsigned b20: 1;
        unsigned b21: 1;
        unsigned b22: 1;
        unsigned b23: 1;
        unsigned b24: 1;
        unsigned b25: 1;
        unsigned b26: 1;
        unsigned b27: 1;
        unsigned b28: 1;
        unsigned b29: 1;
        unsigned b30: 1;
        unsigned b31: 1;
    } bit;
} FLOAT_UN;

/**
 * @brief Prints the individual bits of a 32-bit floating-point number. This function takes a 32-bit
 * floating-point number represented as a union and prints its individual bits in a readable format.
 * @param float_32 The 32-bit floating-point number to print.
 * @param text A text string to prepend to the printed bits for identification.
 * @return Always returns 0.
 */
int print_bits(FLOAT_UN float_32, char *text);

/**
 * @brief Makes text bold with ANSI escape sequences.
 * @param text The text to be made bold.
 * @return The formatted text with bold effect.
 */
char *bold(const char *text);

#endif
