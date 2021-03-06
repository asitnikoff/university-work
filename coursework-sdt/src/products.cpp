#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <map>

#include "fstream-utilities.h"
#include "date-utilities.h"
#include "products.h"
#include "variables.h"
#include "sorts.h"
#include "other-functions.h"
#include "searches.h"
#include "validation.h"
#include "modules.h"

void useCommonUserProductManager() {
    std::vector<ProductProperties> products;
    readProducts(products);

    while (true) {
        system("cls");
        if (products.empty()) {
            std::cout << LIST_OF_PRODUCTS_EMPTY << std::endl << std::endl;
        } else {
            showListOfProducts(products);
        }

        std::cout << "1) " << SORT << std::endl;
        std::cout << "2) " << SEARCH << std::endl;
        std::cout << "3) " << SHOW_LIST_OF_RELEASED_PRODUCTS << std::endl;
        std::cout << "4) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                useProductSorts(products);
                break;
            case 2:
                useSearch(products);
                break;
            case 3:
                showListOfReleasedProducts(products);
                break;
            case 4:
                writeProducts(products);
                return;
        }
    }
}

void showListOfProducts(const std::vector<ProductProperties>& products) {
    /*
    for (const auto &product : products) {
        std::cout << "date: [" << product.date.day << "." << product.date.month << "." << product.date.year << "]\n";
        std::cout << "shop_number: [" << product.shop_number << "]\n";
        std::cout << "product_name: [" << product.product_name << "]\n";
        std::cout << "product_amount: [" << product.product_amount << "]\n";
        std::cout << "responsible_name: [" << product.responsible_name << "]\n\n";
    }
    std::cout << std::endl;
    */

    std::cout << "| ??????? |    ????    |   ????? ????   |   ???????? ?த????   | ???????⢮ ?த???? |    ??? ?⢥??⢥?????    |" << std::endl;
    for (int i = 0; i < 114; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
    int cnt = 0;
    for (const auto &product : products) {
        ++cnt;
        std::cout << "|";
        std::cout << cnt << std::setw(9) << "|";
        showDate(product.date); std::cout << std::setw(3) << "|";
        std::cout << product.shop_number << std::setw(16 - (int)product.shop_number.size() + 1) << "|";
        std::cout << product.product_name << std::setw(23 - (int)product.product_name.size() + 1) << "|";
        std::cout << product.product_amount << std::setw(21 - getAmountOfBits(product.product_amount) + 1) << "|";
        std::cout << product.responsible_name << std::setw(26 - (int)product.responsible_name.size() + 1) << "|";
        std::cout << std::endl;
    }
    for (int i = 0; i < 114; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl << std::endl;
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
    fout.open(PRODUCTS_FILENAME, std::ios::out | std::ios::binary);

    int n = (int)products.size();
    for (int i = 0; i < n; ++i) {
        writeDateInOfstream(fout, products[i].date);
        writeStringInOfstream(fout, products[i].shop_number);
        writeStringInOfstream(fout, products[i].product_name);
        writeIntInOfstream(fout, products[i].product_amount);
        writeStringInOfstream(fout, products[i].responsible_name);
    }
    fout.close();
}

void showListOfReleasedProducts(const std::vector<ProductProperties>& products) {
    std::cout << INPUT_SHOP_NUMBER; fflush(stdout);
    std::string shop_number;
    std::cin >> shop_number;
    std::cout << INPUT_RANGE_DATE; fflush(stdout);
    DateProperties begin_date = inputDate();
    DateProperties end_date = inputDate();

    std::map<std::string, int> released_products;
    for (auto product : products) {
        if ((product.shop_number == shop_number) &&
            isLessOrEqual(begin_date, product.date) &&
            isLessOrEqual(product.date, end_date)) {
            released_products[product.product_name] += product.product_amount;
        }
    }

    if (released_products.empty()) {
        std::cout << NO_RELEASE_PRODUCTS_SUCH_REQUIRMENTS << std::endl;
    } else {
        system("cls");
        for (auto& product : released_products) {
            std::cout << product.first << " - " << product.second << std::endl;
        }
    }
    system("pause");
}

void addProduct(std::vector<ProductProperties> &products) {
    system("cls");
    ProductProperties product;
    product.date = inputDate();
    std::cout << INPUT_SHOP_NUMBER; fflush(stdout);
    std::cin >> product.shop_number;
    std::cout << INPUT_PRODUCT_NAME; fflush(stdout);
    std::cin >> product.product_name;
    while (true) {
        std::cout << INPUT_PRODUCT_AMOUNT; fflush(stdout);
        std::cin >> product.product_amount;
        clearInputBuffer();
        if (product.product_amount >= 0) {
            break;
        } else {
            std::cout << PRODUCT_AMOUNT_CANT_BE_LESS_ZERO << std::endl;
            std::cout << PLEASE_TRY_AGAIN << std::endl;
        }
    }
    std::cout << INPUT_PRODUCT_RESPONSIBLE_NAME; fflush(stdout);
    getline(std::cin, product.responsible_name);

    products.push_back(product);

    std::cout << PRODUCT_WAS_ADDED << std::endl;
    system("pause");
}

void deleteProduct(std::vector<ProductProperties> &products) {
    int position = -1;
    while (true) {
        system("cls");
        if (products.empty()) {
            std::cout << LIST_OF_PRODUCTS_EMPTY << std::endl << std::endl;
        } else {
            showListOfProducts(products);
        }

        std::cout << INPUT_PRODUCT_POSITION;
        position = readInt(1, (int) products.size());

        if (position == 0) {
            std::cout << INVALID_INPUT << std::endl;
            std::cout << NUMBER_MUST_BE_IN_RANGE << " [1; " << (int) products.size() << "]." << std::endl;
        } else {
            break;
        }

        if (!isTryAgain()) {
            return;
        }
    }

    if (isConfirmChanges(WAIT_CONFIRMATION_FOR_DELETE_PRODUCT)) {
        products.erase(products.begin() + position - 1);
        std::cout << PRODUCT_WAS_DELETED << std::endl;
        system("pause");
    } else {
        return;
    }
}

void useAdminProductManager() {
    std::vector<ProductProperties> products;
    readProducts(products);

    while (true) {
        system("cls");
        if (products.empty()) {
            std::cout << LIST_OF_PRODUCTS_EMPTY << std::endl << std::endl;
        } else {
            showListOfProducts(products);
        }

        std::cout << "1) " << SORT << std::endl;
        std::cout << "2) " << SEARCH << std::endl;
        std::cout << "3) " << ADD_PRODUCT << std::endl;
        std::cout << "4) " << DELETE_PRODUCT << std::endl;
        std::cout << "5) " << EDIT_PRODUCT << std::endl;
        std::cout << "6) " << SHOW_LIST_OF_RELEASED_PRODUCTS << std::endl;
        std::cout << "7) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 1:
                useProductSorts(products);
                break;
            case 2:
                useSearch(products);
                break;
            case 3:
                addProduct(products);
                break;
            case 4:
                deleteProduct(products);
                break;
            case 5:
                editProductModule(products);
                break;
            case 6:
                showListOfReleasedProducts(products);
                break;
            case 7:
                writeProducts(products);
                return;
        }
    }
}

void editProduct(ProductProperties& product) {
    while (true) {
        system("cls");
        showProductData(product);
        std::cout << "0) " << BACK_MESSAGE << std::endl;

        int choice = getch() - '0';

        switch (choice) {
            case 0:
                return;
            case 1:
                editProductDate(product);
                break;
            case 2:
                editProductShopNumber(product);
                break;
            case 3:
                editProductProductName(product);
                break;
            case 4:
                editProductProductAmount(product);
                break;
            case 5:
                editProductResponsibleName(product);
                break;
        }
    }
}

void showProductData(const ProductProperties &product) {
    std::cout << "1) [????]: ";
    showDate(product.date);
    std::cout << std::endl;
    std::cout << "2) [????? ????]: " << product.shop_number << std::endl;
    std::cout << "3) [???????? ?த????]: " << product.product_name << std::endl;
    std::cout << "4) [???????⢮ ?த????]: " << product.product_amount << std::endl;
    std::cout << "5) [??? ?⢥??⢥?????]: " << product.responsible_name << std::endl;
}

void editProductDate(ProductProperties &product) {
    DateProperties date = inputDate();
    if (date.day == 0) {
        return;
    }

    product.date = date;
}

void editProductShopNumber(ProductProperties &product) {
    system("cls");
    std::cout << INPUT_SHOP_NUMBER;
    std::string shop_number;
    std::cin >> shop_number;

    product.shop_number = shop_number;
}

void editProductProductName(ProductProperties &product) {
    system("cls");
    std::cout << INPUT_PRODUCT_NAME;
    std::string product_name;
    std::cin >> product_name;

    product.product_name = product_name;
}

void editProductProductAmount(ProductProperties &product) {
    int product_amount;
    do {
        system("cls");
        std::cout << INPUT_PRODUCT_AMOUNT; fflush(stdout);
        std::cin >> product_amount;
        clearInputBuffer();
        if (product_amount >= 0) {
            break;
        } else {
            std::cout << PRODUCT_AMOUNT_CANT_BE_LESS_ZERO << std::endl;
        }

        if (!isTryAgain()) {
            return;
        }
    } while (true);

    product.product_amount = product_amount;
}

void editProductResponsibleName(ProductProperties &product) {
    system("cls");
    std::cout << INPUT_PRODUCT_RESPONSIBLE_NAME;
    std::string responsible_name;
    std::cin >> responsible_name;

    product.responsible_name = responsible_name;
}
