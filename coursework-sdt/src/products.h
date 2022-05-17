#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <vector>

struct DateProperties {
    int day;
    int month;
    int year;
};

struct ProductProperties {
    DateProperties date;
    std::string shop_number;
    std::string product_name;
    int product_amount;
    std::string responsible_name;
};


void useCommonUserProductManager();
void useAdminProductManager();
void showListOfProducts(const std::vector<ProductProperties>&);
void addProduct(std::vector<ProductProperties>&);
void deleteProduct(std::vector<ProductProperties>&);
void showListOfReleasedProducts(const std::vector<ProductProperties>&);
void readProducts(std::vector<ProductProperties>&);
void writeProducts(const std::vector<ProductProperties>&);

#endif
