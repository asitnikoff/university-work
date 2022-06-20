#include <iostream>

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
template double read<double>();


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


bool isValidExpressionBraces(std::string expression) {
    int balance = 0;
    for (int i = 0; i < (int)expression.size(); ++i) {
        if (expression[i] == '(') {
            ++balance;
        } else if (expression[i] == ')') {
            --balance;
        }
        if (balance < 0) {
            return false;
        }
    }
    return (balance == 0);
}


bool isOperatorInValidation(char c) {
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}


bool isValidExpressionOperators(std::string expression) {
    for (int i = 0; (i + 1) < (int)expression.size(); ++i) {
        if (isOperatorInValidation(expression[i]) && isOperatorInValidation(expression[i + 1])) {
            return false;
        }
    }
    return !expression.empty() && (!isOperatorInValidation(expression[0]) || (expression[0] == '-')) &&
           !isOperatorInValidation(expression[(int)expression.size() - 1]);
}
