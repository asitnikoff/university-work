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