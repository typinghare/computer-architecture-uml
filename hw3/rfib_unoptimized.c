#include <stdio.h>

int rfib(int arg);

int fib_invocation_count = 0;

int main(void) {
    int results[5], i;
    const int data[] = {3, 9, 18, 23, 25};
    const int ndata = 5;

    for (i = 0; i < ndata; ++i) {
        printf("\ncalling fib with %d\n", data[i]);
        results[i] = rfib(data[i]);
        printf(" called fib with %d, result is %d\n", data[i], results[i]);
    }

    printf("\nFibonacci numbers:\n");
    for (i = 0; i < ndata; ++i) {
        printf("   FIB of %d\t is %d\n", data[i], results[i]);
    }

    printf("The number of times of invoking the fib function: %d\n", fib_invocation_count);

    return 0;
}

int rfib(const int arg) {
    fib_invocation_count++;

    if (arg == 0) return 0;
    if (arg == 1) return 1;

    const int fn1 = rfib(arg - 1);
    const int fn2 = rfib(arg - 2);

    return fn1 + fn2;
}
