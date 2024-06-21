# Homework 5

## Contact

> Name: Zhuojian Chen (James)  
> ID: 02151380  
> Section: 051  
> Email: Zhuojian_Chen@student.uml.edu

## Description

Degree of Success: 100%

First of all, I discovered that MASM does not allow underscores in labels, which restricts my ability to create label names freely. Additionally, when MASM displays error messages, it shows the ordinal number of the instruction instead of the line number. To address these issues, I updated `masm.c` in homework #4 to support underscores in labels and correct the line number display in error messages. I then compiled `masm_mrd` and used it in homework #5.

Secondly, I refactored `starter_code.asm` to enhance its readability. The updated
`addition.asm` now adheres to the following naming conventions:

* Function labels: PascalCase
* Constant labels: ALL_CAPS
* Variable labels: snake_case

Additionally, all functions are thoroughly commented to improve readability and maintainability. Since `starter_code.asm` already includes the implementation for reading in two positive numbers, I will now elaborate on the process of converting the result of the addition to MIC-1 characters and printing them.

The `ResolveChars` function, found on lines 133 to 145, converts each digit in temp_num (which stores the sum of the two numbers) into its corresponding character representation. Each character is then pushed onto the `res_char` stack (line 219 to 224). Since the maximum number of digits in the result is 5, the stack has a length of 5.

The `Resolve2Chars` function, located on lines 147 to 179, converts these characters into pairs of characters. In MIC-1, a single memory cell is 16 bits wide, allowing it to store two ASCII characters. The final result is stored in chars_arr (lines 226 to 228).

Finally, use the `PrintStr` function to print the `chars_arr` to display the number onto console.

## Available Makefile Targets

~~~shell
make      # Build the `addition.obj` file
make run  # Run the program
~~~

## Resulting Output

The resulting output is available in
`output.txt`, which includes the output of the following additions:

```
235 + 0 = 235
16341 + 957 = 17298
23786 + 12400 = [Overflow]
12 + 23 = 35
1 + 1343 = 1344
```
