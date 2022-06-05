#include <iostream>

#include "stack.h"


void addElementsInStack(StackProperties*&);
void doTask(StackProperties*&);


int main() {
    StackProperties *stack = nullptr;

    while (true) {
        std::cout << "1 - Create new stack.\n";
        std::cout << "2 - Add elements in stack.\n";
        std::cout << "3 - Show stack.\n";
        std::cout << "4 - Clear stack.\n";
        std::cout << "5 - Sort stack.\n";
        std::cout << "6 - Do task.\n";
        std::cout << "Else - Exit.\n";

        std::cout << "Input option: ";
        fflush(stdout);

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!isEmptyStack(stack)) {
                    std::cout << "Stack don't empty. Are you want to clear it now?\n";
                    std::cout << "1 - yes.\n";
                    std::cout << "Else - no.\n";
                    fflush(stdout);

                    std::cin >> choice;
                    if (choice == 1) {
                        clearStack(stack);
                    } else {
                        std::cout << "Before create new stack you need to empty last." << std::endl;
                        break;
                    }
                }

                addElementsInStack(stack);
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
    std::cout << "Input number of elements: ";
    fflush(stdout);

    int n;
    std::cin >> n;

    std::cout << "Input elements." << std::endl;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        pushStack(stack, x);
    }
}


void doTask(StackProperties*& stack) {
    StackProperties *stack_first_element = getMinElementStack(stack);
    StackProperties *stack_second_element = getMaxElementStack(stack);

    if (isEarlyStack(stack_second_element, stack_first_element, stack)) {
        swapElementsStack(stack_first_element, stack_second_element);
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