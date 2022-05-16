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
    std::cout << "Добро пожаловать, " << login << "!" << std::endl;
}
