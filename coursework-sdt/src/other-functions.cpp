#include <vector>
#include <iostream>
#include <conio.h>
#include <limits>

#include "other-functions.h"
#include "accounts.h"
#include "system-access.h"
#include "modules.h"


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showAccountWelcomeMessage(const std::string &login) {
    std::cout << "????? ??????????, " << login << "!" << std::endl;
}

bool isConfirmChanges(std::string message) {
    std::cout << message << std::endl;
    std::cout << "1) " << YES << std::endl;
    std::cout << "2) " << NO << std::endl;

    int choice;
    do {
        choice = getch() - '0';
    } while ((choice != 1) && (choice != 2));

    return (choice == 1);
}

void showMessage(std::string message) {
    system("cls");
    std::cout << message << std::endl;
    system("pause");
}

int getAmountOfBits(int x) {
    int ret = 0;
    while (x > 0) {
        ++ret;
        x /= 10;
    }
    return ret;
}
