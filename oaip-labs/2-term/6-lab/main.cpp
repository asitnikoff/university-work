#include <iostream>
#include <cmath>
#include <limits>


template <typename Type>
Type read();
void clearInputBuffer();
double fun(double);
double getZeroOfFunction(double, double, double);
void inputParameters(double&, double&, double&, double&);
void findZerosOfFunction(double, double, double, double);


int main() {
    double a, b, eps, h;

    while (true) {
        std::cout << "Input new parameters - 0" << std::endl;
        std::cout << "Find zeros of function - 1" << std::endl;
        std::cout << "Else - exit" << std::endl;

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 0:
                inputParameters(a, b, eps, h);
                break;
            case 1:
                findZerosOfFunction(a, b, eps, h);
                break;
            default:
                std::cout << "Bye!" << std::endl;
                return 0;
        }
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


double fun(double x) {
    return (sin(x) * sin(x)) - (x / 5.0) - 1;
}


double getZeroOfFunction(double x0, double x1, double eps) {
    double x2, fun1;
    while (fabs(x0 - x1) > eps) {
        fun1 = fun(x1);
        x2 = x1 - ((x1 - x0) / (fun1 - fun(x0))) * fun1;

        x0 = x1;
        x1 = x2;
    }

    return x1;
}


void inputParameters(double& a, double& b, double& eps, double& h) {
    std::cout << "Input a: ";
    fflush(stdout);
    a = read<double>();

    std::cout << "Input b: ";
    fflush(stdout);
    b = read<double>();

    std::cout << "Input eps: ";
    fflush(stdout);
    eps = read<double>();

    std::cout << "Input h: ";
    fflush(stdout);
    h = read<double>();
}


void findZerosOfFunction(double a, double b, double eps, double h) {
    while ((a + h) <= b) {
        if ((fun(a) * fun(a + h)) < 0) {
            std::cout << "Zero of function: " << getZeroOfFunction(a, a + h, eps) << std::endl;
        }

        a += h;
    }
}