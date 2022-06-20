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

void clearStack(StackProperties*& stack) {
    while (stack != nullptr) {
        popStack(stack);
    }
    std::cout << "Стек очищен!" << std::endl;
}

int topStack(const StackProperties*& stack) {
    return stack->info;
}

bool isEmptyStack(StackProperties*& stack) {
    return (stack == nullptr);
}

void showStack(StackProperties* stack) {
    std::cout << "Элементы стека:";
    fflush(stdout);

    while (stack != nullptr) {
        std::cout << " [" << stack->info << "]";
        stack = stack->next;
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


bool isEarlyStack(StackProperties* first_element, StackProperties* second_element) {
    while (first_element != nullptr) {
        if (first_element == second_element) {
            return true;
        }

        first_element = first_element->next;
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