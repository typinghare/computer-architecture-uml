#include <stdio.h>
#include "framework.h"

int main() {
    FLOAT_UN float_32_s1, float_32_s2, float_32_rslt;

    // Local helper variables
    float the_hardware_result;
    int mant_s1, mant_s2, mant_res, exp_s1, exp_s2, exp_res;
    int shift_count;

    // Print prompts
    printf("%s", bold(
               "This program will emulate the addition of two IEEE 754 floating point numbers\n"));
    printf("Please enter two positive floating point values each with:\n");
    printf("- no more than 6 significant digits\n");
    printf("- a value between + 10**37 and 10**-37\n");

    // Request two floating-point numbers
    printf("Enter Float 1: ");
    scanf("%g", &float_32_s1.floating_value_in_32_bits);
    printf("Enter Float 2: ");
    scanf("%g", &float_32_s2.floating_value_in_32_bits);

    // Print the floating-point numbers in binary format
    print_bits(float_32_s1, "Original pattern of Float 1:");
    print_bits(float_32_s2, "Original pattern of Float 2:");

    // The following generates floating point hardware results:
    // Get the mantissa and exponent components into the helper varibales
    mant_s1 = float_32_s1.f_bits.mantissa;
    mant_s2 = float_32_s2.f_bits.mantissa;
    exp_s1 = float_32_s1.f_bits.exponent;
    exp_s2 = float_32_s2.f_bits.exponent;

    // Check for normalization and slam in the hidden bit if normalized
    if (exp_s1 > 0) mant_s1 |= (1 << 23);
    if (exp_s2 > 0) mant_s2 |= (1 << 23);

    // Shift mantissa of the smaller value for common exponent
    if (exp_s1 < exp_s2) {
        shift_count = exp_s2 - exp_s1;
        if (shift_count > 24) shift_count = 24;
        mant_s1 >>= shift_count;
        exp_res = exp_s2;
    } else if (exp_s1 > exp_s2) {
        shift_count = exp_s1 - exp_s2;
        if (shift_count > 24) shift_count = 24;
        mant_s2 >>= shift_count;
        exp_res = exp_s1;
    }

    // Add the two mantissas and adjust the final mantissa
    mant_res = mant_s1 + mant_s2;
    if (mant_res >> 24 == 1) {
        // case of 10.xx...
        ++exp_res;
        mant_res >>= 1;
    }
    // Extract to rightmost 23 bits as the final mantissa
    mant_res &= 0x7FFFFF;

    // Particularly, if the exponent is 0xFF (1111 1111), the result if overflow
    // Make the mantissa all 0's to represent "infinity"
    if (exp_res == 0xFF) mant_res = 0;

    // Since the two numbers are positive, the sign bit is 0
    float_32_rslt.f_bits.sign = 0;
    float_32_rslt.f_bits.exponent = exp_res;
    float_32_rslt.f_bits.mantissa = mant_res;

    // Hardware result (real value)
    the_hardware_result = float_32_s1.floating_value_in_32_bits + float_32_s2.
                          floating_value_in_32_bits;

    // Print the result
    print_bits(float_32_rslt, bold("Bit pattern of result:      "));
    printf("%s%g\n", bold("EMULATED FLOATING RESULT FROM PRINTF ==>>> "),
           float_32_rslt.floating_value_in_32_bits);
    printf("%s%g", bold("HARDWARE FLOATING RESULT FROM PRINTF ==>>> "), the_hardware_result);

    return 0;
}
