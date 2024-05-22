# Homework 2

## Contact

> Name: Zhuojian Chen (James)
> 
> ID: 02151380
> 
> Section: 051
> 
> Email: Zhuojian_Chen@student.uml.edu

## Description

I think my degree of success is 100% in this project. To ensure accurate results in adding two positive floating-point numbers, I meticulously followed these steps:

* **Setup**: I enhanced the readability of `main.c` by encapsulating the `float_32` union and two helper functions within `framework.h`. The `float_32` union, `print_bits` function, and the initial segment of the main function were extracted from the supplied "template.txt" file.
* **Adding Hidden Bit**: To check and adjust the exponents of two input float numbers, if their exponents are greater than zero, we can add a 1 to the mantissa. This is done by performing a bitwise OR operation on the mantissa with `1 << 23`.
* **Alignment** Shift mantissa of the smaller value for common exponent. After the alignment, the exponent of the two numbers are equal, and we assign it to `exp_res`.
* **Add Two Mantissa** Perform the addition of the mantissas of the two numbers. After the addition, check if the 25th bit from the right is 1. If the 25th bit is 1, shift the mantissa one bit to the right and increment the `exp-res` by 1. Note that since we are adding two positive numbers, the largest sum of two mantissa can only reach 25 bits.
* **Overflow Solution** Particularly, if the exponent is 0xFF (1111 1111), the result is overflow. According to IEEE standard, we should make the mantissa all 0's to represent "infinity".
* **Print Results** Print the emulated result and the hardware result.

## Build and Testing

I have crafted a complete [Makefile](./Makefile) to streamline testing:

```shell
make        # Build
make run    # Build and run
make clean  # Clean all object files and the executable file
```

All test cases within `test_data.txt` have been passed.

### Resulting Output

A complete resulting output is presented in `resulting_output.txt`. The two input float numbers are `7.491` and `4.617e20`, and the result is `4.617e+20`, which is the same as the hardware result.