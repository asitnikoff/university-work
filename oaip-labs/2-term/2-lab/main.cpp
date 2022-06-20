#include <iostream>

#include "stack.h"


template <typename Type>
Type read();
template <typename Type>
Type read(Type, Type);
void addElementsInStack(StackProperties*&);
void doTask(StackProperties*&);
void clearInputBuffer();
int getRandomNumber();


int main() {
    srand(time(0));
    std::cout << "Чтобы упростить вам работу, стек автоматически создан и он пуст." << std::endl;
    StackProperties *stack = nullptr;

    while (true) {
        std::cout << "1 - Создать новый стек (старый очиститься).\n";
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

        switch (choice) {
            case 1:
//                if (!isEmptyStack(stack)) {
//                    std::cout << "Стек не пуст. Хотите очистить его сейчас?\n";
//                    std::cout << "1 - да.\n";
//                    std::cout << "Иначе - нет.\n";
//                    fflush(stdout);
//
//                    std::cin >> choice;
//                    clearInputBuffer();
//
//                    if (choice == 1) {
//                        clearStack(stack);
//                    } else {
//                        std::cout << "Перед созданием нового стека вам необходимо очистить старый." << std::endl;
//                        break;
//                    }
//                }

                clearStack(stack);
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


template <typename Type>
Type read() {
    Type x;
    while (true) {
        std::cin >> x;
        if (std::cin.get() != '\n') {
            clearInputBuffer();
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
        }
        else {
            break;
        }
    }
    return x;
}


template <typename Type>
Type read(Type left, Type right) {
    Type x;
    while (true) {
        std::cin >> x;
        if (std::cin.get() != '\n') {
            clearInputBuffer();
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
        }
        else if (!((x >= left) && (x <= right))) {
            std::cout << "Число не удовлетворяет отрезку. Попробуйте снова." << std::endl;
        } else {
            break;
        }
    }
    return x;
}


void addElementsInStack(StackProperties*& stack) {
    std::cout << "Введите количество элементов N (1 <= N <= 10000): ";
    fflush(stdout);
    int n = read<int>(1, 10000);

    std::cout << "Какие элементы добавить?" << std::endl;
    std::cout << "1 - случайно сгенерированные" << std::endl;
    std::cout << "2 - введенные с клавиатуры" << std::endl;

    int choice = read<int>(1, 2);

    if (choice == 1) {
        std::cout << "Введите элементы стека: ";
        fflush(stdout);
        while (n > 0) {
            int x = read<int>();
            pushStack(stack, x);
            --n;
        }
    } else {
        while (n > 0) {
            int x = getRandomNumber();
            pushStack(stack, x);
            --n;
        }
    }

    std::cout << "Элементы добавлены в стек." << std::endl;
}


void doTask(StackProperties*& stack) {
    if ((stack == nullptr) || (stack->next == nullptr)) {
        std::cout << "Для выполнения задания стек должен состоять минимум из 2 элементов." << std::endl;
        return;
    }

    StackProperties *stack_first_element = getMinElementStack(stack);
    StackProperties *stack_second_element = getMaxElementStack(stack);

    if (isEarlyStack(stack_second_element, stack_first_element)) {
        swapElementsStack(stack_first_element, stack_second_element);
    }

    if (stack_first_element->next == stack_second_element) {
        std::cout << "Максимальный и минимальный элементы находятся рядом. Ничего удалять не нужно." << std::endl;
        return;
    }

    StackProperties* tmp = stack_first_element->next;
    stack_first_element->next = stack_second_element;

    std::cout << "Элементы, которые были удалены:";

    stack_first_element = tmp;
    while (stack_first_element != stack_second_element) {
        tmp = stack_first_element;
        stack_first_element = stack_first_element->next;
        tmp->next = nullptr;
        std::cout << " [" << tmp->info << "]";
        delete tmp;
    }
    std::cout << std::endl;
}


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


int getRandomNumber() {
    return rand();
}