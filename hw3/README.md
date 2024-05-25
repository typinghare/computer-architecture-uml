# Homework 3

## Contact

> Name: Zhuojian Chen (James)  
> ID: 02151380  
> Section: 051  
> Email: Zhuojian_Chen@student.uml.edu

## Description

Degree of Success: 100%

I created two versions of recursive solutions for the fibonacci function. The [unoptimized version](rfib_unoptimized.asm) implements the pure recursion. In contrast, the [optimized_version](rfib.asm) combines recursion with memoization to reduce the number of recursive calls.

The unoptimized version modifies some instructions within the `FIB` function in the iteration version. If the argument `n` is neither 0 nor 1, push `(n - 1)` to the stack, then call `FIB` to obtain `fib(n - 1)`, and push the result to the stack. Next, get `n - 2` and call `FIB` again to obtain `fib(n - 2)`. The result will still be in the accumulator right after the invocation, so we use `ADDL 1` to add `fib(n - 1)` and `fib(n - 2)`. Finally, use `INSP 3` to clear the stack.

Based on it, the optimized version creates an array named `memo` to store the results of fibonacci from 0 to 25. The `memo` array is initialized with all `-1`, except for `memo[0] = 0` and `memo[1] = 1`. The `FIB` function is also adjusted: if `memo[n]` is not `-1`, return `memo[n]` directly; otherwise, calculate the fibonacci value for `n`, and store it to `memo[n]` before returning.

The optimization results in a significant improvement. The unoptimized version takes 33,217,509 cycles, whereas the optimized version takes only 8,596 cycles.

~~~bash
make                  # Build the rfib.obj file
make run              # Build and run the optimized version
make run-unoptimized  # Build and run the unoptimized version (will take some time)
~~~

## Resulting Output

The resulting output of the unoptimized version is available in `output_unoptimized.txt`, while the resulting output of the optimized version is available in `output.txt`. The result values in the resulting output are the same as the expected output presented in the homework instructions.