#ifndef BOOK_H
#define BOOK_H


#include <string>


struct Book {
    int book_number;
    char author[100];
    char title[100];
    int year;
    char publish_house[100];
    int page_number;
};


#endif