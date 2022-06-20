#include "sorts.h"


template <typename Type1, typename Type2> int compareStrings(Type1 str1, Type2 str2) {
    while (((*str1) != '\0') && ((*str1) == (*str2))) {
        ++str1;
        ++str2;
    }

    return (*str1) - (*str2);
}


void swapElements(Book& el1, Book& el2) {
    Book tmp = el1;
    el1 = el2;
    el2 = tmp;
}


void sortArray(Book *books, int left, int right) {
    if (left >= right) {
        return;
    }

    Book pivot = books[(left + right) >> 1];

    int i = left - 1, j = right + 1;

    while (true) {
        do {
            ++i;
        } while (compareStrings(books[i].author, pivot.author) < 0);
        do {
            --j;
        } while (compareStrings(books[i].author, pivot.author) > 0);

        if (i >= j) {
            break;
        }

        swapElements(books[i], books[j]);
    }

    sortArray(books, left, j);
    sortArray(books, j + 1, right);
}


void sortFile() {
    
}