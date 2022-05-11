#ifndef ACCOUNTS_H
#define ACCOUNTS_H


#include <vector>

#include "variables.h"

struct AccountProperties {
    std::string login;
    std::string salted_hash_password;
    std::string salt;
    bool isAdmin = false;
    bool isHaveAccess = false;
    bool isApproved = false;
};


std::string generateSalt(std::string);
AccountProperties getDefaultAccount();
void readAccounts(std::vector<AccountProperties>&);
void writeAccounts(const std::vector<AccountProperties>&);
void outputUserData(const AccountProperties&);
AccountProperties createNewUser(std::string, std::string);
void addAccount(const AccountProperties&, std::vector<AccountProperties>&);
bool isAccountExist(const std::string&, const std::vector<AccountProperties>&);
void showListOfUsers(const std::vector<AccountProperties>&);
void editUserData(std::vector<AccountProperties>&);
int getAccountPositionByLogin(std::string, const std::vector<AccountProperties>&);
AccountProperties getAccountByLogin(std::string, const std::vector<AccountProperties>&);
void editUserLogin(AccountProperties&);
void editUserPassword(AccountProperties&);
void editUserRole(AccountProperties&);
void deleteUserData(std::vector<AccountProperties>&);
void approveAccounts(std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfUnapprovedAccounts(std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfBlockedAccounts(std::vector<AccountProperties>&);
void blockAccounts(std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfUnblockedAccounts(std::vector<AccountProperties>&);
void giveAdminRootAccounts(std::vector<AccountProperties>&);


#endif