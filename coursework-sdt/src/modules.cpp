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
        system("cls");
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
            if (!isTryAgain()) {
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
        showCommonUserModule(account, accounts);
    }
}

void showAdminUserModule(AccountProperties& account, std::vector<AccountProperties>& accounts) {
    while (true) {
        system("cls");
        showAccountWelcomeMessage(account.login);
        std::cout << "1) " << USE_ADMIN_PANEL_MESSAGE << std::endl;
        std::cout << "2) " << USE_COMMON_USER_PANEL_MESSAGE << std::endl;
        std::cout << "3) " << LOG_OUT_MESSAGE << std::endl << std::endl;

        std::cout << DANGER_ZONE << std::endl;
        std::cout << "0) " << DELETE_ACCOUNT << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 0:
                deleteYourAccount(account, accounts);
                if (!isLoginExist(account.login, accounts)) {
                    return;
                }
                break;
            case 1:
                useAccountManager(account, accounts);
                break;
            case 2:
                useProductManager();
                break;
            case 3:
            default:
                return;
        }
    }
}

void registerUserPage(std::vector<AccountProperties>& accounts, bool isAdmin) {
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

    AccountProperties new_user = createNewUser(login, password);

    std::cout << SUCCESSFUL_ACCOUNT_REGISTRATION_MESSAGE << std::endl;

    if (isAdmin) {
        new_user.isApproved = true;
    } else {
        std::cout << WAIT_CONFIRMATION << std::endl;
    }
    addAccount(new_user, accounts);
    system("pause");
}

void useAccountManager(AccountProperties& account, std::vector<AccountProperties>& accounts) {
    while (true) {
        system("cls");
        showListOfUsers(accounts);

        std::cout << "1) " << ADD_NEW_USER << std::endl;
        std::cout << "2) " << EDIT_USER << std::endl;
        std::cout << "3) " << DELETE_USER << std::endl;
        std::cout << "4) " << APPROVE_USERS_REGISTRATION << std::endl;
        std::cout << "5) " << BLOCK_USER << std::endl;
        std::cout << "6) " << UNBLOCK_USER << std::endl;
        std::cout << "7) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                registerUserPage(accounts, true);
                break;
            case 2:
                editUserData(accounts);
                break;
            case 3:
                deleteUserData(account, accounts);
                break;
            case 4:
                approveAccounts(accounts);
                break;
            case 5:
                blockAccounts(account, accounts);
                break;
            case 6:
                unblockAccounts(accounts);
                break;
            case 7:
            default:
                return;
        }
    }
}

void showCommonUserModule(AccountProperties& account, std::vector<AccountProperties>& accounts) {
    while (true) {
        std::cout << "1) " << OPEN_DATA_MANAGER << std::endl;
        std::cout << "2) " << CHANGE_PASSWORD << std::endl;
        std::cout << "3) " << LOG_OUT_MESSAGE << std::endl << std::endl;

        std::cout << DANGER_ZONE << std::endl;
        std::cout << "0) " << DELETE_ACCOUNT << std::endl;


        int choice = getch() - '0';

        switch (choice) {
            case 0:
                deleteYourAccount(account, accounts);
                if (!isLoginExist(account.login, accounts)) {
                    return;
                }
                break;
            case 1:
                useProductManager();
                break;
            case 2:
                editUserPassword(account);
                break;
            case 3:
            default:
                return;
        }
    }
}

void showMainModule(std::vector<AccountProperties> &accounts) {
    while (true) {
        system("cls");
        std::cout << WELCOME_MESSAGE << std::endl << std::endl;

        std::cout << "1) " << LOGIN_SYSTEM_MESSAGE << std::endl;
        std::cout << "2) " << REGISTER_MESSAGE << std::endl;
        std::cout << "3) " << CLOSE_SYSTEM_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                logInSystem(accounts);
                break;
            case 2:
                registerUserPage(accounts, false);
                break;
            case 3:
            default:
                return;
        }
    }
}
