#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <conio.h>

#include "accounts.h"
#include "sha256.h"
#include "fstream-utilities.h"
#include "other-functions.h"
#include "system-access.h"


std::string generateSalt(std::string salt) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(salt.begin(), salt.end(), g);

    return salt;
}

AccountProperties getDefaultAccount() {
    AccountProperties temp;
    temp.login = DEFAULT_LOGIN;
    temp.salt = generateSalt(SALT_TEMPLATE);
    temp.salted_hash_password = sha256(DEFAULT_PASSWORD + temp.salt);
    temp.isAdmin = true;
    temp.isHaveAccess = true;
    temp.isApproved = true;

    return temp;
}

void readAccounts(std::vector<AccountProperties>& accounts) {
    std::ifstream fin;
    fin.open(ACCOUNTS_FILENAME, std::ios::in | std::ios::binary);
    if (!fin.is_open()) {
        accounts.push_back(getDefaultAccount());
    }
    else {
        AccountProperties temp;

        fin.seekg(0, std::ios::end);
        int file_size = (int)fin.tellg();
        fin.seekg(0, std::ios::beg);

        while (fin.tellg() < file_size) {
            temp.login = readStringFromIfstream(fin);
            temp.salted_hash_password = readStringFromIfstream(fin);
            temp.salt = readStringFromIfstream(fin);
            temp.isAdmin = readBoolFromIfstream(fin);
            temp.isHaveAccess = readBoolFromIfstream(fin);
            temp.isApproved = readBoolFromIfstream(fin);

            accounts.push_back(temp);
        }
    }
    fin.close();
}

void writeAccounts(const std::vector<AccountProperties>& accounts) {
    std::ofstream fout;
    fout.open(ACCOUNTS_FILENAME, std::ios::out | std::ios::binary);

    int n = (int)accounts.size();
    for (int i = 0; i < n; ++i) {
        writeStringInOfstream(fout, accounts[i].login);
        writeStringInOfstream(fout, accounts[i].salted_hash_password);
        writeStringInOfstream(fout, accounts[i].salt);
        writeBoolInOfstream(fout, accounts[i].isAdmin);
        writeBoolInOfstream(fout, accounts[i].isHaveAccess);
        writeBoolInOfstream(fout, accounts[i].isApproved);
    }
}

AccountProperties createNewUser(std::string login, std::string password) {
    AccountProperties new_user;
    new_user.login = login;
    new_user.salt = generateSalt(SALT_TEMPLATE);
    new_user.salted_hash_password = sha256(password + new_user.salt);
    new_user.isAdmin = false;
    new_user.isHaveAccess = false;

    return new_user;
}

void addAccount(const AccountProperties& user, std::vector<AccountProperties>& accounts) {
    accounts.push_back(user);
}

bool isAccountExist(const std::string& login, const std::vector<AccountProperties>& accounts) {
    for (const auto &account : accounts) {
        if (account.login == login) {
            return true;
        }
    }
    return false;
}

void showListOfUsers(const std::vector<AccountProperties>& accounts) {
    for (const auto &user : accounts) {
        std::cout << "login: [" << user.login << "]\n";
        std::cout << "salt: [" << user.salt << "]\n";
        std::cout << "salted_hash_password: [" << user.salted_hash_password << "]\n";
        std::cout << "admin: [" << (user.isAdmin ? "true" : "false") << "]\n";
        std::cout << "access: [" << (user.isHaveAccess ? "true" : "false") << "]\n";
        std::cout << "approved: [" << (user.isApproved ? "true" : "false") << "]\n\n";
    }
    std::cout << std::endl;
}

void editUserData(std::vector<AccountProperties>& accounts) {
    showListOfUsers(accounts);

    std::cout << INPUT_USER_LOGIN;
    fflush(stdout);

    int p = getAccountPositionByLogin(inputLogin(), accounts);

    std::cout << WHAT_CHANGE << std::endl;
    std::cout << "1) " << LOGIN << std::endl;
    std::cout << "2) " << PASSWORD << std::endl;
    std::cout << "3) " << ROLE << std::endl;

    char choice = _getch();

    switch (choice) {
        case '1':
            editUserLogin(accounts[p]);
            break;
        case '2':
            editUserPassword(accounts[p]);
            break;
        case '3':
            editUserRole(accounts[p]);
            break;
    }
}

int getAccountPositionByLogin(std::string login, const std::vector<AccountProperties>& accounts) {
    for (int i = 0; i < (int)accounts.size(); ++i) {
        if (accounts[i].login == login) {
            return i;
        }
    }
    return -1;
}

void editUserLogin(AccountProperties& account) {
    std::cout << LOGIN_INPUT_MESSAGE;
    fflush(stdout);
    std::string login = inputLogin();
    account.login = login;
}

void editUserPassword(AccountProperties& account) {
    std::cout << PASSWORD_INPUT_MESSAGE;
    fflush(stdout);
    std::string password = inputPassword();
    account.salt = generateSalt(SALT_TEMPLATE);
    account.salted_hash_password= sha256(password + account.salt);
}

void editUserRole(AccountProperties& account) {
    std::cout << SELECT_ROLE << std::endl;
    std::cout << "1) " << ADMIN << std::endl;
    std::cout << "2) " << COMMON_USER << std::endl;

    char choice = _getch();

    switch (choice) {
        case '1':
            account.isAdmin = true;
            break;
        case '2':
            account.isAdmin = false;
            break;
    }
}

void deleteUserData(std::vector<AccountProperties>& accounts) {
    showListOfUsers(accounts);

    std::cout << INPUT_USER_LOGIN;
    fflush(stdout);

    int p = getAccountPositionByLogin(inputLogin(), accounts);

    accounts.erase(accounts.begin() + p);
}

void confirmAccounts(std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> blocked_accounts = getListOfBlockedAccounts(accounts);
    showListOfUsers(blocked_accounts);

    std::cout << INPUT_USER_LOGIN_FOR_UNBLOCK;
    fflush(stdout);

    int p = getAccountPositionByLogin(inputLogin(), accounts);

    accounts[p].isHaveAccess = true;
}

std::vector<AccountProperties> getListOfBlockedAccounts(std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> blocked_accounts;
    for (auto& account : accounts) {
        if (!account.isHaveAccess) {
            blocked_accounts.push_back(account);
        }
    }
    return blocked_accounts;
}

void blockAccounts(std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> unblocked_accounts = getListOfUnblockedAccounts(accounts);
    showListOfUsers(unblocked_accounts);

    std::cout << INPUT_USER_LOGIN_FOR_UNBLOCK;
    fflush(stdout);

    int p = getAccountPositionByLogin(inputLogin(), accounts);

    accounts[p].isHaveAccess = false;
}

std::vector<AccountProperties> getListOfUnblockedAccounts(std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> unblocked_accounts;
    for (auto& account : accounts) {
        if (!account.isHaveAccess) {
            unblocked_accounts.push_back(account);
        }
    }
    return unblocked_accounts;
}

void giveAdminRootAccounts(std::vector<AccountProperties>& accounts) {
    std::cout << INPUT_USER_LOGIN_FOR_ADMIN_ROOT;
    fflush(stdout);

    int p = getAccountPositionByLogin(inputLogin(), accounts);

    accounts[p].isHaveAccess = false;
}

AccountProperties getAccountByLogin(std::string login, const std::vector<AccountProperties>& accounts) {
    AccountProperties ret;
    for (auto& account : accounts) {
        if (account.login == login) {
            ret = account;
        }
    }
    return ret;
}