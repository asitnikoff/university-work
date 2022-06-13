#include <iostream>
#include <cmath>


double a, b, eps, h;


double fun(double);
double getZeroOfFunction(double, double, double);


int main() {
    std::cout << "Input a: ";
    fflush(stdout);
    std::cin >> a;

    std::cout << "Input b: ";
    fflush(stdout);
    std::cin >> b;

    std::cout << "Input eps: ";
    fflush(stdout);
    std::cin >> eps;

    std::cout << "Input h: ";
    fflush(stdout);
    std::cin >> h;

    while (!((a + h) > b)) {
        if ((fun(a) * fun(a + h)) < 0) {
            std::cout << "zero of function: " << getZeroOfFunction(a, a + h, eps) << std::endl;
        }

        a += h;
    }

    return 0;
}


double fun(double x) {
    return (sin(x) * sin(x)) - (x / 5.0) - 1;
}


double getZeroOfFunction(double a, double b, double eps) {
    double x0 = a, x1 = b, x2;
    while (fabs(x0 - x1) > eps) {
        x2 = x1 - ((x1 - x0) / (fun(x1) - fun(x0))) * fun(x1);

        x0 = x1;
        x1 = x2;
    }

    return x1;
}