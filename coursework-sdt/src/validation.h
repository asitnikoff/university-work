#ifndef VALIDATION_H
#define VALIDATION_H

#include <vector>

#include "variables.h"
#include "accounts.h"


bool isCorrectAccount(const std::string&, const std::string&, const std::vector<AccountProperties>&);
bool isValidLogin(const std::string&);
bool isUniqueLogin(const std::string&, const std::vector<AccountProperties>&);
bool isValidPassword(const std::string&);
bool isTryAgain();
bool isLoginExist(const std::string&, const std::vector<AccountProperties>&);
bool isAccountExist(const std::string&, const std::vector<AccountProperties>&);
int readInt(int, int);

#endif