#ifndef LAB_STACK_H
#define LAB_STACK_H

template <typename T>
struct StackProperties {
    T info;
    StackProperties<T> *next;
};


template <typename T>
class Stack {
private:
    StackProperties<T> *head_;
public:
    Stack();
    ~Stack();

    void push(T value);
    void pop();
    T top();
    bool empty();
    void clear();
}


#endif