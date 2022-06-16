#include "recursions.h"

double calcRecursionBinPow(double x, int n) {
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


double calcSimplePow(double x, int n) {
    double result = 1;
    while (n > 0) {
        result *= x;
        --n;
    }
    return result;
}


double calcIterativeBinPow(double x, int n) {
    double result = 1;
    while (n > 0) {
        if (n & 1) {
            result *= x;
        }
        x *= x;
        n >>= 1;
    }
    return result;
}