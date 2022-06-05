#include <iostream>
#include <limits>

#include "recursions.h"


template <typename Type>
Type read();
void clearInputBuffer();


int main() {
    while (true) {
        std::cout << "Input x:" << std::endl;
        int x = read<int>();

        std::cout << "Input n:" << std::endl;
        int n = read<int>();

        std::cout << "Recursion binary pow - 1" << std::endl;
        std::cout << "Simple pow - 2" << std::endl;
        std::cout << "Iterative binary pow - 3" << std::endl;
        std::cout << "Exit - another key" << std::endl;
        std::cout << "Choose option: ";
        char choice;
        std::cin >> choice;

        switch (choice) {
            default:
                system("pause");
                return 0;
            case '1':
                std::cout << "Recursion result = " << calcRecursionBinPow(x, n) << "\n";
                break;
            case '2':
                std::cout << "Simple result = " << calcSimplePow(x, n) << "\n";
                break;
            case '3':
                std::cout << "Iterative result = " << calcIterativeBinPow(x, n) << "\n";
                break;
        }
        std::cout << std::endl;
    }
}


template <typename Type>
Type read() {
    Type x;
    while (true) {
//        std::cin.clear();
//        std::cin.ignore(10, '\n');

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


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}