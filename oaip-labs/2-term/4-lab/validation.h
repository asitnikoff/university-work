#ifndef VALIDATION_H
#define VALIDATION_H


template <typename Type>
Type read();
void clearInputBuffer();
bool isValidExpressionBraces(std::string);
bool isValidExpressionOperators(std::string);


#endif