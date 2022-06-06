#include <iostream>

#include "stack.h"


void pushStack(StackProperties*& stack,int value) {
    auto *tmp = new StackProperties();
    tmp->info = value;
    tmp->next = stack;
    stack = tmp;
}

void popStack(StackProperties*& stack) {
    StackProperties *tmp = stack;
    stack = stack->next;
    tmp->next = nullptr;
    delete tmp;
}

int topStack(const StackProperties*& stack) {
    return stack->info;
}

bool isEmptyStack(StackProperties*& stack) {
    return (stack == nullptr);
}

void clearStack(StackProperties*& stack) {
    while (stack != nullptr) {
        popStack(stack);
    }
    std::cout << "Стек очищен!" << std::endl;
}

void showStack(StackProperties*& stack) {
    std::cout << "Stack elements:";
    fflush(stdout);

    StackProperties *tmp = stack;
    while (tmp != nullptr) {
        std::cout << " [" << tmp->info << "]";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}


StackProperties* getMinElementStack(StackProperties* stack) {
    StackProperties *ret = stack;
    stack = stack->next;

    while (stack != nullptr) {
        if (stack->info < ret->info) {
            ret = stack;
        }
        stack = stack->next;
    }

    return ret;
}


StackProperties* getMaxElementStack(StackProperties* stack) {
    StackProperties *ret = stack;
    stack = stack->next;

    while (stack != nullptr) {
        if (stack->info > ret->info) {
            ret = stack;
        }
        stack = stack->next;
    }

    return ret;
}


bool isEarlyStack(StackProperties* first_element, StackProperties* second_element, StackProperties* stack) {
    while (stack != second_element) {
        if (stack == first_element) {
            return true;
        }

        stack = stack->next;
    }
    return false;
}


void swapElementsStack(StackProperties*& first_element, StackProperties*& second_element) {
    StackProperties *tmp = first_element;
    first_element = second_element;
    second_element = tmp;
}


void sortStack(StackProperties*& stack) {
    std::cout << "Sort stack." << std::endl;
}