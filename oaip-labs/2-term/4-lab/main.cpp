#include <iostream>

#include "stack.h"
#include "validation.h"


void processOp(StackProperties<double>*&, char, bool&);
bool isOperator(char);
bool isUnaryOperator(char);
int getPriority(char);
double getVariableVal(char**, int, double*, std::string);
void getVariablesFromExpression(std::string, char**&, int&);
void inputVariablesValues(char**, double*&, int);
double toNumber(std::string);
bool isEqual(const char*, std::string);
bool isAlphabet(char);
bool isDigit(char);


int main() {
    std::string expression;

    while (true) {
        std::cout << "Введите выражение: ";
        std::cin >> expression;

        if (isValidExpressionBraces(expression) && isValidExpressionOperators(expression)) {
            break;
        } else {
            std::cout << "Выражение некорректное. Попробуйте заново." << std::endl;
        }
    }

    double* variables_value = nullptr;
    char** variables_name;
    int variables_count = 0;
    getVariablesFromExpression(expression, variables_name, variables_count);

    inputVariablesValues(variables_name, variables_value, variables_count);

    StackProperties<char> *op = nullptr;
    StackProperties<double> *st = nullptr;

    bool is_ok = true;
    bool is_may_unary = true;
    for (int i = 0; i < (int)expression.size(); ++i) {
        if (expression[i] == ' ') {
            continue;
        }
        if (expression[i] == '(') {
            pushStack<char>(op, '(');
            is_may_unary = true;
        } else if (expression[i] == ')') {
            while (topStack(op) != '(') {
                processOp(st, topStack(op), is_ok);
                popStack(op);
            }
            popStack(op);
            is_may_unary = false;
        } else if (isOperator(expression[i])) {
            char current_operator = expression[i];

            if (is_may_unary && isUnaryOperator(current_operator)) {
                current_operator = -current_operator;
            }

            while (!isEmptyStack(op) && (getPriority(topStack(op)) >= getPriority(current_operator))) {
                if ((topStack(op) == '/') && (topStack(st) == 0)) {
                    for (int i = 0; i < variables_count; ++i) {
                        delete[] variables_name[i];
                    }
                    delete[] variables_name;
                    delete[] variables_value;
                    clearStack(st);
                    clearStack(op);
                    return 0;
                }
                processOp(st, topStack(op), is_ok);
                popStack(op);
            }
            pushStack<char>(op, current_operator);
            is_may_unary = false;
        } else {
            std::string operand;
            while ((i < (int)expression.length()) && (isAlphabet(expression[i]) || isDigit(expression[i]))) {
                operand += expression[i];
                ++i;
            }
            --i;

            if (!operand.empty() && (operand[0] >= '0') && (operand[0] <= '9')) {
                pushStack<double>(st, toNumber(operand));
            } else {
                pushStack<double>(st, getVariableVal(variables_name, variables_count, variables_value, operand));
            }
            is_may_unary = false;
        }
    }

    while (!isEmptyStack(op)) {
        processOp(st, topStack(op), is_ok);
        if (!is_ok) {
            break;
        }
        popStack(op);
    }

    if (is_ok) {
        std::cout << "Result -> " << topStack(st) << std::endl;
    }

    for (int i = 0; i < variables_count; ++i) {
        delete[] variables_name[i];
    }
    delete[] variables_name;
    delete[] variables_value;
    clearStack(st);
    clearStack(op);

    return 0;
}


void processOp(StackProperties<double>*& st, char op, bool& is_ok) {
    if (op < 0) {
        double lt = topStack(st);
        popStack(st);

        switch (-op) {
            case '+':
                pushStack<double>(st, lt);
                break;
            case '-':
                pushStack<double>(st, -lt);
                break;
        }
    } else {
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
                if (rt == 0) {
                    is_ok = false;
                    std::cout << "Нельзя делить на 0!" << std::endl;
                    return;
                }
                pushStack<double>(st, lt / rt);
                break;
        }
    }
}


bool isOperator(char op) {
    return ((op == '+') || (op == '-') || (op == '*') || (op == '/'));
}


bool isUnaryOperator(char op) {
    return ((op == '+') || (op == '-'));
}


int getPriority(char op) {
    if (op < 0) {
        return 3;
    }
    return ((op == '*') || (op == '/')) ? 2 :
           ((op == '+') || (op == '-')) ? 1 : -1;
}


double getVariableVal(char** variables_name, int variables_count, double* variables_value, std::string operand) {
    for (int i = 0; i < variables_count; ++i) {
        if (isEqual(variables_name[i], operand)) {
            return variables_value[i];
        }
    }
    return -1;
}


bool isEqual(const char* str1, std::string str2) {
    int i = 0;
    while ((str1[i] != '\0') && (i < (int)str2.size()) && (str1[i] == str2[i])) {
        ++i;
    }

    return ((str1[i] == '\0') && (i == (int)str2.size()));
}


void inputVariablesValues(char** variables_name, double*& variables_value, int variables_count) {
    variables_value = new double[variables_count];
    for (int i = 0; i < variables_count; ++i) {
        std::cout << "Input value of variable \"" << variables_name[i] << "\": ";
        fflush(stdout);
        variables_value[i] = read<double>();
    }
}


double toNumber(std::string operand) {
    double result = 0;
    for (int i = 0; i < (int)operand.size(); ++i) {
        (result *= 10) += (operand[i] - '0');
    }

    for (int i = 0; i < (int)operand.size(); ++i) {
        if (operand[i] == '.') {
            result /= 10 * ((int)operand.size() - i - 1);
        }
    }

    return result;
}


void getVariablesFromExpression(std::string expression, char**& variables_name, int& variables_count) {
    for (int i = 0; i < (int)expression.size(); ++i) {
        if (isAlphabet(expression[i])) {
            while ((i < (int)expression.length()) && isAlphabet(expression[i])) {
                ++i;
            }
            --i;

            variables_count++;
        }
    }

    variables_name = new char*[variables_count];
    variables_count = 0;
    for (int i = 0; i < (int)expression.size(); ++i) {
        if (isAlphabet(expression[i])) {
            std::string operand;
            while ((i < (int)expression.length()) && isAlphabet(expression[i])) {
                operand += expression[i];
                ++i;
            }
            --i;

            variables_name[variables_count] = new char[(int)operand.size() + 1];
            for (int j = 0; j < (int)operand.size(); ++j) {
                variables_name[variables_count][j] = operand[j];
            }
            variables_name[variables_count][(int)operand.size()] = '\0';
            ++variables_count;
        }
    }
}


bool isAlphabet(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}


bool isDigit(char c) {
    return ((c >= '0') && (c <= '9'));
}