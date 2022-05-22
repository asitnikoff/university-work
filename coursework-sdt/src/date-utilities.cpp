#include "date-utilities.h"
#include "variables.h"
#include "validation.h"

#include <iostream>

DateProperties parseDate(std::string date_str) {
    DateProperties ret_date;
    ret_date.day = atoi(date_str.substr(0, date_str.find('.')).c_str());
    date_str.erase(0, date_str.find('.') + 1);
    ret_date.month = atoi(date_str.substr(0, date_str.find('.')).c_str());
    date_str.erase(0, date_str.find('.') + 1);
    ret_date.year = atoi(date_str.c_str());

    return ret_date;
}

bool isLessOrEqual(const DateProperties &left_date, const DateProperties &right_date) {
    if (left_date.year != right_date.year) {
        return left_date.year <= right_date.year;
    }
    if (left_date.month != right_date.month) {
        return left_date.month <= right_date.month;
    }
    return left_date.day <= right_date.day;
}

DateProperties inputDate() {
    DateProperties date;
    while (true) {
        std::cout << INPUT_DATE;
        std::string date_str;
        std::cin >> date_str;
        date = parseDate(date_str);
        if (date.day == 0) {
            std::cout << INCORRECT_DATE_OR_FORMAT << std::endl;
        } else {
            break;
        }

        if (!isTryAgain()) {
            return date;
        }
    }

    return date;
}

bool isEqualsDate(const DateProperties &left_date, const DateProperties &right_date) {
    return (left_date.day == right_date.day) &&
           (left_date.month == right_date.month) &&
           (left_date.year == right_date.year);
}

void showDate(const DateProperties &date) {
    if (date.day < 10) {
        std::cout << "0";
    }
    std::cout << date.day << "-";
    if (date.month < 10) {
        std::cout << "0";
    }
    std::cout << date.month << "-";
    std::cout << date.year << std::endl;
}
