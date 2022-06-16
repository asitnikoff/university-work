#include <iostream>

#include "stack.h"
#include "validation.h"


#define INCORRECT_NUMBER_OF_ELEMENTS_IN_STACK "Неверное количество элементов в стеке."


void addElementsInStack(StackProperties*&);
void doTask(StackProperties*&);
void clearInputBuffer();


int main() {
    StackProperties *stack = nullptr;
    bool isCreated = false;

    while (true) {
        std::cout << "1 - Создать стек.\n";
        std::cout << "2 - Добавить элементы в стек.\n";
        std::cout << "3 - Вывести элементы стека.\n";
        std::cout << "4 - Очистить стек.\n";
        std::cout << "5 - Отсортировать стек.\n";
        std::cout << "6 - Удалить элементы между минимальным и максимальным элементами.\n";
        std::cout << "Иначе - Выйти.\n";

        std::cout << "Введите опцию: ";
        fflush(stdout);

        int choice;
        std::cin >> choice;
        clearInputBuffer();

        if (!isCreated && (choice >= 2) && (choice <= 6)) {
            std::cout << "Сначала необходимо создать стек, чтобы с ним работать." << std::endl;
            std::cout << "Для этого в главном меню необходимо выбрать опцию \"1\"." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                if (!isEmptyStack(stack)) {
                    std::cout << "Стек не пуст. Хотите очистить его сейчас?\n";
                    std::cout << "1 - да.\n";
                    std::cout << "Иначе - нет.\n";
                    fflush(stdout);

                    std::cin >> choice;
                    clearInputBuffer();

                    if (choice == 1) {
                        clearStack(stack);
                    } else {
                        std::cout << "Перед созданием нового стека вам необходимо очистить старый." << std::endl;
                        break;
                    }
                }

                isCreated = true;
                std::cout << "Стек создан!" << std::endl;
                break;
            case 2:
                addElementsInStack(stack);
                break;
            case 3:
                showStack(stack);
                break;
            case 4:
                clearStack(stack);
                break;
            case 5:
                sortStack(stack);
                break;
            case 6:
                doTask(stack);
                break;
            default:
                clearStack(stack);
                return 0;
        }
    }
}


void addElementsInStack(StackProperties*& stack) {
    int n;
    do {
        std::cout << "Введите количество элементов N (1 <= N <= 10000): ";
        fflush(stdout);

        n = readInt(1, 10000);

        if (n == 0) {
            std::cout << INCORRECT_NUMBER_OF_ELEMENTS_IN_STACK << std::endl;
            if (!isTryAgain()) {
                return;
            }
        }
    } while (n == 0);

    std::cout << "Введите элементы стека: ";
    fflush(stdout);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        pushStack(stack, x);
    }
    clearInputBuffer();

    std::cout << "Элементы добавлены в стек" << std::endl;
}


void doTask(StackProperties*& stack) {
    if (isEmptyStack(stack) || (stack->next == nullptr)) {
        std::cout << "Для выполнения задания стек должен состоять минимум из 2 элементов." << std::endl;
        return;
    }

    StackProperties *stack_first_element = getMinElementStack(stack);
    StackProperties *stack_second_element = getMaxElementStack(stack);

    if (isEarlyStack(stack_second_element, stack_first_element, stack)) {
        swapElementsStack(stack_first_element, stack_second_element);
    }

    if (stack_first_element->next == stack_second_element) {
        std::cout << "Максимальный и минимальный элементы находятся рядом. Ничего удалять не нужно." << std::endl;
        return;
    }

    StackProperties* tmp = stack_first_element->next;
    stack_first_element->next = stack_second_element;
    while (tmp != stack_second_element) {
        StackProperties* new_tmp = tmp;
        tmp = tmp->next;
        new_tmp->next = nullptr;
        delete new_tmp;
    }
}


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}