#include <iostream>
#include <vector>
#include <conio.h>
#include <string>

#include "modules.h"
#include "other-functions.h"
#include "system-access.h"
#include "validation.h"
#include "variables.h"


void logInSystem(std::vector<AccountProperties>& accounts) {
    AccountProperties account;
    while (true) {
        std::cout << LOGIN_INPUT_MESSAGE;
        fflush(stdout);
        std::string login = inputLogin();

        std::cout << PASSWORD_INPUT_MESSAGE;
        fflush(stdout);
        std::string password = inputPassword();

        if (isCorrectAccount(login, password, accounts)) {
            account = getAccountByLogin(login, accounts);
            break;
        }
        else {
            std::cout << INCORRECT_LOGIN_OR_PASSWORD_MESSAGE << std::endl;
            std::cout << "Попробовать снова? (1 - да, 2 - нет)" << std::endl;
            char c = _getch();
            if (c == '2') {
                break;
            }
        }
    }

    if (/*account.isAdmin*/true) {
        showAdminUserModule(account, accounts);
    }
    else {
        showCommonUserModule(account);
    }
}

void showAdminUserModule(AccountProperties& user, std::vector<AccountProperties>& accounts) {
    while (true) {
        std::cout << "1) " << USE_ADMIN_PANEL_MESSAGE << std::endl;
        std::cout << "2) " << USE_COMMON_USER_PANEL_MESSAGE << std::endl;
        std::cout << "3) " << BACK_MESSAGE << std::endl;
        char choice = _getch();

        switch (choice) {
            case '1':
                useAccountManager(user, accounts);
                break;
            case '2':
                //useDataManager(user);
                break;
            case '3':
            default:
                return;
        }
    }
}

void registerUserPage(std::vector<AccountProperties>& accounts) {
    std::string login, password;

    std::cout << REQUIREMENTS_FOR_LOGIN << std::endl;
    std::cout << REQUIREMENTS_FOR_PASSWORD << std::endl;
    while (true) {
        std::cout << LOGIN_INPUT_MESSAGE;
        fflush(stdout);
        login = inputLogin();

        std::cout << PASSWORD_INPUT_MESSAGE;
        fflush(stdout);
        password = inputPassword();
        if (isValidLogin(login) && isUniqueLogin(login, accounts) && isValidPassword(password)) {
            break;
        }
        else {
            std::cout << INCORRECT_LOGIN_OR_PASSWORD_MESSAGE << std::endl;
            std::cout << "Попробовать снова? (1 - да, 2 - нет)" << std::endl;
            if (_getch() == '2') {
                return;
            }
        }
    }

    addAccount(createNewUser(login, password), accounts);

    std::cout << SUCCESSFUL_ACCOUNT_REGISTRATION_MESSAGE << std::endl;
}

void useAccountManager(AccountProperties& user, std::vector<AccountProperties>& accounts) {
    while (true) {
        std::cout << "1) " << SHOW_ALL_USERS << std::endl;
        std::cout << "2) " << ADD_NEW_USER << std::endl;
        std::cout << "3) " << EDIT_USER << std::endl;
        std::cout << "4) " << DELETE_USER << std::endl;
        std::cout << "5) " << CONFIRM_USERS_REGISTRATION << std::endl;
        std::cout << "6) " << BLOCK_USER << std::endl;
        std::cout << "7) " << GIVE_ADMIN_ROOT << std::endl;
        std::cout << "8) " << BACK_MESSAGE << std::endl;

        char choice = _getch();

        switch (choice) {
            case '1':
                showListOfUsers(accounts);
                break;
            case '2':
                registerUserPage(accounts);
                accounts.back().isHaveAccess = true;
                break;
            case '3':
                editUserData(accounts);
                break;
            case '4':
                deleteUserData(accounts);
                break;
            case '5':
                confirmAccounts(accounts);
                break;
            case '6':
                blockAccounts(accounts);
                break;
            case '7':
                giveAdminRootAccounts(accounts);
                break;
            case '8':
            default:
                return;
        }
    }
}

void showCommonUserModule(AccountProperties& account) {
    std::cout << "Checked function \"showCommonUserModule\"" << std::endl;
}