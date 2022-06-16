#include <iostream>

#include "double-linked-list.h"
#include "validation.h"


void pushBeginList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end, int value) {
    if (list_begin == nullptr) {
        list_begin = new DoubleLinkedListProperties();
        list_begin->info = value;
        list_begin->next = list_begin->prev = nullptr;

        list_end = list_begin;
    } else {
        auto *tmp = new DoubleLinkedListProperties();
        tmp->info = value;
        tmp->prev = nullptr;
        tmp->next = list_begin;
        list_begin->prev = tmp;

        list_begin = tmp;
    }
}


void pushEndList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end, int value) {
    if (list_end == nullptr) {
        list_end = new DoubleLinkedListProperties();
        list_end->info = value;
        list_end->next = list_end->prev = nullptr;

        list_begin = list_end;
    } else {
        auto *tmp = new DoubleLinkedListProperties();
        tmp->info = value;
        tmp->next = nullptr;
        tmp->prev = list_end;
        list_end->next = tmp;

        list_end = tmp;
    }
}


void popBeginList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end) {
    if (list_begin->next == nullptr) {
        delete list_begin;
        list_begin = list_end = nullptr;
    } else {
        DoubleLinkedListProperties *tmp = list_begin;
        list_begin = list_begin->next;
        tmp->next = nullptr;
        delete tmp;
        list_begin->prev = nullptr;
    }
}


void popEndList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end) {
    if (list_end->prev == nullptr) {
        delete list_end;
        list_begin = list_end = nullptr;
    } else {
        DoubleLinkedListProperties *tmp = list_end;
        list_end = list_end->prev;
        tmp->prev = nullptr;
        delete tmp;
        list_end->next = nullptr;
    }
}


int getBeginList(const DoubleLinkedListProperties *&list_begin) {
    return list_begin->info;
}


int getEndList(const DoubleLinkedListProperties *&list_end) {
    return list_end->info;
}


bool isEmptyList(DoubleLinkedListProperties *&list) {
    return (list == nullptr);
}


void clearList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end) {
    while (list_begin != nullptr) {
        popBeginList(list_begin, list_end);
    }
}


void swapElementsList(DoubleLinkedListProperties *&first_element, DoubleLinkedListProperties *&second_element) {
    DoubleLinkedListProperties *tmp = first_element;
    first_element = second_element;
    second_element = tmp;
}


bool isEarlyList(DoubleLinkedListProperties *first_element, DoubleLinkedListProperties *second_element, DoubleLinkedListProperties *list) {
    while (list != second_element) {
        if (list == first_element) {
            return true;
        }

        list = list->next;
    }
    return false;
}


void showListFromBegin(DoubleLinkedListProperties *list_begin) {
    std::cout << "Список элементов с начала:";
    fflush(stdout);

    while (list_begin != nullptr) {
        std::cout << " [" << list_begin->info << "]";
        list_begin = list_begin->next;
    }
    std::cout << std::endl;
}


void showListFromEnd(DoubleLinkedListProperties *list_end) {
    std::cout << "Список элементов с конца:";
    fflush(stdout);

    while (list_end != nullptr) {
        std::cout << " [" << list_end->info << "]";
        list_end = list_end->prev;
    }
    std::cout << std::endl;
}


void showList(DoubleLinkedListProperties *&list_begin, DoubleLinkedListProperties *&list_end) {
    std::cout << "Вывести список с начала (1) или с конца (2)?" << std::endl;
    std::cout << "Введите то, что выбрали: ";
    fflush(stdout);

    int choice;
    do {
        choice = readInt(1, 2);

        if (choice == 0) {
            std::cout << "Неверный ввод." << std::endl;
            if (!isTryAgain()) {
                return;
            }
        }
    } while (choice == 0);

    (choice == 1) ? showListFromBegin(list_begin) : showListFromEnd(list_end);
}


DoubleLinkedListProperties *getMinElementList(DoubleLinkedListProperties *list_begin) {
    DoubleLinkedListProperties *ret = list_begin;
    list_begin = list_begin->next;

    while (list_begin != nullptr) {
        if (list_begin->info < ret->info) {
            ret = list_begin;
        }
        list_begin = list_begin->next;
    }
    return ret;
}


DoubleLinkedListProperties *getMaxElementList(DoubleLinkedListProperties *list_begin) {
    DoubleLinkedListProperties *ret = list_begin;
    list_begin = list_begin->next;

    while (list_begin != nullptr) {
        if (list_begin->info > ret->info) {
            ret = list_begin;
        }
        list_begin = list_begin->next;
    }
    return ret;
}
