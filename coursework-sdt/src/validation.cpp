#include <iostream>
#include <conio.h>

#include "validation.h"
#include "accounts.h"
#include "sha256.h"


bool isCorrectAccount(const std::string& login, const std::string& password, const std::vector<AccountProperties>& accounts) {
    bool is_correct = false;
    for (auto account : accounts) {
        if (account.login != login) {
            continue;
        }
        std::string hashed_password = sha256(password + account.salt);
        if (hashed_password != account.salted_hash_password) {
            continue;
        }
        is_correct = true;
    }
    return is_correct;
}

bool isValidLogin(const std::string& login) {
    for (auto& el : login) {
        if (LOGIN_TEMPLATE.find(el) == std::string::npos) {
            return false;
        }
    }
    return !login.empty();
}

bool isUniqueLogin(const std::string& login, const std::vector<AccountProperties>& accounts) {
    return !isLoginExist(login, accounts);
}

bool isValidPassword(const std::string& password) {
    for (auto& el : password) {
        if (PASSWORD_TEMPLATE.find(el) == std::string::npos) {
            return false;
        }
    }
    return ((int)password.size() >= 6);
}

bool isTryAgain() {
    std::cout << TRY_AGAIN << std::endl;
    return ((char)getch() == '1');
}

bool isLoginExist(const std::string &login, const std::vector<AccountProperties> &accounts) {
    for (const auto &account : accounts) {
        if (account.login == login) {
            return true;
        }
    }
    return false;
}

bool isAccountExist(const std::string& login, const std::vector<AccountProperties>& accounts) {
    for (const auto &account : accounts) {
        if (account.login == login) {
            return true;
        }
    }
    return false;
}

int readInt(int left_range, int right_range) {
    int temp;
    std::cin >> temp;
    bool isGood = (std::cin.get() == '\n');

    if (isGood && (temp >= left_range) && (temp <= right_range)) {
        return temp;
    }
    return (left_range - 1);
}
