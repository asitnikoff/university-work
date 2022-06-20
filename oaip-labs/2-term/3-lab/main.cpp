#include <iostream>

#include "double-linked-list.h"
#include "validation.h"


#define INCORRECT_NUMBER_OF_ELEMENTS_IN_LIST "Неверное количество элементов в списке."


void addElementsInList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
void doTask(DoubleLinkedListProperties*);
int getRandomNumber();


int main() {
    srand(time(0));

    std::cout << "Чтобы упростить вам работу, список автоматически создан и он пуст." << std::endl;

    DoubleLinkedListProperties *list_begin = nullptr, *list_end = nullptr;

    while (true) {
        std::cout << "1 - Создать список (старый очистится).\n";
        std::cout << "2 - Добавить элементы в список.\n";
        std::cout << "3 - Вывести элементы списка.\n";
        std::cout << "4 - Очистить список.\n";
        std::cout << "5 - Удалить элементы между минимальным и максимальным элементами.\n";
        std::cout << "Иначе - Выйти.\n";

        std::cout << "Введите опцию: ";
        fflush(stdout);

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                clearList(list_begin, list_end);
                std::cout << "Список создан!" << std::endl;
                break;
            case 2:
                addElementsInList(list_begin, list_end);
                break;
            case 3:
                showList(list_begin);
                break;
            case 4:
                clearList(list_begin, list_end);
                break;
            case 5:
                doTask(list_begin);
                break;
            default:
                clearList(list_begin, list_end);
                return 0;
        }
    }
}


void addElementsInList(DoubleLinkedListProperties*& list_begin, DoubleLinkedListProperties*& list_end) {
    std::cout << "Введите количество элементов N (1 <= N <= 10000): ";
    fflush(stdout);
    int n = read<int>(1, 10000);

    std::cout << "Добавлять элементы в начало (1) или в конец (2)?" << std::endl;
    int choice_where = read<int>(1, 2);

    std::cout << "Какие элементы добавлять?" << std::endl;
    std::cout << "1 - случайно сгенерированные" << std::endl;
    std::cout << "2 - введенные с клавиатуры" << std::endl;

    int choice = read<int>(1, 2);

    if (choice == 1) {
        std::cout << "Введите элементы списка: ";
        fflush(stdout);
        if (choice_where == 1) {
            while (n > 0) {
                int x = read<int>();
                pushBeginList(list_begin, list_end, x);
                --n;
            }
        } else {
            while (n > 0) {
                int x = read<int>();
                pushEndList(list_begin, list_end, x);
                --n;
            }
        }
    } else {
        if (choice_where == 1) {
            while (n > 0) {
                int x = getRandomNumber();
                pushBeginList(list_begin, list_end, x);
                --n;
            }
        } else {
            while (n > 0) {
                int x = getRandomNumber();
                pushEndList(list_begin, list_end, x);
                --n;
            }
        }
    }
    clearInputBuffer();

    std::cout << "Элементы добавлены в список." << std::endl;
}


void doTask(DoubleLinkedListProperties* list_begin) {
    if (isEmptyList(list_begin) || (list_begin->next == nullptr)) {
        std::cout << "Для выполнения задания список должен состоять минимум из 2 элементов." << std::endl;
        return;
    }

    DoubleLinkedListProperties *list_first_element = getMinElementList(list_begin);
    DoubleLinkedListProperties *list_second_element = getMaxElementList(list_begin);

    if (isEarlyList(list_second_element, list_first_element)) {
        swapElementsList(list_first_element, list_second_element);
    }

    if (list_first_element->next == list_second_element) {
        std::cout << "Максимальный и минимальный элементы находятся рядом. Ничего удалять не нужно." << std::endl;
        return;
    }

    DoubleLinkedListProperties *tmp = list_first_element->next;
    list_second_element->prev->next = nullptr;
    list_second_element->prev = list_first_element;
    list_first_element->next->prev = nullptr;
    list_first_element->next = list_second_element;


    std::cout << "Элементы, которые были удалены:";

    list_first_element = tmp;
    while (list_first_element != list_second_element) {
        tmp = list_first_element;
        list_first_element = list_first_element->next;
        tmp->prev = tmp->next = nullptr;
        std::cout << " [" << tmp->info << "]";
        delete tmp;
    }
    std::cout << std::endl;
}


int getRandomNumber() {
    return rand();
}