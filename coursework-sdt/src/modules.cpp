#include <iostream>
#include <vector>
#include <conio.h>
#include <string>

#include "modules.h"
#include "other-functions.h"
#include "system-access.h"
#include "validation.h"
#include "variables.h"
#include "products.h"


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
            char c = (char)getch();
            if (c == '2') {
                return;
            }
        }
    }

    if (!account.isApproved) {
        std::cout << NOT_APPROVED_MESSAGE << std::endl;
        system("pause");
        return;
    }

    if (!account.isHaveAccess) {
        std::cout << BLOCK_MESSAGE << std::endl;
        system("pause");
        return;
    }

    if (account.isAdmin) {
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
        std::cout << "3) " << LOG_OUT_MESSAGE << std::endl;
        char choice = (char)getch();

        switch (choice) {
            case '1':
                useAccountManager(user, accounts);
                break;
            case '2':
                useProductManager();
                break;
            case '3':
            default:
                return;
        }
    }
}

void registerUserPage(std::vector<AccountProperties>& accounts) {
    std::string login, password;

    while (true) {
        system("cls");

        std::cout << REQUIREMENTS_FOR_LOGIN << std::endl;
        std::cout << REQUIREMENTS_FOR_PASSWORD << std::endl << std::endl;
        std::cout << LOGIN_INPUT_MESSAGE;
        fflush(stdout);
        login = inputLogin();

        std::cout << PASSWORD_INPUT_MESSAGE;
        fflush(stdout);
        password = inputPassword();
        if (!isValidLogin(login)) {
            std::cout << LOGIN_NOT_IN_REQUIREMENTS << std::endl;
        } else if (!isUniqueLogin(login, accounts)) {
            std::cout << LOGIN_NOT_UNIQUE << std::endl;
        } else if (!isValidPassword(password)) {
            std::cout << PASSWORD_NOT_IN_REQUIREMENTS << std::endl;
        } else {
            break;
        }
        if (!isTryAgain()) {
            return;
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
        std::cout << "7) " << UNBLOCK_USER << std::endl;
        std::cout << "8) " << GIVE_ADMIN_ROOT << std::endl;
        std::cout << "9) " << BACK_MESSAGE << std::endl;

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
                approveAccounts(accounts);
                break;
            case '6':
                blockAccounts(accounts);
                break;
            case '7':
                unblockAccounts(accounts);
                break;
            case '8':
                giveAdminRootAccounts(accounts);
                break;
            case '9':
            default:
                return;
        }
    }
}

void showCommonUserModule(AccountProperties& account) {
    while (true) {
        std::cout << "1) " << OPEN_DATA_MANAGER << std::endl;
        std::cout << "2) " << CHANGE_PASSWORD << std::endl;
        std::cout << "3) " << LOG_OUT_MESSAGE << std::endl;

        char choice = (char) getch();

        switch (choice) {
            case '1':
                useProductManager();
                break;
            case '2':
                editUserPassword(account);
                break;
            case '3':
            default:
                return;
        }
    }
}