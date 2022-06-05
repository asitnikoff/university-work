#ifndef MODULES_H
#define MODULES_H


#include <vector>

#include "accounts.h"
#include "products.h"


void logInSystem(std::vector<AccountProperties>&);
void showMainModule(std::vector<AccountProperties>&);
void registerUserPage(std::vector<AccountProperties>&, bool);
void showAdminUserModule(AccountProperties&, std::vector<AccountProperties>&);
void showCommonUserModule(AccountProperties&, std::vector<AccountProperties>&);
void useAccountManager(AccountProperties&, std::vector<AccountProperties>&);
void editProductModule(std::vector<ProductProperties> &products);


#endif