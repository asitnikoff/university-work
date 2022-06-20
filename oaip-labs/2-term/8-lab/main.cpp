#include <iostream>
#include <cmath>
#include <limits>


double fun(double);
template <typename Type>
Type read();
template <typename Type>
Type read(int);
template <typename Type>
Type read(Type, Type);
void clearInputBuffer();
void inputParameters(double&, double&, int&, double&);
void calcIntegral(double, double, int, double);
double calcIntegralByPartition(double, double, int);
double calcIntegralByEpsilon(double, double, double);


int main() {
    double a, b, eps;
    int n;

    std::cout << "Before using program you need to input parameters." << std::endl;
    inputParameters(a, b, n, eps);

    while (true) {
        std::cout << "Input new parameters - 0" << std::endl;
        std::cout << "Calc integral - 1" << std::endl;
        std::cout << "Else - exit" << std::endl;

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 0:
                inputParameters(a, b, n, eps);
                break;
            case 1:
                calcIntegral(a, b, n, eps);
                break;
            default:
                std::cout << "Bye!" << std::endl;
                return 0;
        }
    }
}


double fun(double x) {
    return (sin(x) * sin(x)) - (x / 5.);
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


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void inputParameters(double& a, double& b, int& n, double& eps) {
    do {
        std::cout << "Input a: ";
        fflush(stdout);
        a = read<double>();

        std::cout << "Input b: ";
        fflush(stdout);
        b = read<double>();

        if (a > b) {
            std::cout << "Parameter \"a\" must be not more than \"b\". Please, try again." << std::endl;
        } else {
            break;
        }
    } while (a > b);

    std::cout << "Input n: ";
    fflush(stdout);
    n = read<int>(0);

    std::cout << "Input eps: ";
    fflush(stdout);
    eps = read<double>();
}


void calcIntegral(double a, double b, int n, double eps) {
    std::cout << "Integral by partition: " << calcIntegralByPartition(a, b, n) << std::endl;
    std::cout << calcIntegralByEpsilon(a, b, eps) << std::endl;
    std::cout << std::endl;
}


double calcIntegralByPartition(double a, double b, int n) {
    double h = (b - a) / (double)n;

    double result = (fun(a) + fun(b)) / 2.;

    for (int i = 1; i < n; ++i) {
        a += h;
        result += fun(a);
    }

    return result * h;
}


double calcIntegralByEpsilon(double a, double b, double eps) {
    int n = 1;
    double res1 = calcIntegralByPartition(a, b, n);

    while (true) {
        n <<= 1;
        double res2 = calcIntegralByPartition(a, b, n);

        if (fabs(res1 - res2) < eps) {
            break;
        }

        res1 = res2;
    }

    std::cout << "Integral by epsilon was calculated with " << (n >> 1) << " partitions: " << std::endl;
    return res1;
}