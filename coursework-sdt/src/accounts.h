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
AccountProperties createNewUser(std::string, std::string);
void addAccount(const AccountProperties&, std::vector<AccountProperties>&);
void showListOfUsers(const std::vector<AccountProperties>&);
void editUserData(std::vector<AccountProperties>&);
int getAccountPositionByLogin(std::string, const std::vector<AccountProperties>&);
AccountProperties getAccountByLogin(std::string, const std::vector<AccountProperties>&);
void editUserPassword(AccountProperties&);
void editUserRole(AccountProperties&);
void deleteUserData(const AccountProperties&, std::vector<AccountProperties>&);
void approveAccounts(std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfUnapprovedAccounts(std::vector<AccountProperties>&);
void unblockAccounts(std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfBlockedAccounts(std::vector<AccountProperties>&);
void blockAccounts(const AccountProperties&, std::vector<AccountProperties>&);
std::vector<AccountProperties> getListOfUnblockedAccounts(const AccountProperties&, std::vector<AccountProperties>&);
void approveOneAccount(std::vector<AccountProperties>&, std::vector<AccountProperties>&);
void unapproveOneAccount(std::vector<AccountProperties>&, std::vector<AccountProperties>&);
void approveAllAccounts(std::vector<AccountProperties>&);
void unapproveAllAccounts(std::vector<AccountProperties>&);
void deleteYourAccount(const AccountProperties&, std::vector<AccountProperties>&);
std::string inputLoginForBlock(std::string, const AccountProperties&, const std::vector<AccountProperties>&,
                               const std::vector<AccountProperties>&);
std::string inputLoginForDelete(std::string, const AccountProperties&, const std::vector<AccountProperties>&);
std::string inputLoginForApprove(std::string, const std::vector<AccountProperties>&,
                                 const std::vector<AccountProperties>&);
std::string inputLoginForUnapprove(std::string, const std::vector<AccountProperties>&,
                                   const std::vector<AccountProperties>&);
std::string inputLoginForUnblock(std::string, const std::vector<AccountProperties>&,
                                 const std::vector<AccountProperties>&);


#endif