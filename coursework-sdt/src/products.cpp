#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>

#include "fstream-utilities.h"
#include "date-utilities.h"
#include "products.h"
#include "variables.h"
#include "sorts.h"

void useProductManager() {
    std::vector<ProductProperties> products;
    readProducts(products);

    while (true) {
        showListOfProducts(products);

        std::cout << "1) " << SORT_BY_DATE << std::endl;
        std::cout << "2) " << SORT_BY_SHOP_NUMBER << std::endl;
        std::cout << "3) " << SORT_BY_PRODUCT_NAME << std::endl;
        std::cout << "4) " << SORT_BY_PRODUCT_AMOUNT << std::endl;
        std::cout << "5) " << SORT_BY_RESPONSIBLE_NAME << std::endl;
        std::cout << "6) " << SHOW_LIST_OF_RELEASED_PRODUCTS << std::endl;
        std::cout << "7) " << ADD_PRODUCT << std::endl;
        std::cout << "8) " << DELETE_PRODUCT << std::endl;
        std::cout << "9) " << BACK_MESSAGE << std::endl;

        char choice = (char)getch();

        switch (choice) {
            case '1':
                sortProductsByDate(products);
                break;
            case '2':
                sortProductsByShopNumber(products);
                break;
            case '3':
                sortProductsByProductName(products);
                break;
            case '4':
                sortProductsByProductAmount(products);
                break;
            case '5':
                sortProductsByResponsibleName(products);
                break;
            case '6':
                showListOfReleasedProducts(products);
                break;
            case '7':
                addProduct(products);
                break;
            case '8':
                deleteProduct(products);
                break;
            case '9':
            default:
                return;
        }
    }

    writeProducts(products);
}

void showListOfProducts(const std::vector<ProductProperties>& products) {
    for (const auto &product : products) {
        std::cout << "date: [" << product.date.day << "." << product.date.month << "." << product.date.year << "]\n";
        std::cout << "shop_number: [" << product.shop_number << "]\n";
        std::cout << "product_name: [" << product.product_name << "]\n";
        std::cout << "product_amount: [" << product.product_amount << "]\n";
        std::cout << "responsible_name: [" << product.responsible_name << "]\n\n";
    }
    std::cout << std::endl;
}

void readProducts(std::vector<ProductProperties>& products) {
    std::ifstream fin;
    fin.open(PRODUCTS_FILENAME, std::ios::in | std::ios::binary);
    ProductProperties temp;

    fin.seekg(0, std::ios::end);
    int file_size = (int)fin.tellg();
    fin.seekg(0, std::ios::beg);

    while (fin.tellg() < file_size) {
        temp.date = readDateFromIfstream(fin);
        temp.shop_number = readStringFromIfstream(fin);
        temp.product_name = readStringFromIfstream(fin);
        temp.product_amount = readIntFromIfstream(fin);
        temp.responsible_name = readStringFromIfstream(fin);
        products.push_back(temp);
    }
    fin.close();
}

void writeProducts(const std::vector<ProductProperties>& products) {
    std::ofstream fout;
    fout.open(ACCOUNTS_FILENAME, std::ios::out | std::ios::binary);

    int n = (int)products.size();
    for (int i = 0; i < n; ++i) {
        writeDateInOfstream(fout, products[i].date);
        writeStringInOfstream(fout, products[i].shop_number);
        writeStringInOfstream(fout, products[i].product_name);
        writeIntInOfstream(fout, products[i].product_amount);
        writeStringInOfstream(fout, products[i].responsible_name);
    }
}

void showListOfReleasedProducts(const std::vector<ProductProperties>& products) {
    std::cout << INPUT_SHOP_NUMBER; fflush(stdout);
    std::string shop_number;
    std::cin >> shop_number;
    std::cout << INPUT_RANGE_DATE; fflush(stdout);
    std::string begin_date_str, end_date_str;
    std::cin >> begin_date_str >> end_date_str;
    DateProperties begin_date = parseDate(begin_date_str);
    DateProperties end_date = parseDate(end_date_str);

    std::vector<ProductProperties> released_products;
    for (auto product : products) {
        if ((product.shop_number == shop_number) &&
            isLessOrEqual(begin_date, product.date) &&
            isLessOrEqual(product.date, end_date)) {
            released_products.push_back(product);
        }
    }

    showListOfProducts(released_products);
}

void addProduct(std::vector<ProductProperties> &products) {
    ProductProperties product;
    std::cout << INPUT_DATE; fflush(stdout);
    std::string date_str;
    std::cin >> date_str;
    product.date = parseDate(date_str);
    std::cout << INPUT_SHOP_NUMBER; fflush(stdout);
    std::cin >> product.shop_number;
    std::cout << INPUT_PRODUCT_NAME; fflush(stdout);
    std::cin >> product.product_name;
    std::cout << INPUT_PRODUCT_AMOUTN; fflush(stdout);
    std::cin >> product.product_amount;
    std::cout << INPUT_RESPONSIBLE_NAME; fflush(stdout);
    std::cin >> product.responsible_name;

    products.push_back(product);
}

void deleteProduct(std::vector<ProductProperties> &products) {
    showListOfProducts(products);

    std::cout << INPUT_PRODUCT_NUMBER; fflush(stdout);
    int p;
    std::cin >> p;

    products.erase(products.begin() + p - 1);
}
