#ifndef LAB_STACK_H
#define LAB_STACK_H


template <typename T>
struct StackProperties {
    T info;
    StackProperties<T> *next;
};


template <typename T>
void pushStack(StackProperties<T>*&, T);
template <typename T>
void popStack(StackProperties<T>*&);
template <typename T>
T topStack(StackProperties<T>*&);
template <typename T>
bool isEmptyStack(StackProperties<T>*&);
template <typename T>
void clearStack(StackProperties<T>*&);


#endif