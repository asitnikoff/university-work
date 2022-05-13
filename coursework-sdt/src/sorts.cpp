#include "sorts.h"

#include <algorithm>

void sortAccountsByLoginIncrease(std::vector<AccountProperties>& accounts) {
    sort(accounts.begin(), accounts.end(), [&](const AccountProperties a, const AccountProperties b) {
        return a.login < b.login;
    });
}

void sortProductsByDate(std::vector<ProductProperties>& products) {
    sort(products.begin(), products.end(), [&](const ProductProperties a, const ProductProperties b) {
        if (a.date.year != b.date.year) {
            return a.date.year < b.date.year;
        }
        if (a.date.month != b.date.month) {
            return a.date.month < b.date.month;
        }
        return a.date.day < b.date.day;
    });
}

void sortProductsByShopNumber(std::vector<ProductProperties>& products) {
    sort(products.begin(), products.end(), [&](const ProductProperties a, const ProductProperties b) {
       return a.shop_number < b.shop_number;
    });
}

void sortProductsByProductName(std::vector<ProductProperties>& products) {
    sort(products.begin(), products.end(), [&](const ProductProperties a, const ProductProperties b) {
        return a.product_name < b.product_name;
    });
}

void sortProductsByProductAmount(std::vector<ProductProperties>& products) {
    sort(products.begin(), products.end(), [&](const ProductProperties a, const ProductProperties b) {
        return a.product_amount < b.product_amount;
    });
}

void sortProductsByResponsibleName(std::vector<ProductProperties>& products) {
    sort(products.begin(), products.end(), [&](const ProductProperties a, const ProductProperties b) {
        return a.responsible_name < b.responsible_name;
    });
}