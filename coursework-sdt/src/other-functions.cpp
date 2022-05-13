#include <vector>
#include <iostream>
#include <conio.h>
#include <limits>

#include "other-functions.h"
#include "accounts.h"
#include "system-access.h"
#include "modules.h"


void showMainMenu(std::vector<AccountProperties>& accounts) {
    while (true) {
        system("cls");
        std::cout << WELCOME_MESSAGE << std::endl << std::endl;

        std::cout << "1) " << LOGIN_SYSTEM_MESSAGE << std::endl;
        std::cout << "2) " << REGISTER_MESSAGE << std::endl;
        std::cout << "3) " << CLOSE_SYSTEM_MESSAGE << std::endl;

        char choice;
        choice = (char) getch();

        switch (choice) {
            case '1':
                logInSystem(accounts);
                break;
            case '2':
                registerUserPage(accounts);
                break;
            case '3':
            default:
                return;
        }
    }
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}