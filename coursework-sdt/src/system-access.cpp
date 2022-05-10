#include <iostream>
#include <conio.h>

#include "system-access.h"
#include "accounts.h"
#include "other-functions.h"
#include "validation.h"


std::string inputLogin() {
    std::string login;
    getline(std::cin, login);
    return login;
}

std::string inputPassword() {
    std::string password;
    while (true) {
        char c = _getch();
        if (c == '\r') {
            std::cout << std::endl;
            break;
        }
        if (c == '\b') {
            if (!password.empty()) {
                std::cout << "\x1B[1D"; // Move the cursor one unit to the left
                std::cout << "\x1B[1P"; // Delete the character
                password.erase((int)password.size() - 1, 1);
            }
        }
        else {
            password += c;
            std::cout << '*';
        }
    }

    return password;
}