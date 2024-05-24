#include <stdio.h>

int ifib(int arg);

int main(void) {
    int results[5], i;
    const int data[] = {3, 9, 18, 23, 25};
    const int ndata = 5;

    for (i = 0; i < ndata; ++i) {
        printf("\ncalling fib with %d\n", data[i]);
        results[i] = ifib(data[i]);
        printf(" called fib with %d, result is %d\n", data[i], results[i]);
    }

    printf("\nFibonacci numbers:\n");
    for (i = 0; i < ndata; ++i) {
        printf("   FIB of %d\t is %d\n", data[i], results[i]);
    }

    return 0;
}

int ifib(const int arg) {
    if (arg == 0) return 0;
    if (arg == 1) return 1;

    int fm1 = 1;
    int fm2 = 0;
    int tmp = 0;
    for (int lpcnt = arg - 1; lpcnt > 0; --lpcnt) {
        tmp = fm1 + fm2;
        fm2 = fm1;
        fm1 = tmp;
    }

    return tmp;
}
