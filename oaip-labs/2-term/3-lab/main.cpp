#include <iostream>

#include "double-linked-list.h"
#include "validation.h"


#define INCORRECT_NUMBER_OF_ELEMENTS_IN_LIST "Неверное количество элементов в списке."


void addElementsInList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
void clearInputBuffer();
void doTask(DoubleLinkedListProperties*);


int main() {
    DoubleLinkedListProperties *list_begin = nullptr, *list_end = nullptr;
    bool isCreated = false;

    while (true) {
        std::cout << "1 - Создать список.\n";
        std::cout << "2 - Добавить элементы в список.\n";
        std::cout << "3 - Вывести элементы списка.\n";
        std::cout << "4 - Очистить список.\n";
        std::cout << "5 - Отсортировать список.\n";
        std::cout << "6 - Удалить элементы между минимальным и максимальным элементами.\n";
        std::cout << "Иначе - Выйти.\n";

        std::cout << "Введите опцию: ";
        fflush(stdout);

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (!isCreated && (choice >= 2) && (choice <= 6)) {
            std::cout << "Сначала необходимо создать список, чтобы с ним работать." << std::endl;
            std::cout << "Для этого в главном меню необходимо выбрать опцию \"1\"." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                if (!isEmptyList(list_begin)) {
                    std::cout << "Список не пуст. Хотите очистить его сейчас?\n";
                    std::cout << "1 - да.\n";
                    std::cout << "Иначе - нет.\n";
                    fflush(stdout);

                    std::cin >> choice;
                    clearInputBuffer();

                    if (choice == 1) {
                        clearList(list_begin, list_end);
                    } else {
                        std::cout << "Перед созданием нового списка вам необходимо очистить старый." << std::endl;
                        break;
                    }
                }

                isCreated = true;
                std::cout << "Список создан!" << std::endl;
                break;
            case 2:
                addElementsInList(list_begin, list_end);
                break;
            case 3:
                showList(list_begin, list_end);
                break;
            case 4:
                clearList(list_begin, list_end);
                break;
            case 5:
//                sortList(list);
                break;
            case 6:
                doTask(list_begin);
                break;
            default:
                clearList(list_begin, list_end);
                return 0;
        }
    }
}


void addElementsInList(DoubleLinkedListProperties*& list_begin, DoubleLinkedListProperties*& list_end) {
    int n;
    do {
        std::cout << "Введите количество элементов N (1 <= N <= 10000): ";
        fflush(stdout);

        n = readInt(1, 10000);

        if (n == 0) {
            std::cout << INCORRECT_NUMBER_OF_ELEMENTS_IN_LIST << std::endl;
            if (!isTryAgain()) {
                return;
            }
        }
    } while (n == 0);

    int choice_where;
    do {
        std::cout << "Добавлять элементы в начало (1) или в конец (2)?" << std::endl;
        choice_where = readInt(1, 2);
        if (choice_where == 0) {
            std::cout << "Неверный ввод." << std::endl;
            if (!isTryAgain()) {
                return;
            }
        }
    } while (choice_where == 0);

    std::cout << "Введите элементы стека: ";
    fflush(stdout);
    if (choice_where == 1) {
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            pushBeginList(list_begin, list_end, x);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            pushEndList(list_begin, list_end, x);
        }
    }
    clearInputBuffer();

    std::cout << "Элементы добавлены в список" << std::endl;
}


void doTask(DoubleLinkedListProperties* list_begin) {
    if (isEmptyList(list_begin) || (list_begin->next == nullptr)) {
        std::cout << "Для выполнения задания стек должен состоять минимум из 2 элементов." << std::endl;
        return;
    }

    DoubleLinkedListProperties *list_first_element = getMinElementList(list_begin);
    DoubleLinkedListProperties *list_second_element = getMaxElementList(list_begin);

    if (isEarlyList(list_second_element, list_first_element, list_begin)) {
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

    clearList(tmp, tmp); // костыль, но лень писать отдельную реализацию удаления
}


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}