#ifndef OTHER_FUNCTIONS_H
#define OTHER_FUNCTIONS_H


#include <vector>

#include "accounts.h"


void clearInputBuffer();
void showAccountWelcomeMessage(const std::string&);
bool isConfirmChanges(std::string);
void showMessage(std::string);
int getAmountOfBits(int);


#endif