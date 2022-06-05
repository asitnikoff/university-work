#include "stack.h"


template <typename T>
Stack<T>::Stack() {
    head_ = nullptr;
}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(T value) {
    auto *tmp = new StackProperties<T>();
    tmp->info = value;
    tmp->next = head_;
    head_ = tmp;
}

template <typename T>
void Stack<T>::pop() {
    StackProperties<T> *tmp = head_;
    head_ = head_->next;
    delete *tmp;
}

template <typename T>
T Stack<T>::top() {
    return head_->info;
}

template <typename T>
bool Stack<T>::empty() {
    return (head_ == nullptr);
}

template <typename T>
void Stack<T>::clear() {
    while (head_ != nullptr) {
        pop();
    }
}