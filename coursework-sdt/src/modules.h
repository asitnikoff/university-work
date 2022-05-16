#ifndef MODULES_H
#define MODULES_H


#include <vector>

#include "accounts.h"


void logInSystem(std::vector<AccountProperties>&);
void showMainModule(std::vector<AccountProperties>&);
void registerUserPage(std::vector<AccountProperties>&);
void showAdminUserModule(AccountProperties&, std::vector<AccountProperties>&);
void showCommonUserModule(AccountProperties&, std::vector<AccountProperties>&);
void useAccountManager(AccountProperties&, std::vector<AccountProperties>&);

#endif