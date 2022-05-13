#include <vector>
#include <windows.h>

#include "accounts.h"
#include "other-functions.h"
#include "sorts.h"
#include "system-access.h"

int main() {
//    SetConsoleCP(1251);
//    SetConsoleCP(cp);
//    SetConsoleOutputCP(1251);
//    SetConsoleOutputCP(CP866);

    std::vector<AccountProperties> accounts;
    readAccounts(accounts);

    showMainMenu(accounts);

    writeAccounts(accounts);

    system("pause");

    return 0;
}
