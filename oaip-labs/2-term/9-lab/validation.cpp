#include <iostream>
#include <limits>

#include "validation.h"


template <typename Type>
Type read() {
    Type x;
    while (true) {
        std::cin >> x;
        if (std::cin.get() != '\n') {
            clearInputBuffer();
            std::cout << "Invalid input. Please, try again." << std::endl;
        }
        else {
            break;
        }
    }
    return x;
}
template int read<int>();

template <typename Type>
Type read(Type left, Type right) {
    Type x;
    while (true) {
        std::cin >> x;
        if (std::cin.get() != '\n') {
            clearInputBuffer();
            std::cout << "Invalid input. Please, try again." << std::endl;
        }
        else if ((x < left) || (x > right)) {
            std::cout << "Number not in range. Please, try again." << std::endl;
        } else {
            break;
        }
    }
    return x;
}
template int read<int>(int left, int right);


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}





void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool inputInt(int& x) {
    scanf_s("%d", &x);

    if (getchar() != '\n') {
        printf("Wrong input!\n");
        clearBuffer();
        return false;
    }
    return true;
}


bool inputStr(char* x) {
    scanf_s("%s", x, 1000);

    if (getchar() != '\n') {
        printf("Wrong input!\n");
        clearBuffer();
        return false;
    }
    return true;
}


bool isCorrectPosition(int position, int left, int right) {
    if ((position >= left) && (position <= right)) {
        return 1;
    }
    printf("Incorrect position range!\n");
    return 0;
}