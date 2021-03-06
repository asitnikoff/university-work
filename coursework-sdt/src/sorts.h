#ifndef SORTS_H
#define SORTS_H

#include <vector>

#include "accounts.h"
#include "products.h"


void sortAccountsByLoginIncrease(std::vector<AccountProperties>&);
void sortProductsByDate(std::vector<ProductProperties>&);
void sortProductsByShopNumber(std::vector<ProductProperties>&);
void sortProductsByProductName(std::vector<ProductProperties>&);
void sortProductsByProductAmount(std::vector<ProductProperties>&);
void sortProductsByResponsibleName(std::vector<ProductProperties>&);
void useProductSorts(std::vector<ProductProperties>&);


#endif
