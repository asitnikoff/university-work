#include <iostream>
#include <limits>
#include <cmath>


template <typename Type>
Type read();
template <typename Type>
Type read(int);
void clearInputBuffer();
double fun(double);
void inputParameters(double&, double&, int&, int&, double*&);
void generateTable(double, double, int, double*&);
void showTable(double* const&, const int&);
void calcFunctionApproximation(double, double, int, double* const&);
double getN2(double, double, double, double);


int main() {
    double a, b;
    int n, m;
    double* table_values = nullptr;

    std::cout << "Before using program you need to input parameters." << std::endl;
    inputParameters(a, b, n, m, table_values);

    while (true) {
        std::cout << "Input new parameters - 0" << std::endl;
        std::cout << "Calc function approximation - 1" << std::endl;
        std::cout << "Else - exit" << std::endl;

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 0:
                inputParameters(a, b, n, m, table_values);
                break;
            case 1:
                calcFunctionApproximation(a, b, n, table_values);
                break;
            default:
                std::cout << "Bye!" << std::endl;
                delete[] table_values;
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


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


double fun(double x) {
    return (sin(x) * sin(x)) - (x / 5.0);
}


void inputParameters(double& a, double& b, int& n, int& m, double*& table_values) {
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

    std::cout << "Input m: ";
    fflush(stdout);
    m = read<int>(0);

    std::cout << "Input n: ";
    fflush(stdout);
    n = read<int>(0);

    generateTable(a, b, m, table_values);
    showTable(table_values, m);
}


void generateTable(double a, double b, int m, double*& table_values) {
    double h = (b - a) / (double)(m - 1);

    delete[] table_values;
    table_values = new double[m];
    table_values[0] = a;
    for (int i = 1; i < m; ++i) {
        table_values[i] = table_values[i - 1] + h;
    }
}


void showTable(double* const& table_values, const int& m) {
    std::cout << std::endl;
    std::cout << "Table:" << std::endl;
    for (int i = 0; i < m; ++i) {
        std::cout << (i + 1) << " -> [x = " << table_values[i] << "] && [f(x) = " << fun(table_values[i]) << "]" << std::endl;
    }
    std::cout << std::endl;
}


void calcFunctionApproximation(double x, double b, int n, double* const& table_values) {
    double h = (b - x) / (n - 1);

    int ptr = 0, cnt = 0;
    while (x <= b) {
        ++cnt;
        double res1 = fun(x);
        double res2 = getN2(x, table_values[ptr], table_values[ptr + 1], table_values[ptr + 2]);
        std::cout << cnt << " -> [f(x) = " << res1 << "] && [f*(x) = " << res2 << "] && ";
        std::cout << "[diff = " << fabs(res1 - res2) << "]" << std::endl;

        x += h;
        if (x > b) {
            break;
        }
        while (table_values[ptr + 2] < x) {
            ++ptr;
        }
    }
    std::cout << std::endl;
}


double getN2(double xt, double x_prev, double x_cur, double x_next) {
    double fun_x_prev = fun(x_prev);
    double fun_x_cur = fun(x_cur);
    double diff_xt_x_prev = xt - x_prev;

    double n1 = fun_x_prev + diff_xt_x_prev * ((fun_x_cur - fun_x_prev) / (x_cur - x_prev));

    return n1 + diff_xt_x_prev * (xt - x_cur) *
            ((((fun_x_prev - fun_x_cur) / (x_prev - x_cur)) - ((fun_x_cur - fun(x_next)) / (x_cur - x_next))) /
            (x_prev - x_next));
}