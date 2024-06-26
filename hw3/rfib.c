#include <stdio.h>

int rfib(int arg);

int fib_invocation_count = 0;
int memo[26] = {0, 1};

int main(void) {
    for (int i = 2; i < 26; ++i) memo[i] = -1;

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

    if (memo[arg] >= 0) {
        return memo[arg];
    }

    const int fn1 = rfib(arg - 1);
    const int fn2 = rfib(arg - 2);
    memo[arg] = fn1 + fn2;

    return memo[arg];
}
