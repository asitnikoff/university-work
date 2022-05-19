#include "searches.h"

#include <iostream>
#include <conio.h>

#include "variables.h"
#include "date-utilities.h"

void useSearch(const std::vector <ProductProperties> &products) {
    std::vector<ProductProperties> search_results;
    while (true) {
        system("cls");
        showListOfProducts(products);

        std::cout << "1) " << SEARCH_BY_DATE << std::endl;
        std::cout << "2) " << SEARCH_BY_SHOP_NUMBER << std::endl;
        std::cout << "3) " << SEARCH_BY_PRODUCT_NAME << std::endl;
        std::cout << "4) " << SEARCH_BY_RESPONSIBLE_NAME << std::endl;
        std::cout << "5) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                search_results = findProductsByDate(products);
                break;
            case 2:
                search_results = findProductsByShopNumber(products);
                break;
            case 3:
                search_results = findProductsByProductName(products);
                break;
            case 4:
                search_results = findProductsByResponsibleName(products);
                break;
            case 5:
                return;
        }

        system("cls");
        if (search_results.empty()) {
            std::cout << NOTHING_FOUND << std::endl;
        } else {
            std::cout << SEARCH_RESULT << std::endl;
            showListOfProducts(search_results);
        }
        system("pause");
    }
}

std::vector<ProductProperties> findProductsByDate(const std::vector<ProductProperties> &products) {
    system("cls");

    std::vector<ProductProperties> ret_vector;

    std::cout << INPUT_DATE; fflush(stdout);
    DateProperties date = inputDate();

    for (auto &product : products) {
        if (isEqualsDate(product.date, date)) {
            ret_vector.push_back(product);
        }
    }
    return ret_vector;
}

std::vector<ProductProperties> findProductsByShopNumber(const std::vector<ProductProperties> &products) {
    system("cls");

    std::vector<ProductProperties> ret_vector;

    std::cout << INPUT_SHOP_NUMBER; fflush(stdout);
    std::string shop_number;
    std::cin >> shop_number;

    for (auto &product : products) {
        if (product.shop_number == shop_number) {
            ret_vector.push_back(product);
        }
    }
    return ret_vector;
}

std::vector<ProductProperties> findProductsByProductName(const std::vector<ProductProperties> &products) {
    system("cls");

    std::vector<ProductProperties> ret_vector;

    std::cout << INPUT_PRODUCT_NUMBER; fflush(stdout);
    std::string product_name;
    std::cin >> product_name;

    for (auto &product : products) {
        if (product.product_name == product_name) {
            ret_vector.push_back(product);
        }
    }
    return ret_vector;
}

std::vector<ProductProperties> findProductsByResponsibleName(const std::vector<ProductProperties> &products) {
    system("cls");

    std::vector<ProductProperties> ret_vector;

    std::cout << INPUT_RESPONSIBLE_NAME; fflush(stdout);
    std::string responsible_name;
    std::cin >> responsible_name;

    for (auto &product : products) {
        if (product.responsible_name == responsible_name) {
            ret_vector.push_back(product);
        }
    }
    return ret_vector;
}
