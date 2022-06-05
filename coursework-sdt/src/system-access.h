#ifndef SYSTEM_ACCESS_H
#define SYSTEM_ACCESS_H


#include <vector>

#include "accounts.h"
#include "variables.h"

std::string inputLogin();
std::string inputPassword();
std::string inputCorrectLogin(std::string, const std::vector<AccountProperties>&);


#endif