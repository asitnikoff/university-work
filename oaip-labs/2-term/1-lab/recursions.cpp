#include "recursions.h"

long long calcRecursionBinPow(int x, int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return x;
    }
    if (n & 1) {
        return (x * calcRecursionBinPow(x, n - 1));
    }
    return (calcRecursionBinPow(x, n / 2) * (calcRecursionBinPow(x, n / 2)));
}


long long calcSimplePow(int x, int n) {
    long long result = 1;
    while (n > 0) {
        result *= x;
        --n;
    }
    return result;
}


long long calcIterativeBinPow(int x, int n) {
    long long result = 1;
    while (n > 0) {
        if (n & 1) {
            result *= x;
        }
        x *= x;
        n >>= 1;
    }
    return result;
}