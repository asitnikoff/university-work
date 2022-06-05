#include <iostream>

#include "stack.h"


void addElementsInStack(Stack<int>&);
void showStack(const Stack<int>&);
void clearStack(Stack<int>&);
void doTask(Stack<int>&);


int main() {
    Stack<int> stack;

    while (true) {
        std::cout << "1 - Create new stack.\n";
        std::cout << "2 - Add elements in stack.\n";
        std::cout << "3 - Show stack.\n";
        std::cout << "4 - Clear stack.\n";
        std::cout << "5 - Do task.\n";
        std::cout << "Else - Exit.\n";

        std::cout << "Input option: ";
        fflush(stdout);

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!stack.empty()) {
                    std::cout << "Stack don't empty. Are you want to clear it now?\n";
                    std::cout << "1 - yes.\n";
                    std::cout << "Else - no.\n";
                    fflush(stdout);

                    std::cin >> choice;
                    if (choice == 1) {
                        stack.clear();
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
                doTask(stack);
                break;
            default:
                system("pause");
                return 0;
        }
    }
}
