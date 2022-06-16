#include <iostream>

#include "stack.h"
#include "validation.h"


void processOp(StackProperties<double>*&, char);
bool isOperator(char);
int getPriority(char);
double getVariableVal(double*, char);


int main() {
    std::cout << "Введите выражение: ";
    std::string expression;
    std::cin >> expression;

    double* variables = new double[5];
    for (int i = 0; i < 5; ++i) {
        std::cin >> variables[i];
    }

    StackProperties<char> *op = nullptr;
    StackProperties<double> *st = nullptr;
    for (int i = 0; i < (int)expression.size(); ++i) {
        if (expression[i] == '(') {
            pushStack<char>(op, '(');
        } else if (expression[i] == ')') {
            while (topStack(op) != '(') {
                processOp(st, topStack(op));
                popStack(op);
            }
            popStack(op);
        } else if (isOperator(expression[i])) {
            char current_operator = expression[i];
            while (!isEmptyStack(op) && (getPriority(topStack(op)) >= getPriority(current_operator))) {
                processOp(st, topStack(op));
                popStack(op);
            }
            pushStack<char>(op, current_operator);
        } else {
            pushStack<double>(st, getVariableVal(variables, expression[i]));
        }
    }

    while (!isEmptyStack(op)) {
        processOp(st, topStack(op));
        popStack(op);
    }

    std::cout << "Result -> " << topStack(st) << std::endl;

    delete[] variables;
    clearStack(st);
    clearStack(op);

    return 0;
}


void processOp(StackProperties<double>*& st, char op) {
    double rt = topStack(st);
    popStack(st);

    double lt = topStack(st);
    popStack(st);

    switch (op) {
        case '+':
            pushStack<double>(st, lt + rt);
            break;
        case '-':
            pushStack<double>(st, lt - rt);
            break;
        case '*':
            pushStack<double>(st, lt * rt);
            break;
        case '/':
            pushStack<double>(st, lt / rt);
            break;
    }
}


bool isOperator(char op) {
    return ((op == '+') || (op == '-') || (op == '*') || (op == '/'));
}


int getPriority(char op) {
    return ((op == '*') || (op == '/')) ? 2 :
           ((op == '+') || (op == '-')) ? 1 : -1;
}


double getVariableVal(double* variables, char variable) {
    for (int i = 0; i < 5; ++i) {
        if ((char)(i + 'a') == variable) {
            return variables[i];
        }
    }
    return 0;
}