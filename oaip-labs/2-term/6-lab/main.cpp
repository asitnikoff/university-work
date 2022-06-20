#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>


template <typename Type>
Type read();
template <typename Type>
Type read(Type, Type);
void clearInputBuffer();
double fun(double);
double getZeroOfFunction(double, double);
void inputParameters(double&, double&, double&, double&);
void findSimpleZerosOfFunction(double, double, double, double);
void findSpecificZerosOfFunction(double, double, double);
double getSpecificZeroOfFunction(double, double);


int main() {
    double a, b, h, eps;

    std::cout << "Before using program you need to input parameters." << std::endl;
    inputParameters(a, b, h, eps);

    while (true) {
        std::cout << "Input new parameters - 0" << std::endl;
        std::cout << "Find simple zeros of function - 1" << std::endl;
        std::cout << "Find specific zeros of function - 2" << std::endl;
        std::cout << "Else - exit" << std::endl;

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 0:
                inputParameters(a, b, h, eps);
                break;
            case 1:
                findSimpleZerosOfFunction(a, b, h, eps);
                break;
            case 2:
                findSpecificZerosOfFunction(a, b, eps);
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


double fun(double x) {
    return (sin(x) * sin(x)) - (x / 5.) - 1;
}


double getZeroOfFunction(double x0, double eps) {
    double x1 = x0 + eps * 10, fun0;
    while (fabs(x0 - x1) > eps) {
        fun0 = fun(x0);
        x1 = x0 - (fun0 * eps / (fun0 - fun(x0 - eps)));

        x0 = x1;
    }

    return x1;
}
double getZeroOfFunctionTat(double x1, double eps) {
    double x0, f0;
    do {
        x0 = x1;
        f0 = fun(x0);
        x1 = x0 - f0 * eps / (f0 - fun(x0 - eps));
    }while (fabs(x0 - x1) > eps);

    return x1;
}


void inputParameters(double& a, double& b, double& h, double& eps) {
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

    std::cout << "Input h: ";
    fflush(stdout);
    h = read<double>();

    std::cout << "Input eps: ";
    fflush(stdout);
    eps = read<double>();
}


void findSimpleZerosOfFunction(double a, double b, double h, double eps) {
    int root_count = 0;
    while (a <= b) {
        if ((fun(a) * fun(a + h)) < 0) {
            ++root_count;
            double zero = getZeroOfFunction(a, eps);
            std::cout << root_count << " simple zero of function: " << zero << " and function is equal " << fun(zero) << std::endl;
        }

        a += h;
    }

    if (root_count == 0) {
        std::cout << "There are no simple zeros of function." << std::endl;
    }
}


void findSpecificZerosOfFunction(double a, double b, double eps) {
    double begin_range;
    bool is_found_begin = false;
    int root_count = 0;
    while (a <= b) {
        double fun_result = fabs(fun(a));
        if (fun_result < eps) {
            is_found_begin = true;
            begin_range = a;
        } else if ((fun_result > eps) && is_found_begin) {
            if (fun(begin_range) * fun(a) < 0) {
                is_found_begin = false;
                continue;
            }
            std::cout << std::setprecision(10) << std::fixed;
            ++root_count;
            double zero = getSpecificZeroOfFunction(begin_range, a);
            std::cout << root_count << " specific zero of function: " << zero << " ";
            std::cout << " and function is equal " << fun(zero) << std::endl;
            is_found_begin = false;
        }
        a += eps;
    }

    if (root_count == 0) {
        std::cout << "There are no specific zeros of function." << std::endl;
    }
}


double getSpecificZeroOfFunction(double left, double right) {
    if (std::min(fun(left), fun(right)) < 0) {
        for (int i = 0; i < 200; ++i) {
            double mid1 = left + ((right - left) / 3.);
            double mid2 = right - ((right - left) / 3.);

            if (fun(mid1) < fun(mid2)) {
                left = mid1;
            } else {
                right = mid2;
            }
        }
    } else {
        for (int i = 0; i < 200; ++i) {
            double mid1 = left + ((right - left) / 3.);
            double mid2 = right - ((right - left) / 3.);

            if (fun(mid1) < fun(mid2)) {
                right = mid2;
            } else {
                left = mid1;
            }
        }
    }

    return left;
}