#include <iostream>


int n, m;
double a, b;


int main() {
    std::cout << "Input a: ";
    fflush(stdout);
    std::cin >> a;

    std::cout << "Input b: ";
    fflush(stdout);
    std::cin >> b;

    std::cout << "Input m: ";
    fflush(stdout);
    std::cin >> m;

    std::cout << "Input n: ";
    fflush(stdout);
    std::cin >> n;

    double h1 = (b - a) / m;
    double h2 = (b - a) / n;

    double x1 = a;
    double x2 = a;

    while (!(x2 > b)) {
        

        x2 += h2;
        while ((x1 + (2. * h1)) < x2) {
            x1 += h1;
        }
    }
}
