#include "sorts.h"

#include <algorithm>

void sortAccountsByLoginIncrease(std::vector<AccountProperties>& accounts) {
    sort(accounts.begin(), accounts.end(), [](const AccountProperties& a, const AccountProperties& b) {
        return a.login < b.login;
    });
}
