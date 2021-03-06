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
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
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
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
        }
        else if (!((x >= left) && (x <= right))) {
            std::cout << "Число не удовлетворяет отрезку. Попробуйте снова." << std::endl;
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