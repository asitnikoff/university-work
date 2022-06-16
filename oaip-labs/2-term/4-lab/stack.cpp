#include <iostream>

#include "stack.h"


template <typename T>
void pushStack(StackProperties<T>*& stack, T value) {
    auto *tmp = new StackProperties<T>();
    tmp->info = value;
    tmp->next = stack;
    stack = tmp;
}
template void pushStack<double>(StackProperties<double>*&, double);
template void pushStack<char>(StackProperties<char>*&, char);

template <typename T>
void popStack(StackProperties<T>*& stack) {
    StackProperties<T> *tmp = stack;
    stack = stack->next;
    tmp->next = nullptr;
    delete tmp;
}
template void popStack<double>(StackProperties<double>*&);
template void popStack<char>(StackProperties<char>*&);

template <typename T>
T topStack(StackProperties<T>*& stack) {
    return stack->info;
}
template double topStack<double>(StackProperties<double>*&);
template char topStack<char>(StackProperties<char>*&);

template <typename T>
bool isEmptyStack(StackProperties<T>*& stack) {
    return (stack == nullptr);
}
template bool isEmptyStack<char>(StackProperties<char>*&);

template <typename T>
void clearStack(StackProperties<T>*& stack) {
    while (stack != nullptr) {
        popStack(stack);
    }
    std::cout << "Стек очищен!" << std::endl;
}
template void clearStack<double>(StackProperties<double>*&);
template void clearStack<char>(StackProperties<char>*&);