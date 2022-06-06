#include <iostream>

#include "validation.h"

#define TRY_AGAIN "Попробовать снова? (1 - да, остальное - нет)"


int readInt(int left_range, int right_range) {
    int temp;
    std::cin >> temp;
    bool isGood = (std::cin.get() == '\n');

    if (isGood && (temp >= left_range) && (temp <= right_range)) {
        return temp;
    }
    return (left_range - 1);
}

bool isTryAgain() {
    std::cout << TRY_AGAIN << std::endl;
    int choice;
    std::cin >> choice;
    return (choice == 1);
}