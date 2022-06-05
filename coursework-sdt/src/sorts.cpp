#include "sorts.h"

#include <iostream>
#include <algorithm>
#include <conio.h>

#include "date-utilities.h"
#include "other-functions.h"

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

void useProductSorts(std::vector<ProductProperties> &products) {
    while (true) {
        system("cls");
        showListOfProducts(products);

        std::cout << "1) " << SORT_BY_DATE << std::endl;
        std::cout << "2) " << SORT_BY_SHOP_NUMBER << std::endl;
        std::cout << "3) " << SORT_BY_PRODUCT_NAME << std::endl;
        std::cout << "4) " << SORT_BY_PRODUCT_AMOUNT << std::endl;
        std::cout << "5) " << SORT_BY_RESPONSIBLE_NAME << std::endl;
        std::cout << "6) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                sortProductsByDate(products);
                showMessage(WAS_SORTED_BY_DATE);
                break;
            case 2:
                sortProductsByShopNumber(products);
                showMessage(WAS_SORTED_BY_SHOP_NUMBER);
                break;
            case 3:
                sortProductsByProductName(products);
                showMessage(WAS_SORTED_BY_PRODUCT_NAME);
                break;
            case 4:
                sortProductsByProductAmount(products);
                showMessage(WAS_SORTED_BY_PRODUCT_AMOUNT);
                break;
            case 5:
                sortProductsByResponsibleName(products);
                showMessage(WAS_SORTED_BY_RESPONSIBLE_NAME);
                break;
            case 6:
                writeProducts(products);
                return;
        }
    }
}
