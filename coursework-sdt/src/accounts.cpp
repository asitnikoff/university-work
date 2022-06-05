#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <conio.h>
#include <iomanip>

#include "accounts.h"
#include "sha256.h"
#include "fstream-utilities.h"
#include "other-functions.h"
#include "system-access.h"
#include "validation.h"


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
    fout.close();
}

AccountProperties createNewUser(std::string login, std::string password) {
    AccountProperties new_user;
    new_user.login = login;
    new_user.salt = generateSalt(SALT_TEMPLATE);
    new_user.salted_hash_password = sha256(password + new_user.salt);
    new_user.isAdmin = false;
    new_user.isHaveAccess = true;
    new_user.isApproved = false;

    return new_user;
}

void addAccount(const AccountProperties& user, std::vector<AccountProperties>& accounts) {
    accounts.push_back(user);
}

void showListOfUsers(const std::vector<AccountProperties>& accounts) {
    /*
    for (const auto &user : accounts) {
        std::cout << "login: [" << user.login << "]\n";
        std::cout << "salt: [" << user.salt << "]\n";
        std::cout << "salted_hash_password: [" << user.salted_hash_password << "]\n";
        std::cout << "admin: [" << (user.isAdmin ? "true" : "false") << "]\n";
        std::cout << "access: [" << (user.isHaveAccess ? "true" : "false") << "]\n";
        std::cout << "approved: [" << (user.isApproved ? "true" : "false") << "]\n\n";
    }
    std::cout << std::endl;
    */

    std::cout << "| Позиция |      Логин      |         Пароль         |      Роль      |     Доступ     | Подтверждён |" << std::endl;
    for (int i = 0; i < 102; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
    int cnt = 0;
    for (const auto &user : accounts) {
        ++cnt;
        std::cout << "|";
        std::cout << cnt << std::setw(9) << "|";
        std::cout << user.login << std::setw(17 - (int)user.login.size() + 1) << "|";
        std::cout << user.salted_hash_password.substr(0, 15) + "..." << std::setw(7) << "|";
        std::cout << (user.isAdmin ? "Администратор" : "Пользователь") << std::setw(16 - (user.isAdmin ? 13 : 12) + 1) << "|";
        std::cout << (user.isHaveAccess ? "Разрешен" : "Запрещен") << std::setw(16 - 7) << "|";
        std::cout << (user.isApproved ? "Да" : "Нет") << std::setw(13 - (user.isApproved ? 2 : 3) + 1) << "|";
        std::cout << std::endl;
    }
    for (int i = 0; i < 102; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl << std::endl;
}

void editUserData(std::vector<AccountProperties>& accounts) {
    std::string login;
    while (true) {
        login = inputCorrectLogin(INPUT_USER_LOGIN, accounts);
        if (login.empty()) {
            return;
        }
        if (!isAccountExist(login, accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return;
        }
    }

    int p = getAccountPositionByLogin(login, accounts);

    std::cout << WHAT_CHANGE << std::endl;
    std::cout << "1) " << PASSWORD << std::endl;
    std::cout << "2) " << ROLE << std::endl;

    int choice;
    do {
        choice = getch() - '0';
    } while ((choice != 1) && (choice != 2));

    switch (choice) {
        case 1:
            editUserPassword(accounts[p]);
            break;
        case 2:
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

void editUserPassword(AccountProperties& account) {
    std::string password, confirmation_password;
    while (true) {
        system("cls");
        std::cout << NEW_PASSWORD_INPUT_MESSAGE;
        fflush(stdout);
        password = inputPassword();
        std::cout << CONFIRM_PASSWORD_MESSAGE;
        fflush(stdout);
        confirmation_password = inputPassword();

        if (password != confirmation_password) {
            std::cout << PASSWORDS_DONT_MATCH << std::endl;
        } else if (sha256(password + account.salt) == account.salted_hash_password){
            std::cout << NEW_PASSWORD_SHOULDNT_MATCH_WITH_OLD << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return;
        }
    }
    account.salt = generateSalt(SALT_TEMPLATE);
    account.salted_hash_password= sha256(password + account.salt);

    std::cout << SUCCESSFUL_PASSWORD_CHANGE << std::endl;
    system("pause");
}

void editUserRole(AccountProperties& account) {
    std::cout << SELECT_ROLE << std::endl;
    std::cout << "1) " << ADMIN << std::endl;
    std::cout << "2) " << COMMON_USER << std::endl;

    int choice;
    do {
        choice = getch() - '0';
    } while ((choice != 1) && (choice != 2));

    account.isAdmin = (choice == 1);

    std::cout << SUCCESSFUL_ROLE_CHANGE << std::endl;
    system("pause");
}

void deleteUserData(const AccountProperties& account, std::vector<AccountProperties>& accounts) {
    std::string login = inputLoginForDelete(INPUT_USER_LOGIN_FOR_DELETE, account, accounts);
    if (login.empty()) {
        return;
    }

    if (isConfirmChanges(WAIT_CONFIRMATION_FOR_DELETE) == 1) {
        int p = getAccountPositionByLogin(login, accounts);

        accounts.erase(accounts.begin() + p);

        std::cout << SUCCESSFUL_ACCOUNT_DELETE << std::endl;
        system("pause");
    }
}

void approveAccounts(std::vector<AccountProperties>& accounts) {
    while (true) {
        system("cls");
        std::vector<AccountProperties> unapproved_accounts = getListOfUnapprovedAccounts(accounts);
        if (unapproved_accounts.empty()) {
            std::cout << NO_UNAPPROVED_ACCOUNTS << std::endl;
            system("pause");
            return;
        }
        showListOfUsers(unapproved_accounts);

        std::cout << "1) " << APPROVE_ONE_ACCOUNT << std::endl;
        std::cout << "2) " << UNAPPROVE_ONE_ACCOUNT << std::endl;
        std::cout << "3) " << APPROVE_ALL_ACCOUNTS << std::endl;
        std::cout << "4) " << UNAPPROVE_ALL_ACCOUNTS << std::endl;
        std::cout << "5) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                approveOneAccount(unapproved_accounts, accounts);
                break;
            case 2:
                unapproveOneAccount(unapproved_accounts, accounts);
                break;
            case 3:
                approveAllAccounts(accounts);
                break;
            case 4:
                unapproveAllAccounts(accounts);
                break;
            case 5:
                return;
        }
    }
}

std::vector<AccountProperties> getListOfUnapprovedAccounts(std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> unapproved_accounts;
    for (auto& account : accounts) {
        if (!account.isApproved) {
            unapproved_accounts.push_back(account);
        }
    }
    return unapproved_accounts;
}

void blockAccounts(const AccountProperties& account, std::vector<AccountProperties>& accounts) {
    system("cls");
    std::vector<AccountProperties> unblocked_accounts = getListOfUnblockedAccounts(account, accounts);
    if (unblocked_accounts.empty()) {
        std::cout << NO_UNBLOCKED_ACCOUNTS << std::endl;
        system("pause");
        return;
    }
    std::string login = inputLoginForBlock(INPUT_USER_LOGIN_FOR_BLOCK, account, unblocked_accounts, accounts);
    if (login.empty()) {
        return;
    }

    if (isConfirmChanges(WAIT_CONFIRMATION_FOR_BLOCK) == 1) {
        int p = getAccountPositionByLogin(login, accounts);

        accounts[p].isHaveAccess = false;

        std::cout << SUCCESSFUL_ACCOUNT_BLOCK << std::endl;
        system("pause");
    }
}

void unblockAccounts(std::vector<AccountProperties>& accounts) {
    system("cls");
    std::vector<AccountProperties> blocked_accounts = getListOfBlockedAccounts(accounts);
    if (blocked_accounts.empty()) {
        std::cout << NO_BLOCKED_ACCOUNTS << std::endl;
        system("pause");
        return;
    }

    std::string login = inputLoginForUnblock(INPUT_USER_LOGIN_FOR_UNBLOCK, blocked_accounts, accounts);
    if (login.empty()) {
        return;
    }

    if (isConfirmChanges(WAIT_CONFIRMATION_FOR_UNBLOCK) == 1) {
        int p = getAccountPositionByLogin(login, accounts);

        accounts[p].isHaveAccess = true;

        std::cout << SUCCESSFUL_ACCOUNT_UNBLOCK << std::endl;
        system("pause");
    }
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

std::vector<AccountProperties> getListOfUnblockedAccounts(const AccountProperties& current_account,
                                                          std::vector<AccountProperties>& accounts) {
    std::vector<AccountProperties> unblocked_accounts;
    for (auto& account : accounts) {
        if ((account.login != current_account.login) && account.isHaveAccess && !account.isAdmin) {
            unblocked_accounts.push_back(account);
        }
    }
    return unblocked_accounts;
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

void approveOneAccount(std::vector<AccountProperties> &unapproved_accounts,
                       std::vector<AccountProperties> &all_accounts) {
    std::string login = inputLoginForApprove(INPUT_USER_LOGIN_FOR_APPROVE, unapproved_accounts, all_accounts);
    if (login.empty()) {
        return;
    }

    int p = getAccountPositionByLogin(login, all_accounts);

    all_accounts[p].isApproved = true;

    std::cout << SUCCESSFUL_ACCOUNT_APPROVE << std::endl;
    system("pause");
}

void unapproveOneAccount(std::vector<AccountProperties> &unapproved_accounts,
                         std::vector<AccountProperties> &all_accounts) {
    std::string login = inputLoginForUnapprove(INPUT_USER_LOGIN_FOR_UNAPPROVE, unapproved_accounts, all_accounts);
    if (login.empty()) {
        return;
    }

    int p = getAccountPositionByLogin(login, all_accounts);

    all_accounts.erase(all_accounts.begin() + p);

    std::cout << SUCCESSFUL_ACCOUNT_UNAPPROVE << std::endl;
    system("pause");
}


void approveAllAccounts(std::vector<AccountProperties> &accounts) {
    for (auto &account : accounts) {
        account.isApproved = true;
    }

    std::cout << SUCCESSFUL_ALL_ACCOUNTS_APPROVE << std::endl;
    system("pause");
}

void unapproveAllAccounts(std::vector<AccountProperties> &all_accounts) {
    int i = 0;
    while (i < (int)all_accounts.size()) {
        if (!all_accounts[i].isApproved) {
            all_accounts.erase(all_accounts.begin() + i);
        } else {
            ++i;
        }
    }

    std::cout << SUCCESSFUL_ALL_ACCOUNTS_UNAPPROVE << std::endl;
    system("pause");
}

void deleteYourAccount(const AccountProperties &account, std::vector<AccountProperties> &accounts) {
    std::cout << ARE_YOU_SURE_TO_DELETE << std::endl;
    std::cout << "1) " << YES << std::endl;
    std::cout << "2) " << NO << std::endl;

    int choice = getch() - '0';
    if (choice == 1) {
        accounts.erase(accounts.begin() + getAccountPositionByLogin(account.login, accounts));
    }
}

std::string inputLoginForBlock(std::string message, const AccountProperties& account,
                               const std::vector<AccountProperties> &unblocked_accounts,
                               const std::vector<AccountProperties> &all_accounts) {
    std::string login;
    while (true) {
        system("cls");
        showListOfUsers(unblocked_accounts);
        login = inputCorrectLogin(message, unblocked_accounts);
        if (login.empty()) {
            return "";
        }
        if (!isAccountExist(login, all_accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else if (login == account.login) {
            std::cout << CANT_BLOCK_YOURSELF << std::endl;
        } else if (!isAccountExist(login, unblocked_accounts)) {
            std::cout << USER_ALREADY_BLOCKED_OR_THIS_IS_ADMIN << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return "";
        }
    }
    return login;
}

std::string inputLoginForDelete(std::string message, const AccountProperties &account,
                                const std::vector<AccountProperties> &accounts) {
    std::string login;
    while (true) {
        system("cls");
        showListOfUsers(accounts);
        login = inputCorrectLogin(message, accounts);
        if (login.empty()) {
            return "";
        }
        if (!isAccountExist(login, accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else if (login == account.login) {
            std::cout << CANT_DELETE_YOURSELF << std::endl;
        } else {
            AccountProperties current_account = getAccountByLogin(login, accounts);
            if (current_account.isAdmin) {
                std::cout << CANT_DELETE_ADMIN << std::endl;
            } else {
                break;
            }
        }
        if (!isTryAgain()) {
            return "";
        }
    }
    return login;
}

std::string inputLoginForApprove(std::string message, const std::vector<AccountProperties> &unapproved_accounts,
                                 const std::vector<AccountProperties> &all_accounts) {
    std::string login;
    while (true) {
        system("cls");
        showListOfUsers(unapproved_accounts);
        login = inputCorrectLogin(message, unapproved_accounts);
        if (login.empty()) {
            return "";
        }
        if (!isAccountExist(login, all_accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else if (!isAccountExist(login, unapproved_accounts)) {
            std::cout << LOGIN_ALREADY_APPROVED << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return "";
        }
    }
    return login;
}

std::string inputLoginForUnapprove(std::string message, const std::vector<AccountProperties> &unapproved_accounts,
                                   const std::vector<AccountProperties> &all_accounts) {
    std::string login;
    while (true) {
        system("cls");
        showListOfUsers(unapproved_accounts);
        login = inputCorrectLogin(message, unapproved_accounts);
        if (login.empty()) {
            return "";
        }
        if (!isAccountExist(login, all_accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else if (!isAccountExist(login, unapproved_accounts)) {
            std::cout << LOGIN_ALREADY_APPROVED << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return "";
        }
    }
    return login;
}

std::string inputLoginForUnblock(std::string message, const std::vector<AccountProperties> &blocked_accounts,
                                 const std::vector<AccountProperties> &all_accounts) {
    std::string login;
    while (true) {
        system("cls");
        showListOfUsers(blocked_accounts);
        login = inputCorrectLogin(message, blocked_accounts);
        if (login.empty()) {
            return "";
        }
        if (!isAccountExist(login, all_accounts)) {
            std::cout << LOGIN_DOESNT_EXIST << std::endl;
        } else if (!isAccountExist(login, blocked_accounts)) {
            std::cout << LOGIN_ALREADY_UNBLOCKED << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return "";
        }
    }
    return login;
}

