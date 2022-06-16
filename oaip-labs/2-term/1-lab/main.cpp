#include <iostream>
#include <limits>

#include "recursions.h"


template <typename Type>
Type read();
void clearInputBuffer();
void inputParameters(double&, int&, bool&);


int main() {
    bool is_parameters_entered = false;
    double x;
    int n;

    std::cout << "This program calculates x^n." << std::endl;

    while (true) {
        std::cout << "Input paramaters - 0" << std::endl;
        std::cout << "Recursion binary pow - 1" << std::endl;
        std::cout << "Simple pow - 2" << std::endl;
        std::cout << "Iterative binary pow - 3" << std::endl;
        std::cout << "Print all - 4" << std::endl;
        std::cout << "Exit - another key" << std::endl;
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;

        if (!is_parameters_entered && (choice >= 1) && (choice <= 4)) {
            std::cout << "You must input parameters first!";
            inputParameters(x, n, is_parameters_entered);
        }

        switch (choice) {
            default:
                std::cout << "Bye!\n";
                return 0;
            case 0:
                inputParameters(x, n, is_parameters_entered);
                break;
            case 1:
                std::cout << "Recursion result = " << calcRecursionBinPow(x, n) << "\n";
                break;
            case 2:
                std::cout << "Simple result = " << calcSimplePow(x, n) << "\n";
                break;
            case 3:
                std::cout << "Iterative result = " << calcIterativeBinPow(x, n) << "\n";
                break;
            case 4:
                std::cout << "Recursion result = " << calcRecursionBinPow(x, n) << "\n";
                std::cout << "Simple result = " << calcSimplePow(x, n) << "\n";
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


void inputParameters(double& x, int& n, bool& is_parameters_entered) {
    std::cout << "Input x: ";
    x = read<double>();

    std::cout << "Input n: ";
    n = read<int>();

    is_parameters_entered = true;
}