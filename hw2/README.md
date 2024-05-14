# Homework 2

## Description

I think my degree of success is 100% in this project. To ensure accurate results in adding two positive floating-point numbers, I meticulously followed these steps:

* **Setup**: I enhanced the readability of `main.c` by encapsulating the `float_32` union and two helper functions within `framework.h`. The `float_32` union, `print_bits` function, and the initial segment of the main function were extracted from the supplied "template.txt" file.
* 

I have crafted a complete Makefile to streamline testing. Simply execute the command below to compile and run the program:

```shell
make run
```

## Resulting Output

A complete resulting output is presented in `resulting_output.txt`. The two input float numbers are `7.491` and `4.617e20`, and the result is `4.617e+20`, which is the same as the hardware result.