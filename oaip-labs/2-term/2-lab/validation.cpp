#include "validation.h"


int readInt(int left_range, int right_range) {
    int temp;
    std::cin >> temp;
    bool isGood = (std::cin.get() == '\n');

    if (isGood && (temp >= left_range) && (temp <= right_range)) {
        return temp;
    }
    return (left_range - 1);
}