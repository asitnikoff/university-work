#include <vector>
#include <windows.h>

#include "accounts.h"
#include "other-functions.h"
#include "sorts.h"
#include "system-access.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::vector<AccountProperties> accounts;
    readAccounts(accounts);

    showMainMenu(accounts);

    showListOfUsers(accounts);

    writeAccounts(accounts);

    system("pause");

    return 0;
}
