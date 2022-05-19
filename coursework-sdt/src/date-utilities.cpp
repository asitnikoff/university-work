#include "date-utilities.h"

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
    std::string date_str;
    std::cin >> date_str;

    return parseDate(date_str);
}

bool isEqualsDate(const DateProperties &left_date, const DateProperties &right_date) {
    return (left_date.day == right_date.day) &&
           (left_date.month == right_date.month) &&
           (left_date.year == right_date.year);
}
