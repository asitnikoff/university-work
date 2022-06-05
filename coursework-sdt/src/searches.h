#ifndef SEARCHES_H
#define SEARCHES_H

#include <vector>

#include "products.h"

std::vector<ProductProperties> findProductsByDate(const std::vector<ProductProperties>&);
std::vector<ProductProperties> findProductsByShopNumber(const std::vector<ProductProperties>&);
std::vector<ProductProperties> findProductsByProductName(const std::vector<ProductProperties>&);
std::vector<ProductProperties> findProductsByResponsibleName(const std::vector<ProductProperties>&);
void useSearch(const std::vector<ProductProperties>&);


#endif
