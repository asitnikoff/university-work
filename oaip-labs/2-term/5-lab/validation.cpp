#include <iostream>

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
Type read(int left) {
    Type x;
    while (true) {
        std::cin >> x;
        if (std::cin.get() != '\n') {
            clearInputBuffer();
            std::cout << "Invalid input. Please, try again." << std::endl;
        }
        else if (x <= left) {
            std::cout << "Parameter must be a positive integer. Please, try again." << std::endl;
        } else {
            break;
        }
    }
    return x;
}
template int read<int>(int left);


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}