#ifndef DATE_UTILITIES_H
#define DATE_UTILITIES_H

#include "products.h"

DateProperties parseDate(std::string);
bool isLessOrEqual(const DateProperties&, const DateProperties&);
DateProperties inputDate();
bool isEqualsDate(const DateProperties&, const DateProperties&);

#endif